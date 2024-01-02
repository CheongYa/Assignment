#ifndef SERVERDATABASE_H
#define SERVERDATABASE_H

#include <nlohmann/json.hpp>
#include <string_view>
#include <mutex>
#include <mysql/mysql.h>

using nlohmann::json;

struct Database {
    Database();
    ~Database();

    void SaveToDatabase(std::string_view message);

    private:
        // Connect to MariaDB
        void ConnectToMariaDB();
        void SaveCpuToDatabase(json const& cpuData);
        void SaveNicToDatabase(json const& nicData);
        void SaveMemoryToDatabase(json const& memoryData);
        void SaveDiskToDatabase(json const& diskData);

        // MariaDB connection handle
        std::mutex mutex_;
        struct st_mysql* handle_ = nullptr;
};

#endif