#include <iostream>
#include <csignal>
#include <MetricsCollector.h>
#include "WebServer.h"
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
using namespace std;
WebServer *g_server = nullptr;

void signalHandler(int signal)
{
    if (g_server)
    {
        g_server->stop();
    }
}

int main()
{
    cout << unitbuf;
    chdir("/home/ilya/Advanced-system-monitor/backend");

    cout << "server work" << endl;
    WebServer server;
    g_server = &server;
    // настройка обработчиков сигнал
    signal(SIGINT, signalHandler);  // ctrl+c
    signal(SIGTERM, signalHandler); // kill

    if (server.start(8080))
    {
        while (server.isRunning())
        {
        }
    }

    cout << "Goodbye" << endl;
    return 0;
}