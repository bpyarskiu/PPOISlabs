#include "Employee.hpp"
#include <iostream>

using namespace std;

Employee::Employee(int id, const string& firstName, const string& lastName, 
                   const ContactInfo& contact, int employeeId, 
                   const string& position, double salary)
    : Person(id, firstName, lastName, contact), 
      employeeId(employeeId), position(position), salary(salary) {
    
    if (position.empty()) {
        throw invalid_argument("Position cannot be empty");
    }
    if (salary < 0) {
        throw invalid_argument("Salary cannot be negative");
    }
}

int Employee::getEmployeeId() const { return employeeId; }
string Employee::getPosition() const { return position; }
double Employee::getSalary() const { return salary; }

void Employee::displayEmployeeInfo() const {
    display();
    cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
}