#include "Company.hpp"
#include <iostream>

using namespace std;

Company::Company(const string& name, int foundationYear, const Address& headquarters)
    : name(name), foundationYear(foundationYear), headquarters(headquarters) {
    
    if (name.empty()) {
        throw invalid_argument("Company name cannot be empty");
    }
    if (foundationYear < 1880 || foundationYear > 2025) {
        throw invalid_argument("Invalid foundation year");
    }
}

string Company::getName() const { return name; }
int Company::getFoundationYear() const { return foundationYear; }
Address Company::getHeadquarters() const { return headquarters; }

const vector<shared_ptr<Employee>>& Company::getEmployees() const { return employees; }
const vector<shared_ptr<Client>>& Company::getClients() const { return clients; }
const vector<shared_ptr<Tour>>& Company::getTours() const { return tours; }
const vector<shared_ptr<Booking>>& Company::getBookings() const { return bookings; }
const vector<shared_ptr<Accommodation>>& Company::getAccommodations() const { return accommodations; }
 const std::vector<std::shared_ptr<Equipment>>& Company::getEquipment() const {return equipment;}
     const std::vector<std::shared_ptr<Complaint>>& Company::getComplaints() const{return complaints;}

void Company::addEmployee(const shared_ptr<Employee>& employee) {
    if (!employee) {
        throw invalid_argument("Cannot add null employee");
    }
    employees.push_back(employee);
}

void Company::addClient(const shared_ptr<Client>& client) {
    if (!client) {
        throw invalid_argument("Cannot add null client");
    }
    clients.push_back(client);
}

void Company::addTour(const shared_ptr<Tour>& tour) {
    if (!tour) {
        throw invalid_argument("Cannot add null tour");
    }
    tours.push_back(tour);
}

void Company::addBooking(const shared_ptr<Booking>& booking) {
    if (!booking) {
        throw invalid_argument("Cannot add null booking");
    }
    bookings.push_back(booking);
}

void Company::addAccommodation(const shared_ptr<Accommodation>& accommodation) {
    if (!accommodation) {
        throw invalid_argument("Cannot add null accommodation");
    }
    accommodations.push_back(accommodation);
}

void Company::addEquipment(const shared_ptr<Equipment>& newEquipment) {
    if (!newEquipment) {
        throw invalid_argument("Cannot add null equipment");
    }
    equipment.push_back(newEquipment);
}

void Company::addComplaint(const shared_ptr<Complaint>& complaint) {
    if (!complaint) {
        throw invalid_argument("Cannot add null complaint");
    }
    complaints.push_back(complaint);
}

void Company::resolveComplaint(int index) {
    if (index >= 0 && index < complaints.size()) {
        complaints[index]->resolve();
    }
}

Equipment* Company::findEquipment(const string& name) {
    for (auto& eq : equipment) {
        if (eq && eq->getName() == name) {
            return eq.get();
        }
    }
    return nullptr;
}

void Company::displayAllEquipment() const {
    cout << "=== COMPANY EQUIPMENT ===" << endl;
    for (const auto& eq : equipment) {
        if (eq) {
            eq->display();
            cout << "---" << endl;
        }
    }
    cout << "=========================" << endl;
}

void Company::displayPendingComplaints() const {
    cout << "=== PENDING COMPLAINTS ===" << endl;
    bool hasPending = false;
    for (const auto& complaint : complaints) {
        if (complaint && !complaint->isResolved()) {
            complaint->display();
            hasPending = true;
        }
    }
    if (!hasPending) {
        cout << "No pending complaints" << endl;
    }
    cout << "==========================" << endl;
}

void Company::displayCompanyInfo() const {
    cout << "=== COMPANY INFORMATION ===" << endl;
    cout << "Name: " << name << endl;
    cout << "Foundation Year: " << foundationYear << endl;
    headquarters.display();
    cout << "Employees: " << employees.size() << endl;
    cout << "Clients: " << clients.size() << endl;
    cout << "Tours: " << tours.size() << endl;
    cout << "Bookings: " << bookings.size() << endl;
    cout << "Accommodations: " << accommodations.size() << endl;
    cout << "Equipment: " << equipment.size() << endl;
    cout << "Complaints: " << complaints.size() << endl;
    
    // Показываем статистику по жалобам
    int resolvedCount = 0;
    for (const auto& complaint : complaints) {
        if (complaint && complaint->isResolved()) {
            resolvedCount++;
        }
    }
    cout << "Resolved complaints: " << resolvedCount << endl;
    cout << "===========================" << endl;
}

void Company::displayAllAccommodations() const {
    cout << "=== ALL ACCOMMODATIONS ===" << endl;
    for (const auto& accommodation : accommodations) {
        if (accommodation) {
            accommodation->displayAccommodationInfo();
            cout << endl;
        }
    }
    cout << "==========================" << endl;
}