#ifndef CLIENTJSON_H
#define CLIENTJSON_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Json {
    Json();
    ~Json();

    json makeJson();

    private:
        void getCpuData(json &cpudata);
        void getNicData(json &nicdata);
        void getMemoryData(json &memorydata);
        void getDiskData(json &diskdata);
};

#endif