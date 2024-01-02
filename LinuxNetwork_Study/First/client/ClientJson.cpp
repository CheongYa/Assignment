#include "ClientJson.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream> // 파일 입출력을 위한 헤더 파일

using json = nlohmann::json;

Json::Json() {
    makeJson(); 
}
Json::~Json() {}

// JSON 생성 시작 함수
json Json::makeJSON() {
    // 시스템 정보를 JSON으로 가져오기
    json systemData;

    getCpuData(systemData["CPU"]);       // CPU 정보 수집
    getNicData(systemData["NIC"]);   // 네트워크 정보 수집
    getMemoryData(systemData["Memory"]); // 메모리 정보 수집
    getDiskData(systemData["Disk"]);     // 디스크 정보 수집

    return systemData;
}

void Json::getCpuData(json &cpudata) {
    // 프로세서의 수를 찾습니다.
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    std::string line;
    int processorCount = 0;
    while (std::getline(cpuInfoFile, line)) {
        if (line.find("processor") != std::string::npos) {
            processorCount++;
        }
    }

    // 각 프로세서를 반복합니다.
    for (int i = 0; i < processorCount; ++i) {ssssssssssssssssssssssss
        json processorData;  // 각 프로세서에 대한 정보를 저장할 JSON 객체

        // 코어 수 확인
        processorData["Cores"] = getCPUInfo("cpu cores", i);

        // 모델 이름 확인
        processorData["Model"] = getCPUInfo("model name", i);

        // Siblings 확인
        processorData["Siblings"] = getCPUInfo("siblings", i);

        // cpudata에 각 프로세서의 정보를 추가합니다.
        cpudata[std::to_string(i)] = processorData;
    }
}

// CPU 정보를 읽어오는 함수
std::string getCPUInfo(const std::string &key, int processorNumber) {
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    std::string line;
    int currentProcessor = -1;  // 현재 프로세서를 추적하는 변수
    while (std::getline(cpuInfoFile, line)) {
        if (line.find("processor") != std::string::npos) {
            // 새로운 프로세서 항목을 찾았습니다.
            currentProcessor = std::stoi(line.substr(line.find(":") + 2));
        }
        if (currentProcessor == processorNumber) {
            size_t pos = line.find(key);
            if (pos != std::string::npos) {
                // 찾은 경우, 해당 라인에서 ':' 다음의 값을 반환
                return line.substr(line.find(":") + 2);
            }
        }
    }
    return "N/A"; // 정보를 찾지 못한 경우
}

void Json::getNicData(json &nicdata) {
    char interfaces[MAX_INTERFACES][MY_IFNAMSIZ];

    // NIC 인터페이스 목록 얻기
    int numInterfaces = getNICInterfaces(interfaces);

    // 각 NIC에 대한 정보 출력
    for (int i = 0; i < numInterfaces; ++i) {
        getNICInfo(interfaces[i], nicdata);
    }
}

// NIC 인터페이스 목록을 얻는 함수
int getNICInterfaces(char interfaces[][MY_IFNAMSIZ]) {
    int numInterfaces = 0;
    DIR *dir;
    struct dirent *ent;

    // /sys/class/net 디렉토리 열기
    if ((dir = opendir("/sys/class/net")) == NULL) {
        throw std::runtime_error("/sys/class/net를 읽어올 수 없습니다.");
    } else {
        while ((ent = readdir(dir)) != NULL && numInterfaces < MAX_INTERFACES) {
            // "."와 ".."을 제외하고 디렉토리 이름을 배열에 추가
            if (std::strcmp(ent->d_name, ".") != 0 && std::strcmp(ent->d_name, "..") != 0) {
                std::strcpy(interfaces[numInterfaces], ent->d_name);
                ++numInterfaces;
            }
        }
        closedir(dir);
    }

    return numInterfaces;
}

// NIC 정보를 얻는 함수
void getNICInfo(const char *interface, json &nicdata) {
    nicdata[interface]["Interface"] = interface;

    // 운영 상태정보 읽기
    std::string operstate = readNICFile("/sys/class/net/" + std::string(interface) + "/operstate");
    nicdata[interface]["Operational State"] = operstate;

    // 속도 정보 읽기
    std::string speed = readNICFile("/sys/class/net/" + std::string(interface) + "/speed");
    nicdata[interface]["Speed"] = speed;

    // MAC 주소 읽기
    std::string macAddress = readNICFile("/sys/class/net/" + std::string(interface) + "/address");
    nicdata[interface]["MAC Address"] = macAddress;
}

// NIC 파일 읽기 위한 함수
std::string readNICFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error(filePath + " 파일을 열 수 없습니다.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    // 개행문자 제거
    std::string content = buffer.str();
    content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());

    return content;
}

void Json::getMemoryData(json &memorydata) {
    std::ifstream meminfo("/proc/meminfo"); // meminfo 파일 열기
    std::string line;

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(meminfo, line)) {
        // ':'을 기준으로 문자열을 나누어 key-value 쌍으로 저장
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // key와 value에서 불필요한 공백 제거
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

            // JSON 객체에 추가
            memorydata["Memory"][key] = value;
        }
    }
}

void Json::getDiskData(json &diskdata) {
    std::ifstream diskstats("/proc/diskstats"); // diskstats 파일 열기

    if (!diskstats.is_open()) {
        throw std::runtime_error("/proc/diskstats 파일을 열 수 없습니다.");
    }

    std::string line;

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(diskstats, line)) {
        std::istringstream iss(line);
        std::string device;
        long completed, merged, sectors, ms_reading, ms_writing;

        // 공백을 기준으로 문자열을 파싱하고, 변수 형식에 맞게 변환
        iss >> device >> completed >> merged >> sectors >> ms_reading >> ms_writing;

        // 디스크 정보 출력
        diskdata[device]["Device"] = device;
        // 디스크가 완료한 입출력 작업의 수
        diskdata[device]["Completed I/O operations"] = completed;
        // 디스크에서 병합된 입출력 작업의 수
        diskdata[device]["Merged I/O operations"] = merged;
        // 디스크의 총 섹터 수
        diskdata[device]["Total sectors"] = sectors;
        // 디스크에서 읽기 작업에 소요된 시간(ms)
        diskdata[device]["Time spent reading (ms)"] = ms_reading;
        // 디스크에서 쓰기 작업에 소요된 시간(ms)
        diskdata[device]["Time spent writing (ms)"] = ms_writing;
    }

    diskstats.close(); // 파일 닫기
}
