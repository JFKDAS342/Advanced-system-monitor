#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <string>
#include "SystemMetrics.h"

using namespace std;

class JSONSerializer {
public:
    
    static string serializeMetrics(const SystemMetrics& metrics);
    static string serializeError(const string& error);
};

#endif