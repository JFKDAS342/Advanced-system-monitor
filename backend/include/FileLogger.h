#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <string>

using namespace std;
class FileLogger{
    private:
        string logFilePath;
        void writeToFile(const string& message);
    public:
    FileLogger();
    ~FileLogger();

    void log(const string& message);
    void logError(const string& error);


};


#endif