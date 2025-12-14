#pragma once
#include <string>
#include "ContactInfo.hpp"

class Person  {
private:
    int id;
    std::string firstName;
    std::string lastName;
    ContactInfo contact;

public:
    Person(int id, const std::string& firstName, const std::string& lastName, 
           const ContactInfo& contact);
    
    // Геттеры
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    ContactInfo getContactInfo() const;
    std::string getEmail() const;
    std::string getPhone() const;
    
    // Вспомогательные методы
    std::string getFullName() const;
    void display() const;

private:
    bool validateName(const std::string& name) const;
};