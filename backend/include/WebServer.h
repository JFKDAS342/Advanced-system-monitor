#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <MetricsCollector.h>
using namespace std;

class WebServer
{
private:
    int server_port;
    int server_fd;           // это Файловый дескриптор "— это
                             // уникальный числовой идентификатор, который операционная система назначает каждому открытому файлу, каталогу, сокету или другому потоку ввода-вывода"
    atomic<bool> is_running; // атомарный флаг работы сервера
    MetricsCollector collector;
    string readHTTPRequest(int client_socket);
    void handleClient(int client_socket);

    vector<thread> worker_threads; // вектор рабочих потоков
    mutex log_mutex;               // мьютекс для безопасного вывода в консоль

public:
    WebServer();
    ~WebServer();

    bool start(int port = 8080);
    void stop();

    bool isRunning() const;
};

#endif