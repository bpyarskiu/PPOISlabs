#pragma once
#include "Company.hpp"
#include <memory>
#include <string>
#include <vector>

class BackupManager {
private:
    std::shared_ptr<Company> company;
    std::string backupDirectory;

public:
    BackupManager(const std::shared_ptr<Company>& company, const std::string& directory = "backups/");
    
    bool createBackup(const std::string& backupName) const;
    void listBackups() const;
    bool restoreBackup(const std::string& backupName) const;
    
    std::vector<std::string> getBackupFiles() const;
    std::string generateBackupFileName(const std::string& backupName) const;
};