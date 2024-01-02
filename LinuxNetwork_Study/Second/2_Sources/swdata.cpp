#include "swdata.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sqlite3.h>

SWdata::SWdata() {
    // SQLite database 연결
    rc = sqlite3_open("main.db", &db);
    logMessage("main.db와 연결하였습니다. #SW");

    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

SWdata::~SWdata() {
    // SQLite database 종료
    sqlite3_close(db);
}

void SWdata::logMessage(const std::string& message) {
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

void SWdata::startSwDB() {
    dropAndCreateTable(db, rc);
    saveData(db, rc);
}

// 테이블 삭제 후 재생성 함수
void SWdata::dropAndCreateTable(sqlite3* db, int rc) {
    logMessage("deb와 rpm 테이블을 삭제하였습니다. #SW");
    const char* drop_table_query =
        "DROP TABLE IF EXISTS deb_table;"
        "DROP TABLE IF EXISTS rpm_table";

    rc = sqlite3_exec(db, drop_table_query, 0, 0, 0);

    // 동일한 테이블이 없으면 생성
    const char* create_table_query =
        "CREATE TABLE IF NOT EXISTS deb_table ("
        "    id INTEGER PRIMARY KEY,"
        "    name TEXT,"
        "    version TEXT,"
        "    install_date TEXT,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE TABLE IF NOT EXISTS rpm_table ("
        "    id INTEGER PRIMARY KEY,"
        "    name TEXT,"
        "    version TEXT,"
        "    install_date TEXT,"
        "    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");";

    rc = sqlite3_exec(db, create_table_query, 0, 0, 0);

    if (rc) {
        logMessage("deb와 rpm 테이블 생성에 실패하였습니다. #SW");
        std::cerr << "Cannot create table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
    logMessage("deb와 rpm 테이블을 생성하였습니다. #SW");
}

// transaction과 commit을 이용해 한 번에 DB에 넣는 함수 (실질적인 저장이 이뤄짐)
void SWdata::saveData(sqlite3* db, int rc) {
    // transaction 실행
    rc = sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

    insertSwData(db, rc);

    // Commit transaction
    rc = sqlite3_exec(db, "COMMIT", 0, 0, 0);
    logMessage("main.db에 정보를 저장하였습니다. #SW");
}

// SW의 정보를 읽어 Insert 쿼리문에 담는 함수
void SWdata::insertSwData(sqlite3* db, int rc) {
    logMessage("deb 정보를 DB에 저장할 준비를 시작합니다. #SW");
    // 파일에서 읽어올 문자열
    std::ifstream input_file("/var/log/dpkg.log");

    if (!input_file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        exit(1);
    }

    std::string line;

    // 파일에서 한 줄씩 읽어오기
    while (std::getline(input_file, line)) {
        // 해당 줄에 "install " 문자열이 포함되어 있는지 확인
        if (line.find("install ") != std::string::npos) {
            // 문자열을 띄워쓰기(space)를 기준으로 나누기
            std::istringstream iss(line);
            std::string split_parts[10];

            for (int i = 0; i < 10; ++i) {
                iss >> split_parts[i];
            }

            // 나뉜 부분을 각각의 변수에 할당
            std::string install_date = split_parts[0] + " " + split_parts[1];
            std::string name = split_parts[3];
            std::string version = split_parts[5];

            // Insert 쿼리문 작성
            std::ostringstream insert_query;
            insert_query << "INSERT INTO deb_table (name, version, install_date) VALUES ('"
                         << name << "', '"
                         << version << "', '"
                         << install_date << "');";

            rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

            if (rc) {
                std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
            }
        }
        else if (line.find("status installed") != std::string::npos || line.find("status half-install") != std::string::npos) {
            // 문자열을 띄워쓰기(space)를 기준으로 나누기
            std::istringstream iss(line);
            std::string split_parts[10];

            for (int i = 0; i < 10; ++i) {
                iss >> split_parts[i];
            }

            // 나뉜 부분을 각각의 변수에 할당
            std::string install_date = split_parts[0] + " " + split_parts[1];
            std::string name = split_parts[4];
            std::string version = split_parts[5];

            // Insert 쿼리문 작성
            std::ostringstream insert_query;
            insert_query << "INSERT INTO deb_table (name, version, install_date) VALUES ('"
                         << name << "', '"
                         << version << "', '"
                         << install_date << "');";

            rc = sqlite3_exec(db, insert_query.str().c_str(), 0, 0, 0);

            if (rc) {
                std::cerr << "Cannot insert data: " << sqlite3_errmsg(db) << std::endl;
            }
        }
    }
    input_file.close();
}


