#ifndef HWDATA_H
#define HWDATA_H

#include <iostream>
#include <string>
#include <sqlite3.h>

class HWdata {
public:
    HWdata();
    ~HWdata();

    void startHwDB();

private:
    void logMessage(const std::string& message);
    
    void dropAndCreateDB(sqlite3* db, int rc);

    void saveData(sqlite3* db, int rc);

    void insertOsData(sqlite3* db, int rc);

    void insertCpuData(sqlite3* db, int rc);

    void insertNicData(sqlite3* db, int rc);

    void insertMemoryData(sqlite3* db, int rc);

    sqlite3* db;
    int rc;
};

#endif