#ifndef SWDATA_H
#define SWDATA_H

#include <iostream>
#include <sqlite3.h>

class SWdata {
public:
    SWdata();
    ~SWdata();

    void startSwDB();

private:
    void logMessage(const std::string& message);

    void dropAndCreateTable(sqlite3* db, int rc);

    void saveData(sqlite3* db, int rc);

    void insertSwData(sqlite3* db, int rc);

    sqlite3* db;
    int rc;
};

#endif