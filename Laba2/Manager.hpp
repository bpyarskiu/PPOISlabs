#pragma once
#include "Employee.hpp"
#include <vector>
#include <string>

class Manager : public Employee {
private:
    std::vector<std::string> responsibilities;
    int teamSize;
    double performanceBonus;

public:
    Manager(int id, const std::string& firstName, const std::string& lastName,
            const ContactInfo& contact, int employeeId, 
            const std::string& position, double salary,
            const std::vector<std::string>& responsibilities,
            int teamSize, double performanceBonus);

    const std::vector<std::string>& getResponsibilities() const;
    int getTeamSize() const;
    double getPerformanceBonus() const;

    void addResponsibility(const std::string& responsibility);
    double calculateTotalCompensation() const;
    void displayInfo() const;
};