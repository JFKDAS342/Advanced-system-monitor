#include "FileLogger.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

FileLogger::FileLogger() : logFilePath("serve.log") {}

FileLogger::~FileLogger() {}

void FileLogger::log(const string& message){
    cout << "message: " << message << endl;
    writeToFile("[INFO] " + message);
}

void FileLogger::logError(const string& error){
    cout << "Error: " << error << endl;
    writeToFile("[ERROR] " + error);
}

// Добавляем недостающий метод writeToFile
void FileLogger::writeToFile(const string& message){
    ofstream file(logFilePath, ios::app);

    if (file.is_open()){
        time_t now = time(0);
        char* dt = ctime(&now); // исправлено: передаем адрес
        // Убираем символ новой строки из ctime (он уже есть в endl)
        string timeStr(dt);
        timeStr.erase(timeStr.find('\n')); // удаляем \n из ctime
        file << timeStr << ": " << message << endl;
        file.close();
    } else {
        cerr << "Cannot open log file: " << logFilePath << endl;
    }
}