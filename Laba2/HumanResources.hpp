#pragma once
#include "Employee.hpp"
#include <vector>
#include <string>

class HumanResources : public Employee {
private:
    std::vector<std::string> hrSpecializations;
    int recruitedEmployees;
    double recruitmentBonus;

public:
    HumanResources(int id, const std::string& firstName, const std::string& lastName,
                   const ContactInfo& contact, int employeeId, 
                   const std::string& position, double salary,
                   const std::vector<std::string>& hrSpecializations,
                   int recruitedEmployees, double recruitmentBonus);

    const std::vector<std::string>& getHrSpecializations() const;
    int getRecruitedEmployees() const;
    double getRecruitmentBonus() const;

    void addHrSpecialization(const std::string& specialization);
    double calculateTotalBonus() const;
    void displayInfo() const;
};