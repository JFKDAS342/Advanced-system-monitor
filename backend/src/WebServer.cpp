#include "WebServer.h"
#include "MetricsCollector.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// КОНСТРУКТОР - инициализация переменных
WebServer::WebServer() : server_port(0), server_fd(-1), is_running(false) {}

// ДЕСТРУКТОР - автоматически вызывается при удалении объекта
WebServer::~WebServer()
{
    stop();
}

// ЧТЕНИЕ HTTP ЗАПРОСА ОТ КЛИЕНТА
string WebServer::readHTTPRequest(int client_socket)
{
    char buffer[4096] = {0}; // Буфер для данных
    // read - системный вызов для чтения из сокета
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0)
    {
        cout << "Получен запрос: " << buffer << endl;
        return string(buffer, bytes_read); // Преобразуем char[] в string
    }
    return ""; // Возвращаем пустую строку при ошибке
}

void WebServer::handleClient(int client_socket)
{
    string request = readHTTPRequest(client_socket);

    if (request.empty())
    {
        close(client_socket);
        return;
    }

    string response;
    string content_type;
    string status_line = "HTTP/1.1 200 OK\r\n";

    if (request.find("GET /api/hello") != string::npos)
    {
        response = "{\"message\": \"Hello API\", \"status\": \"success\"}";
        content_type = "application/json";
    }
    else if (request.find("GET /api/metrics") != string::npos)
    {
        MetricsCollector collector;
        response = collector.serializeToJSON();
        content_type = "application/json";
    }
    else if (request.find("GET / ") != string::npos ||
             request.find("GET / HTTP") != string::npos ||
             request.find("GET /") == 0)
    {
        response = "<!DOCTYPE html><html><head><title>System Monitor</title></head>"
                   "<body><h1>System Monitor</h1><p>Server is running!</p></body></html>";
        content_type = "text/html; charset=utf-8";
    }
    else
    {
        response = "404 - Page Not Found";
        content_type = "text/plain; charset=utf-8";
        status_line = "HTTP/1.1 404 Not Found\r\n";
    }

    string http_response =
        status_line +
        "Content-Type: " + content_type + "\r\n" +
        "Content-Length: " + to_string(response.length()) + "\r\n" +
        "Cache-Control: no-cache, no-store, must-revalidate\r\n" +
        "Pragma: no-cache\r\n" +
        "Expires: 0\r\n" +
        "Connection: close\r\n"
        "\r\n" +
        response;

    send(client_socket, http_response.c_str(), http_response.length(), 0);
    close(client_socket);
}

bool WebServer::start(int port)
{
    server_port = port;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        cerr << "Ошибка создания сервера!" << endl;
        return false;
    }

    // НАСТРОЙКА АДРЕСА
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // ПРИВЯЗКА СОКЕТА
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        cerr << "Ошибка привязки" << endl;
        close(server_fd);
        return false;
    }

    cout << "Сокет успешно настроен" << endl;

    // ПРОСЛУШИВАНИЕ ПОРТА
    if (listen(server_fd, 10) < 0)
    {
        cerr << "Ошибка при прослушивании" << endl;
        close(server_fd);
        return false;
    }

    cout << "Сервер слушает на порту " << port << endl;
    is_running = true;

    while (is_running)
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket < 0)
        {
            if (is_running)
            {
                cerr << "Ошибка принятия соединения" << endl;
            }
            continue;
        }

        cout << "Новое соединение принято!" << endl;
        handleClient(client_socket); // Обрабатываем клиента
    }

    close(server_fd);
    return true;
}

void WebServer::stop()
{
    if (is_running)
    {
        is_running = false;
        close(server_fd);
        cout << "Сервер остановлен" << endl;
    }
}

bool WebServer::isRunning() const
{
    return is_running;
}