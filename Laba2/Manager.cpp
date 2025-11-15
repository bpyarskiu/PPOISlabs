#include "Manager.hpp"
#include <iostream>

using namespace std;

Manager::Manager(int id, const string& firstName, const string& lastName,
                 const ContactInfo& contact, int employeeId, 
                 const string& position, double salary,
                 const vector<string>& responsibilities,
                 int teamSize, double performanceBonus)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      responsibilities(responsibilities), teamSize(teamSize), 
      performanceBonus(performanceBonus) {
    
    if (responsibilities.empty()) {
        throw invalid_argument("Manager must have at least one responsibility");
    }
}

const vector<string>& Manager::getResponsibilities() const { return responsibilities; }
int Manager::getTeamSize() const { return teamSize; }
double Manager::getPerformanceBonus() const { return performanceBonus; }

void Manager::addResponsibility(const string& responsibility) {
    if (responsibility.empty()) {
        throw invalid_argument("Responsibility cannot be empty");
    }
    responsibilities.push_back(responsibility);
}

double Manager::calculateTotalCompensation() const {
    return getSalary() + performanceBonus;
}

void Manager::displayInfo() const {
    Employee::displayEmployeeInfo();
    cout << "Team Size: " << teamSize << " employees" << endl;
    cout << "Performance Bonus: " << performanceBonus << " RUB" << endl;
    cout << "Total Compensation: " << calculateTotalCompensation() << " RUB" << endl;
    cout << "Responsibilities: ";
    for (const auto& responsibility : responsibilities) {
        cout << responsibility << "; ";
    }
    cout << endl;
}