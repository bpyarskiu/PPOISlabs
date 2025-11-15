#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Validator.hpp"

class TransportCompany {
private:
    int companyId;
    std::string name;
    std::string contactPhone;
    std::string email;
    std::string address;
    double reliabilityRating;

public:
    TransportCompany(int companyId, const std::string& name,
                     const std::string& contactPhone, const std::string& email,
                     const std::string& address, double reliabilityRating);

    // Геттеры
    int getCompanyId() const;
    std::string getName() const;
    std::string getContactPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
    double getReliabilityRating() const;

    // Сеттеры с валидацией
    void setCompanyId(int companyId);
    void setName(const std::string& name);
    void setContactPhone(const std::string& phone);
    void setEmail(const std::string& email);
    void setAddress(const std::string& address);
    void setReliabilityRating(double rating);

    // Методы
    void displayCompanyInfo() const;

private:
    void validateCompanyData() const;
};