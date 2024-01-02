#include "ServerDatabase.h"

#include <iostream>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include <mutex>

Database::Database() { ConnectToMariaDB(); }
Database::~Database() {
    if (handle_) {
        ::mysql_close(handle_);
        std::cout << "MariaDB 연결 해제" << std::endl;
    }
}

void Database::ConnectToMariaDB() {
    // Initialize MariaDB connection
    handle_ = ::mysql_init(nullptr);
    if (!handle_ ) {
        std::cerr << "MariaDB 연결 초기화 실패" << std::endl;
        exit(1);
    }

    const char* host = "localhost";
    const char* user = "root";
    const char* password = "1234";
    const char* database = "servertest";
    unsigned int port = 3306;

    if (::mysql_real_connect(handle_, host, user, password, database, port, nullptr, 0) == nullptr) {
        std::cerr << "MariaDB 연결 실패: " << mysql_error(handle_) << std::endl;
        exit(1);
    }

    std::cout << "MariaDB 연결 성공" << std::endl;
}

// Save message to the database
void Database::SaveToDatabase(std::string_view message) {
    // Assume JSON and save to the database
    try {
        auto j = json::parse(message);
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (j.find("CPU") != j.end()) {
           SaveCpuToDatabase(j["CPU"]);
        }
        if (j.find("NIC") != j.end()) {
           SaveNicToDatabase(j["NIC"]);
        }
        if (j.find("Memory") != j.end()) {
           SaveMemoryToDatabase(j["Memory"]);
        }
        if (j.find("Disk") != j.end()) {
           SaveDiskToDatabase(j["Disk"]);
        }

        std::cout << "데이터베이스에 저장 완료" << std::endl;
    } catch (const nlohmann::detail::parse_error& e) { // JSON 파싱 오류 캐치
        std::cerr << "JSON 파싱 오류: " << e.what() << std::endl;
        std::cerr << "오류가 발생한 메시지: " << message << std::endl;
    } catch (const std::exception& e) { // DB 오류 캐치
        std::cerr << "데이터베이스 저장 실패: " << e.what() << std::endl;
        std::cerr << "오류가 발생한 메시지: " << message << std::endl;
    }
}

// CPU 데이터 추출 및 저장 함수
void Database::SaveCpuToDatabase(const json& cpuData) {
        for (const auto& processor : cpuData) {
        // 각 프로세서 정보 추출
        std::string cores = processor["Cores"].get<std::string>();
        std::string model = processor["Model"].get<std::string>();
        std::string siblings = processor["Siblings"].get<std::string>();

        // 쿼리 생성 후 DB에 데이터 저장
        std::string query = "INSERT INTO cpu_table (cores, model, siblings) VALUES ('" + cores + "', '" + 
            model + "', '" + siblings + "')";
        if (::mysql_query(handle_, query.c_str()) != 0) {
            std::cerr << "CPU 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(handle_) << std::endl;
        }
    }
}

// NIC 데이터 추출 및 저장 함수
void Database::SaveNicToDatabase(const json& nicData) {
    for (const auto& nic : nicData) {
        // 각 nic 정보 추출
        std::string interface = nic["Interface"].get<std::string>();
        std::string mac_address = nic["MAC Address"].get<std::string>();
        std::string operational_state = nic["Operational State"].get<std::string>();
        std::string speed = nic["Speed"].get<std::string>();

        // 쿼리 생성 후 DB에 데이터 저장
        std::string query = "INSERT INTO nic_table (interface, mac_address, operational_state, speed) VALUES ('" + interface + "', '" + 
            mac_address + "', '" + operational_state + "', '" + speed + "')";
        int queryResult = ::mysql_query(handle_, query.c_str());
        if (queryResult != 0) {
            std::cerr << "NIC 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(handle_) << std::endl;
        }
    }
}

