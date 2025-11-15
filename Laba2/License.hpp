#pragma once
#include <string>

class License {
private:
    std::string number;
    std::string category;
    std::string expirationDate;

public:
    License(const std::string& number, const std::string& category,
            const std::string& expirationDate);
    
    // Геттеры
    std::string getNumber() const;
    std::string getCategory() const;
    std::string getExpirationDate() const;
    
    // Вспомогательные методы
    bool isValid() const;
    bool canDriveCategory(const std::string& requiredCategory) const;
    void display() const;

private:
    bool validateNumber(const std::string& number) const;
};