#include <iostream>
#include <csignal>
#include <MetricsCollector.h>
#include "WebServer.h"
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <ctime>
using namespace std;
WebServer *g_server = nullptr;

void signalHandler(int signal)
{
    if (g_server)
    {
        g_server->stop();
    }
}

    WebServer server;

int main()
{
    cout << unitbuf;
    time_t now = time(0);
    for (char c : "Loading.."){
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(90));
    }
    cout << "Сервер запустился!\n" << "time" << now << endl;

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