#include "Logger.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Logger::Logger(const string& filename, bool consoleOutput) 
    : logFileName(filename), consoleOutput(consoleOutput) {}

string Logger::getCurrentTime() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Logger::writeToFile(const string& message) {
    ofstream file(logFileName, ios::app);
    if (file.is_open()) {
        file << message << endl;
        file.close();
    }
}

void Logger::log(LogLevel level, const string& message) {
    string logMessage = "[" + getCurrentTime() + "] [" + levelToString(level) + "] " + message;
    
    if (consoleOutput) {
        cout << logMessage << endl;
    }
    
    writeToFile(logMessage);
}

void Logger::info(const string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::setConsoleOutput(bool enabled) {
    consoleOutput = enabled;
}