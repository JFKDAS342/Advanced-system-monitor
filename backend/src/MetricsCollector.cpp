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

double MetricsCollector::getCPUUsage()
{
    cout << "=== DEBUG: getCPUUsage() called ===" << endl;
    ifstream cpu_Usage("/proc/stat");
    string line;

    if (!cpu_Usage.is_open())
    {
        cerr << "Ошибка открытия /proc/stat" << endl;
        return 0.0;
    }

    if (getline(cpu_Usage, line))
    {
        cout << "=== DEBUG: First line of /proc/stat: " << line << endl;

        istringstream iss(line);
        string cpu_label;
        long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;

        iss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        // ✅ ИСПРАВЛЕНО: правильная проверка ошибок
        if (iss.fail())
        {
            cerr << "Ошибка чтения значений CPU!" << endl;
            return 0.0;
        }

        cout << "=== DEBUG: cpu_label = '" << cpu_label << "'" << endl;
        cout << "=== DEBUG: user = " << user << ", idle = " << idle << endl;

        if (cpu_label == "cpu")
        {
            // Вычисляем общее время работы
            long total = user + nice + system + idle + iowait + irq + softirq + steal;
            long total_idle = idle + iowait;

            cout << "=== DEBUG: total = " << total << ", total_idle = " << total_idle << endl;
            cout << "=== DEBUG: prev_total = " << prev_total << ", prev_idle = " << prev_idle << endl;

            // Если это первый вызов просто сохраняем значения
            if (prev_total == 0 || prev_idle == 0)
            {
                prev_total = total;
                prev_idle = total_idle;
                cout << "=== DEBUG: First call, returning 0.0" << endl;
                return 1.0; // первый вызов не может дать процент
            }

            // Вычисляем разницу с предыдущим замером
            long diff_total = total - prev_total;
            long diff_idle = total_idle - prev_idle;

            // Сохраняем значения для следующего вызова
            prev_total = total;
            prev_idle = total_idle;

            // Вычисляем процент
            if (diff_total > 0)
            {
                double usage = 100.0 * (diff_total - diff_idle) / diff_total;
                cout << "=== DEBUG CPU Usage: " << usage << "% ===" << endl;
                return usage;
            }
            else
            {
                cout << "=== DEBUG: diff_total <= 0" << endl;
            }
        }
        else
        {
            cout << "=== DEBUG: cpu_label is not 'cpu', it's '" << cpu_label << "'" << endl;
        }
    }
    else
    {
        cerr << "Не удалось прочитать первую строку /proc/stat" << endl;
    }

    cout << "=== DEBUG: getCPUUsage() returning 0.0" << endl;
    return 0.0;
}

double MetricsCollector::getMemoryUsage()
{
    cout << "=== DEBUG: getMemoryUsage() called ===" << endl;
    ifstream memory_Usage("/proc/meminfo");
    string line;
    long mem_total = 0, mem_available = 0;
    if (!memory_Usage.is_open())
    {
        cerr << "ошибка открытия /proc/meminfo" << endl;
        return 0.0;
    }
    while (getline(memory_Usage, line))
    {
        if (line.find("MemTotal:") == 0)
        {
            // извлекаем число после meminfo
            sscanf(line.c_str(), "MemTotal: %ld kB", &mem_total);
            cout << "DEBUG MemTotal: " << mem_total << " kB" << endl;
        }
        else if (line.find("MemAvailable:") == 0)
        {
            // извлекаем число после  memavailable
            sscanf(line.c_str(), "MemAvailable: %ld kB", &mem_available);
            cout << "DEBUG MemAvailable: " << mem_available << " kB" << endl;
        }
    }
    memory_Usage.close();

    if (mem_total > 0 && mem_available > 0)
    {
        long used_memory = mem_total - mem_available;
        double usage = 100.0 * used_memory / mem_total;
        cout << "DEBUG Memory Usage: " << usage << "%" << endl;
        return usage;
    }
    cout << "DEBUG Memory: total=" << mem_total << ", available=" << mem_available << endl;
    return 0.0;
}

double MetricsCollector::getDiskUsage()
{
    cout << "=== DEBUG: getDiskUsage() called ===" << endl;
    struct statvfs buf;

    if (statvfs("/", &buf) == 0)
    {
        // вычисляем общее и свободное время
        unsigned long total_blocks = buf.f_blocks;
        unsigned long free_blocks = buf.f_bfree;
        unsigned long block_size = buf.f_frsize;

        // Вычисляем в байтах
        double total_space = total_blocks * block_size;
        double free_space = free_blocks * block_size;
        double used_space = total_space - free_space;

        if (total_space > 0)
        {
            double usage = 100.0 * used_space / total_space;
            cout << "DEBUG Usage disk: " << usage << "%" << endl;
            return usage;
        }
    }
    else
    {
        cerr << "Ошибка получения статистики файловой системы" << endl;
    }

    return 0.0;
}

SystemMetrics MetricsCollector::collectMetrics()
{
    SystemMetrics metrics;

    metrics.cpu_usage = getCPUUsage();
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