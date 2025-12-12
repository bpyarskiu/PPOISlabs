#include "HumanResources.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

HumanResources::HumanResources(int id, const string& firstName, const string& lastName,
                               const ContactInfo& contact, int employeeId, 
                               const string& position, double salary,
                               const vector<string>& hrSpecializations,
                               int recruitedEmployees, double recruitmentBonus)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      hrSpecializations(hrSpecializations), recruitedEmployees(recruitedEmployees),
      recruitmentBonus(recruitmentBonus) {
    
    if (hrSpecializations.empty()) {
        throw invalid_argument("HR must have at least one specialization");
    }
    if (recruitedEmployees < 0) {
        throw invalid_argument("Recruited employees cannot be negative");
    }
}

const vector<string>& HumanResources::getHrSpecializations() const { return hrSpecializations; }
int HumanResources::getRecruitedEmployees() const { return recruitedEmployees; }
double HumanResources::getRecruitmentBonus() const { return recruitmentBonus; }

void HumanResources::addHrSpecialization(const string& specialization) {
    if (specialization.empty()) {
        throw invalid_argument("HR specialization cannot be empty");
    }
    if (find(hrSpecializations.begin(), hrSpecializations.end(), specialization) == hrSpecializations.end()) {
        hrSpecializations.push_back(specialization);
    }
}

double HumanResources::calculateTotalBonus() const {
    return recruitmentBonus * recruitedEmployees;
}

void HumanResources::displayInfo() const {
    display();
     cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
    cout << "HR Specializations: ";
    for (const auto& specialization : hrSpecializations) {
        cout << specialization << ", ";
    }
    cout << endl << "Recruited Employees: " << recruitedEmployees << endl;
    cout << "Recruitment Bonus per Employee: " << recruitmentBonus << " RUB" << endl;
    cout << "Total Bonus: " << calculateTotalBonus() << " RUB" << endl;
}