// Memory 데이터 추출 및 저장 함수
void Database::SaveMemoryToDatabase(const json& memoryData) {
    for (const auto& memory : memoryData) {
        // 각 memory 정보 추출
        std::string active = memory["Active"].get<std::string>();
        std::string active_anon = memory["Active(anon)"].get<std::string>();
        std::string active_file = memory["Active(file)"].get<std::string>();
        std::string anonHugePages = memory["AnonHugePages"].get<std::string>();
        std::string anonPages = memory["AnonPages"].get<std::string>();
        std::string bounce = memory["Bounce"].get<std::string>();
        std::string buffers = memory["Buffers"].get<std::string>();
        std::string cached = memory["Cached"].get<std::string>();
        std::string cmaFree = memory["CmaFree"].get<std::string>();
        std::string cmaTotal = memory["CmaTotal"].get<std::string>();
        std::string commitLimit = memory["CommitLimit"].get<std::string>();
        std::string committed_AS = memory["Committed_AS"].get<std::string>();
        std::string directMap2M = memory["DirectMap2M"].get<std::string>();
        std::string directMap4k = memory["DirectMap4k"].get<std::string>();
        std::string dirty = memory["Dirty"].get<std::string>();
        std::string fileHugePages = memory["FileHugePages"].get<std::string>();
        std::string filePmdMapped = memory["FilePmdMapped"].get<std::string>();
        std::string hardwareCorrupted = memory["HardwareCorrupted"].get<std::string>();
        std::string hugePages_Free = memory["HugePages_Free"].get<std::string>();
        std::string hugePages_Rsvd = memory["HugePages_Rsvd"].get<std::string>();
        std::string hugePages_Surp = memory["HugePages_Surp"].get<std::string>();
        std::string hugePages_Total = memory["HugePages_Total"].get<std::string>();
        std::string hugepagesize = memory["Hugepagesize"].get<std::string>();
        std::string hugetlb = memory["Hugetlb"].get<std::string>();
        std::string inactive = memory["Inactive"].get<std::string>();
        std::string inactive_anon = memory["Inactive(anon)"].get<std::string>();
        std::string inactive_file = memory["Inactive(file)"].get<std::string>();
        std::string kreclaimable = memory["KReclaimable"].get<std::string>();
        std::string kernelStack = memory["KernelStack"].get<std::string>();
        std::string mapped = memory["Mapped"].get<std::string>();
        std::string memAvailable = memory["MemAvailable"].get<std::string>();
        std::string memFree = memory["MemFree"].get<std::string>();
        std::string memTotal = memory["MemTotal"].get<std::string>();
        std::string mlocked = memory["Mlocked"].get<std::string>();
        std::string nFS_Unstable = memory["NFS_Unstable"].get<std::string>();
        std::string pageTables = memory["PageTables"].get<std::string>();
        std::string percpu = memory["Percpu"].get<std::string>();
        std::string sReclaimable = memory["SReclaimable"].get<std::string>();
        std::string sUnreclaim = memory["SUnreclaim"].get<std::string>();
        std::string shmem = memory["Shmem"].get<std::string>();
        std::string shmemHugePages = memory["ShmemHugePages"].get<std::string>();
        std::string shmemPmdMapped = memory["ShmemPmdMapped"].get<std::string>();
        std::string slab = memory["Slab"].get<std::string>();
        std::string swapCached = memory["SwapCached"].get<std::string>();
        std::string swapFree = memory["SwapFree"].get<std::string>();
        std::string swapTotal = memory["SwapTotal"].get<std::string>();
        std::string unevictable = memory["Unevictable"].get<std::string>();
        std::string vmallocChunk = memory["VmallocChunk"].get<std::string>();
        std::string vmallocTotal = memory["VmallocTotal"].get<std::string>();
        std::string vmallocUsed = memory["VmallocUsed"].get<std::string>();
        std::string writeback = memory["Writeback"].get<std::string>();
        std::string writebackTmp = memory["WritebackTmp"].get<std::string>();
        std::string zswap = memory["Zswap"].get<std::string>();
        std::string zswapped = memory["Zswapped"].get<std::string>();

		// 쿼리 생성 후 DB에 데이터 저장
        std::string query = "INSERT INTO memory_table (active, active_anon, active_file, anonHugePages, anonPages, bounce, buffers, cached, cmaFree, cmaTotal, commitLimit, committed_AS, directMap2M, directMap4k, dirty, fileHugePages, filePmdMapped, hardwareCorrupted, hugePages_Free, hugePages_Rsvd, hugePages_Surp, hugePages_Total, hugepagesize, hugetlb, inactive, inactive_anon, inactive_file, kreclaimable, kernelStack, mapped, memAvailable, memFree, memTotal, mlocked, nFS_Unstable, pageTables, percpu, sReclaimable, sUnreclaim, shmem, shmemHugePages, shmemPmdMapped, slab, swapCached, swapFree, swapTotal, unevictable, vmallocChunk, vmallocTotal, vmallocUsed, writeback, writebackTmp, zswap, zswapped) VALUES ('" + 
            active + "', '" + active_anon + "', '" + active_file + "', '" + anonHugePages + "', '" + anonPages + "', '" + bounce + "', '" + buffers + "', '" + 
            cached + "', '" + cmaFree + "', '" + cmaTotal + "', '" + commitLimit + "', '" + committed_AS + "', '" + directMap2M + "', '" + directMap4k + "', '" + dirty + "', '" + fileHugePages + "', '" + 
            filePmdMapped + "', '" + hardwareCorrupted + "', '" + hugePages_Free + "', '" + hugePages_Rsvd + "', '" + hugePages_Surp + "', '" + hugePages_Total + "', '" + hugepagesize + "', '" + hugetlb + "', '" + 
            inactive + "', '" + inactive_anon + "', '" + inactive_file + "', '" + kreclaimable + "', '" + kernelStack + "', '" + mapped + "', '" + memAvailable + "', '" + memFree + "', '" + memTotal + "', '" + 
            mlocked + "', '" + nFS_Unstable + "', '" + pageTables + "', '" + percpu + "', '" + sReclaimable + "', '" + sUnreclaim + "', '" + shmem + "', '" + shmemHugePages + "', '" + shmemPmdMapped + "', '" + 
            slab + "', '" + swapCached + "', '" + swapFree + "', '" + swapTotal + "', '" + unevictable + "', '" + vmallocChunk + "', '" + vmallocTotal + "', '" + vmallocUsed + "', '" + writeback + "', '" + 
            writebackTmp + "', '" + zswap + "', '" + zswapped + "')";
        int queryResult = ::mysql_query(handle_, query.c_str());
        if (queryResult != 0) {
            std::cerr << "Memory 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(handle_) << std::endl;
        }
    }
}

// Disk 데이터 추출 및 저장 함수
void Database::SaveDiskToDatabase(const json& diskData) {
    for (const auto& disk : diskData) {
        std::string device = disk["Device"].get<std::string>();
        int completed_io_operations = disk["Completed I/O operations"].get<int>();
        int merged_io_operations = disk["Merged I/O operations"].get<int>();
        int time_spent_reading = disk["Time spent reading (ms)"].get<int>();
        int time_spent_writing = disk["Time spent writing (ms)"].get<int>();
        int total_sectors = disk["Total sectors"].get<int>();

        // 쿼리 생성 후 DB에 데이터 저장
        std::stringstream query;
        query << "INSERT INTO disk_table (device, completed_io_operations, merged_io_operations, time_spent_reading, time_spent_writing, total_sectors) VALUES ('"
              << device << "', " << completed_io_operations << ", " << merged_io_operations << ", " << time_spent_reading << ", " << time_spent_writing << ", " << total_sectors << ")";
        int queryResult = ::mysql_query(handle_, query.str().c_str());
        if (queryResult != 0) {
            std::cerr << "Disk 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(handle_) << std::endl;
        }
    }
}