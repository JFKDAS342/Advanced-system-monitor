#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include <string>
#include "SystemMetrics.h"
using namespace std;

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