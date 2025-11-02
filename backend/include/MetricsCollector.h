#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include <string>

using namespace std;

struct SystemMetrics
{
    double cpu_usage;
    double memory_usage;
    double disk_usage;
};

class MetricsCollector
{
private:
    double getCPUUsage();
    double getMemoryUsage();
    double getDiskUsage();

    // Для расчета CPU usage между замерами
    long prev_total;
    long prev_idle;

public:
    MetricsCollector();
    SystemMetrics collectMetrics();
    string serializeToJSON();
};

#endif