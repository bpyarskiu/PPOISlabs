#pragma once
#include <string>

class ContactInfo {
private:
    std::string email;
    std::string phone;

public:
    ContactInfo(const std::string& email, const std::string& phone);
    ContactInfo()= default;
    
    // Геттеры
    std::string getEmail() const;
    std::string getPhone() const;
    
    // Вспомогательные методы
    bool isValidEmail() const;
    bool isValidPhone() const;
    void display() const;

private:
    bool validateEmail(const std::string& email) const;
    bool validatePhone(const std::string& phone) const;
};