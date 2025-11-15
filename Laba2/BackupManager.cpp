#include "BackupManager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

using namespace std;

BackupManager::BackupManager(const shared_ptr<Company>& company, const string& directory)
    : company(company), backupDirectory(directory) {
    
    // Создаем директорию для бэкапов, если её нет
    filesystem::create_directories(backupDirectory);
}

bool BackupManager::createBackup(const string& backupName) const {
    string filename = generateBackupFileName(backupName);
    ofstream file(filename);
    
    if (!file.is_open()) {
        return false;
    }
    
    // В реальной системе здесь была бы сериализация данных компании
    file << "Backup: " << backupName << endl;
    file << "Company: " << company->getName() << endl;
    file << "Clients: " << company->getClients().size() << endl;
    file << "Employees: " << company->getEmployees().size() << endl;
    file << "Tours: " << company->getTours().size() << endl;
    file << "Backup created: " << __DATE__ << " " << __TIME__ << endl;
    
    file.close();
    return true;
}

void BackupManager::listBackups() const {
    cout << "=== AVAILABLE BACKUPS ===" << endl;
    
    auto backups = getBackupFiles();
    if (backups.empty()) {
        cout << "No backups found" << endl;
        return;
    }
    
    for (const auto& backup : backups) {
        cout << "- " << backup << endl;
    }
    cout << "=========================" << endl;
}

bool BackupManager::restoreBackup(const string& backupName) const {
    string filename = backupDirectory + backupName;
    
    if (!filesystem::exists(filename)) {
        cout << "Backup file not found: " << filename << endl;
        return false;
    }
    
    // В реальной системе здесь была бы десериализация данных
    cout << "Restoring from backup: " << backupName << endl;
    cout << "Backup restoration simulation completed" << endl;
    return true;
}

vector<string> BackupManager::getBackupFiles() const {
    vector<string> backups;
    
    try {
        for (const auto& entry : filesystem::directory_iterator(backupDirectory)) {
            if (entry.is_regular_file()) {
                backups.push_back(entry.path().filename().string());
            }
        }
    } catch (const filesystem::filesystem_error&) {
        // Директория не существует или нет доступа
    }
    
    return backups;
}

string BackupManager::generateBackupFileName(const string& backupName) const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    
    stringstream ss;
    ss << backupDirectory << "backup_" << backupName << "_" << time << ".txt";
    return ss.str();
}