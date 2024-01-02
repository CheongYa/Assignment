#include "hwdata.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <sqlite3.h>
#include <dirent.h>

HWdata::HWdata() {
    // SQLite database 연결
    int rc = sqlite3_open("main.db", &db);
    logMessage("main.db와 연결하였습니다. #HW");

    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

HWdata::~HWdata() {
    // SQLite database 종료
    sqlite3_close(db);
}

// 로그 남기는 함수
void HWdata::logMessage(const std::string& message) {
    // 현재 시간을 얻기
    std::time_t currentTime = std::time(0);
    std::tm* now = std::localtime(&currentTime);

    // 로그 파일명 생성
    char filename[50];
    std::strftime(filename, sizeof(filename), "log.txt", now);

    // 로그 파일 열기
    std::ofstream logFile(filename, std::ios::app);

    // 현재 시간과 메시지를 로그 파일에 기록
    logFile << "[" << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday
            << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "] " << message << std::endl;

    // 파일 닫기
    logFile.close();
}

// DB 시작 함수
void HWdata::startHwDB() {
    dropAndCreateDB(db, rc);
    saveData(db, rc);
}

// 테이블 삭제와 생성 함수
void HWdata::dropAndCreateDB(sqlite3* db, int rc) {
    // 테이블 삭제
    const char* drop_table_query =
        "DROP TABLE IF EXISTS os_table;"
        "DROP TABLE IF EXISTS cpu_table;"
        "DROP TABLE IF EXISTS nic_table;"
        "DROP TABLE IF EXISTS memory_table;";

    rc = sqlite3_exec(db, drop_table_query, 0, 0, 0);

    logMessage("os, cpu, nic, memory 테이블을 삭제하였습니다. #HW");

    // 동일한 테이블이 없으면 생성
    const char* create_table_query =
        "CREATE TABLE IF NOT EXISTS os_table ("
        "    id INTEGER PRIMARY KEY,"
        "    name text,"
        "    detail text,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE TABLE IF NOT EXISTS cpu_table ("
        "    id INTEGER PRIMARY KEY,"
        "    processor text,"
        "    name text,"
        "    detail text,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE TABLE IF NOT EXISTS nic_table ("
        "    id INTEGER PRIMARY KEY,"
        "    interface text,"
        "    operation_state text,"
        "    speed text,"
        "    mac_address text,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE TABLE IF NOT EXISTS memory_table ("
        "    id INTEGER PRIMARY KEY,"
        "    name text,"
        "    detail text,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");";

    rc = sqlite3_exec(db, create_table_query, 0, 0, 0);

    if (rc) {
        logMessage("os, cpu, nic, memory 테이블 생성에 실패하였습니다. #HW");
        std::cerr << "Cannot create table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
    logMessage("os, cpu, nic, memory 테이블을 생성하였습니다. #HW");
}

// HW의 정보를 수집하고 transaction과 commit을 이용해 한 번에 DB에 저장하는 함수 (실질적인 저장)
void HWdata::saveData(sqlite3* db, int rc) {
    // transaction 시작
    rc = sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

    insertOsData(db, rc);
    insertCpuData(db, rc);
    insertNicData(db, rc);
    insertMemoryData(db, rc);

    // transaction Commit
    rc = sqlite3_exec(db, "COMMIT", 0, 0, 0);
    logMessage("main.db에 정보를 저장하였습니다. #HW");
}

// OS 정보가 들어있는 파일을 열어 Insert 쿼리문을 작성하는 함수
void HWdata::insertOsData(sqlite3* db, int rc) {
    logMessage("OS 정보를 DB에 저장할 준비를 시작합니다. #HW");
    // 파일에서 읽어올 문자열
    std::ifstream input_file("/etc/os-release");

    if (!input_file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        exit(1);
    }

    std::string line;

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(input_file, line)) {
        // 공백과 " 제거
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '"'), line.end());

        // = 가 있는 문자열 찾기
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            // = 기준 왼쪽 = key, 오른쪽 = value
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Insert 쿼리문 작성
            std::ostringstream insert_query;
            insert_query << "INSERT INTO os_table (name, detail) VALUES ('" << key << "', '" << value << "');";

            rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

            if (rc) {
                std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
            }
        }
    }

    input_file.close();
}

