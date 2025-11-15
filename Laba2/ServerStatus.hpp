// ServerStatus.hpp
#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class ServerStatus {
private:
    std::string serverName;
    std::string websiteUrl;
    bool simulateDelay;

public:
    ServerStatus(const std::string& serverName = "Tourism Company Server", 
                 const std::string& websiteUrl = "https://tourism-company.com",
                 bool simulateDelay = true);

    void checkServerStatus() const;
    void checkWebsiteStatus() const;
    void checkDatabaseStatus() const;
    void systemReady() const;
    void startServices() const;
    void stopServices() const;

    // Геттеры
    std::string getServerName() const;
    std::string getWebsiteUrl() const;
};