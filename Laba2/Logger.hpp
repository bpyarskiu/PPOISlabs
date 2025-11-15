#pragma once
#include <string>
#include <fstream>
#include <chrono>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    std::string logFileName;
    bool consoleOutput;

    std::string getCurrentTime() const;
    std::string levelToString(LogLevel level) const;
    void writeToFile(const std::string& message);

public:
    Logger(const std::string& filename = "company_log.txt", bool consoleOutput = true);
    
    void log(LogLevel level, const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    
    void setConsoleOutput(bool enabled);
};