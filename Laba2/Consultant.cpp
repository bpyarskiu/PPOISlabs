#include "Consultant.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Consultant::Consultant(int id, const string& firstName, const string& lastName, 
                       const ContactInfo& contact, int employeeId, 
                       const string& position, double salary,
                       const vector<string>& specializationAreas,
                       int successfulBookings, double commissionRate)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      specializationAreas(specializationAreas),
      successfulBookings(successfulBookings), commissionRate(commissionRate) {
    
    if (specializationAreas.empty()) {
        throw invalid_argument("Consultant must have at least one specialization area");
    }
    if (successfulBookings < 0) {
        throw invalid_argument("Successful bookings cannot be negative");
    }
}

const vector<string>& Consultant::getSpecializationAreas() const { 
    return specializationAreas; 
}

int Consultant::getSuccessfulBookings() const { return successfulBookings; }
double Consultant::getCommissionRate() const { return commissionRate; }

void Consultant::addSpecializationArea(const string& area) {
    if (area.empty()) {
        throw invalid_argument("Specialization area cannot be empty");
    }
    if (find(specializationAreas.begin(), specializationAreas.end(), area) == specializationAreas.end()) {
        specializationAreas.push_back(area);
    }
}

double Consultant::calculateCommission() const {
    return getSalary() * commissionRate * successfulBookings;
}

void Consultant::displayInfo() const {
    display();
     cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
    cout << "Specialization Areas: ";
    for (const auto& area : specializationAreas) {
        cout << area << ", ";
    }
    cout << endl << "Successful Bookings: " << successfulBookings << endl;
    cout << "Commission Rate: " << (commissionRate * 100) << "%" << endl;
    cout << "Monthly Commission: " << calculateCommission() << " RUB" << endl;
}