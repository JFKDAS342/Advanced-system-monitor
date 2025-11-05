#include "JSONSerializer.h"
#include <sstream>
#include <string>
using namespace std;

string JSONSerializer::serializeMetrics(const SystemMetrics& metrics) {
    stringstream json;
    json << "{";
    json << "\"cpu_usage\": " << metrics.cpu_usage << ",";
    json << "\"memory_usage\": " << metrics.memory_usage << ",";
    json << "\"disk_usage\": " << metrics.disk_usage;
    json << "}";
    return json.str();
}

string JSONSerializer::serializeError(const string& error) {
    return "{\"error\": \"" + error + "\"}";
}