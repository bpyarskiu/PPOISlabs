#pragma once
#include "Person.hpp"
#include <string>

class Employee : public Person {
protected:
    int employeeId;
    std::string position;
    double salary;

public:
    Employee(int id, const std::string& firstName, const std::string& lastName, 
                   const ContactInfo& contact, int employeeId, 
                   const std::string& position, double salary);
    
    int getEmployeeId() const;
    std::string getPosition() const;
    double getSalary() const;
    
    virtual void displayInfo() const =0;
};