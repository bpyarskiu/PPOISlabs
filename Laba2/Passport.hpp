#pragma once
#include <string>

class Passport {
private:
    std::string number;
    std::string nationality;
    std::string expirationDate;

public:
    Passport(const std::string& number, const std::string& nationality, 
             const std::string& expirationDate);
    
    // Геттеры
    std::string getNumber() const;
    std::string getNationality() const;
    std::string getExpirationDate() const;
    
    // Вспомогательные методы
    bool isValid() const;
    void display() const;

private:
    bool validateNumber(const std::string& number) const;
    bool validateDate(const std::string& date) const;
};