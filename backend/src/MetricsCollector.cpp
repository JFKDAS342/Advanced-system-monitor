#include <iostream>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <sstream>
#include <string>
#include <sys/statvfs.h>
#include "MetricsCollector.h"
using namespace std;

MetricsCollector::MetricsCollector() : prev_total(0), prev_idle(0) {}
double MetricsCollector::getCPUsage()
{
    ifstream cpu_Usage = ("/proc/stat");
    string line;

    if (!cpu_Usage.is_open())
    {
        cerr << "Ошибка открытия /proc/stat" << endl;
        return 0.0;
    }

    return 99.8;
}

double MetricsCollector::getMemoryUsage()
{
    return 63.33;
}

double MetricsCollector::getDiskUsage()
{
    return 84.44;
}

SystemMetrics MetricsCollector::collectMetrics()
{
    SystemMetrics metrics;

    metrics.cpu_usage = getCPUsage();
    metrics.disk_usage = getDiskUsage();
    metrics.memory_usage = getMemoryUsage();

    return metrics;
}

string MetricsCollector::serializeToJSON()
{
    SystemMetrics metrics = collectMetrics();

    string json = "{";
    json += "\"cpu_usage\": " + to_string(metrics.cpu_usage) + ",";
    json += "\"memory_usage\": " + to_string(metrics.memory_usage) + ",";
    json += "\"disk_usage\": " + to_string(metrics.disk_usage);
    json += "}";
    return json;
}