// ServerStatus.cpp
#include "ServerStatus.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

ServerStatus::ServerStatus(const string& serverName, const string& websiteUrl, bool simulateDelay)
    : serverName(serverName), websiteUrl(websiteUrl), simulateDelay(simulateDelay) {}

void ServerStatus::checkServerStatus() const {
    cout << "🖥️  Checking " << serverName << " status..." << endl;
    
    if (simulateDelay) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "   ↳ Initializing server components..." << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    
    cout << "   ✅ " << serverName << " is running on port 8080" << endl;
    cout << "   📊 Memory: 2.4GB/8GB | CPU: 24% | Uptime: 7d 12h" << endl;
}

void ServerStatus::checkWebsiteStatus() const {
    cout << "🌐 Checking website status..." << endl;
    
    if (simulateDelay) {
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    
    cout << "   ✅ Website '" << websiteUrl << "' is online" << endl;
    cout << "   📈 Response time: 124ms | SSL: Valid | Visitors: 342" << endl;
}

void ServerStatus::checkDatabaseStatus() const {
    cout << "🗃️  Checking database connection..." << endl;
    
    if (simulateDelay) {
        this_thread::sleep_for(chrono::milliseconds(600));
    }
    
    cout << "   ✅ Database connection established" << endl;
    cout << "   💾 PostgreSQL 14 | Connections: 24 | Size: 2.3GB" << endl;
}

void ServerStatus::systemReady() const {
    cout << "🎯 " << serverName << " system is fully operational and ready!" << endl;
    cout << "   All services are running normally ✅" << endl;
}

void ServerStatus::startServices() const {
    cout << "🚀 Starting " << serverName << " services..." << endl;
    
    if (simulateDelay) {
        this_thread::sleep_for(chrono::milliseconds(800));
        cout << "   ↳ Loading configuration..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "   ↳ Establishing database connections..." << endl;
        this_thread::sleep_for(chrono::milliseconds(700));
    }
    
    cout << "   ✅ All services started successfully!" << endl;
}

void ServerStatus::stopServices() const {
    cout << "🛑 Stopping " << serverName << " services..." << endl;
    
    if (simulateDelay) {
        this_thread::sleep_for(chrono::milliseconds(600));
    }
    
    cout << "   ✅ Services stopped gracefully" << endl;
}

string ServerStatus::getServerName() const {
    return serverName;
}

string ServerStatus::getWebsiteUrl() const {
    return websiteUrl;
}