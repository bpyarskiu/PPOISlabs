#pragma once
#include "Employee.hpp"
#include <vector>
#include <string>

class Consultant : public Employee {
private:
    std::vector<std::string> specializationAreas;
    int successfulBookings;
    double commissionRate;

public:
    Consultant(int id, const std::string& firstName, const std::string& lastName, 
               const ContactInfo& contact, int employeeId, 
               const std::string& position, double salary,
               const std::vector<std::string>& specializationAreas,
               int successfulBookings, double commissionRate);

    const std::vector<std::string>& getSpecializationAreas() const;
    int getSuccessfulBookings() const;
    double getCommissionRate() const;

    void addSpecializationArea(const std::string& area);
    double calculateCommission() const;
    void displayInfo() const;
};