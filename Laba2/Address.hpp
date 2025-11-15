#pragma once
#include <string>

class Address {
private:
    std::string street;
    std::string city;
    std::string country;
    std::string postalCode;

public:
    Address(const std::string& street, const std::string& city, 
            const std::string& country, const std::string& postalCode);
    
    // Геттеры
    std::string getStreet() const;
    std::string getCity() const;
    std::string getCountry() const;
    std::string getPostalCode() const;
    
    // Вспомогательные методы
    std::string getFullAddress() const;
    void display() const;

private:
    bool validateAddressComponents() const;
};