#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include <string>
#include <chrono>   
#include <mutex>    
#include "SystemMetrics.h"
using namespace std;

class MetricsCollector
{
private:
    //Мьютекс - "замок" для защиты общих данных

    //Поток - параллельное выполнение кода

    //Chrono - точная работа со временем

    //Кэширование - сохранение результатов тяжелых операций

    SystemMetrics cached_metrics;//кэшированные данные
    chrono::steady_clock::time_point last_cache_time;//время кэширования
    mutex cache_mutex;//защищает кэщ от одновременного доступа
    static constexpr chrono::seconds CACHE_DURATION{1};//сколько живет кэш(1 секунду)

    // Для расчета CPU usage между замерами
    long prev_total;
    long prev_idle;

public:
    double getCPUUsage();
    double getMemoryUsage();
    double getDiskUsage();
    MetricsCollector();
    SystemMetrics collectMetrics();
    string serializeToJSON();
};

#endif