// CPU 정보가 들어있는 파일을 열어 Insert 쿼리문을 작성하는 함수
void HWdata::insertCpuData(sqlite3* db, int rc) {
    logMessage("CPU 정보를 DB에 저장할 준비를 시작합니다. #HW");
    // 파일에서 읽어올 문자열
    std::ifstream input_file("/proc/cpuinfo");

    if (!input_file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        exit(1);
    }

    std::string line;
    std::string processor = "0";

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(input_file, line)) {
        // 공백과 \t 제거
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

        // : 가 있는 문자열 찾기
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // key 값이 processor 일 때, processor 문자열 변경
            if (key == "processor") {
                processor = value;
            }

            // Insert 쿼리문 작성
            std::ostringstream insert_query;
            insert_query << "INSERT INTO cpu_table (processor, name, detail) VALUES ('" << processor << "', '" << key << "', '" << value << "');";

            rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

            if (rc) {
                std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
            }
        }
    }

    input_file.close();
}

// Memory 정보가 들어있는 파일을 열어 Insert 쿼리문을 작성하는 함수
void HWdata::insertMemoryData(sqlite3* db, int rc) {
    logMessage("Memory 정보를 DB에 저장할 준비를 시작합니다. #HW");
    // 파일에서 읽어올 문자열
    std::ifstream input_file("/proc/meminfo");

    if (!input_file.is_open()) {
        std::cerr << "Error opening file. : meminfo" << std::endl;
        exit(1);
    }

    std::string line;

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(input_file, line)) {
        // 공백 제거
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Insert 쿼리문 작성
            std::ostringstream insert_query;
            insert_query << "INSERT INTO memory_table (name, detail) VALUES ('" << key << "', '" << value << "');";

            rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

            if (rc) {
                std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
            }
        }
    }

    input_file.close();
}

// NIC 정보가 들어있는 디렉토리를 열고 내부의 파일을 열어 Insert 쿼리문을 작성하는 함수
void HWdata::insertNicData(sqlite3* db, int rc) {
    logMessage("NIC 정보를 DB에 저장할 준비를 시작합니다. #HW");
    // 네트워크 인터페이스 정보를 읽을 디렉토리 경로
    const std::string dir_path = "/sys/class/net";

    // 디렉토리 열기
    DIR* dir = opendir(dir_path.c_str());

    if (!dir) {
        std::cerr << "Error opening directory." << std::endl;
        exit(1);
    }

    struct dirent* entry;
    std::string nicData[3];

    // 디렉토리 내의 파일 및 디렉토리 읽기
    while ((entry = readdir(dir)) != NULL) {
        // "."과 ".."은 무시
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 디렉토리 이름을 읽어와 데이터베이스에 저장
        std::string interface = entry->d_name;

        // 파일 경로
        std::string operstateFile_path = dir_path + "/" + interface + "/operstate";
        std::string speedFile_path = dir_path + "/" + interface + "/speed";
        std::string addressFile_path = dir_path + "/" + interface + "/address";

        // 파일 열기
        std::ifstream operstateFile(operstateFile_path.c_str());

        if (!operstateFile.is_open()) {
            std::cerr << "Error opening file : memory(operstateFile))" << std::endl;
            continue;
        }
        
        operstateFile >> nicData[0];

        // 파일 닫기
        operstateFile.close();

        std::ifstream speedFile(speedFile_path.c_str());

        if (!speedFile.is_open()) {
            std::cerr << "Error opening file : memory(speedFile))" << std::endl;
            continue;
        }

        // 파일이 비어있는지 확인
        if (speedFile.peek() == std::ifstream::traits_type::eof()) {
            nicData[1] = "NULL"; // 또는 다른 NULL 표현 방식으로 변경할 수 있음
        } else {
            speedFile >> nicData[1];
        }

        speedFile.close();


        std::ifstream addressFile(addressFile_path.c_str());

        if (!addressFile.is_open()) {
            std::cerr << "Error opening file : memory(addressFile))" << std::endl;
            continue;
        }

        addressFile >> nicData[2];
        
        addressFile.close();

        // Insert 쿼리문 작성
        std::ostringstream insert_query;
        insert_query << "INSERT INTO nic_table (interface, operation_state, speed, mac_address) VALUES ('"
                     << interface << "', '"
                     << nicData[0] << "', '"
                     << nicData[1] << "', '"
                     << nicData[2] << "');";

        rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

        if (rc) {
            std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    // 디렉토리 닫기
    closedir(dir);
}