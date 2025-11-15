#include "Statistics.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Statistics::Statistics(const shared_ptr<Company>& company) : company(company) {}

int Statistics::getTotalClients() const {
    return company->getClients().size();
}

int Statistics::getTotalEmployees() const {
    return company->getEmployees().size();
}

int Statistics::getActiveTours() const {
    int count = 0;
    for (const auto& tour : company->getTours()) {
        if (tour && tour->isActive()) {
            count++;
        }
    }
    return count;
}

double Statistics::getAverageTourRating() const {
    double total = 0.0;
    int count = 0;
    
    for (const auto& tour : company->getTours()) {
        if (tour) {
            total += tour->getAverageRating();
            count++;
        }
    }
    
    return count > 0 ? total / count : 0.0;
}

map<string, int> Statistics::getToursByDestination() const {
    map<string, int> destinationCount;
    
    for (const auto& tour : company->getTours()) {
        if (tour) {
            string destination = tour->getDestination();
            destinationCount[destination]++;
        }
    }
    
    return destinationCount;
}

int Statistics::getEquipmentCount() const {
    return company->getEquipment().size();
}

int Statistics::getResolvedComplaintsCount() const {
    int count = 0;
    for (const auto& complaint : company->getComplaints()) {
        if (complaint && complaint->isResolved()) {
            count++;
        }
    }
    return count;
}

void Statistics::displaySummary() const {
    cout << "=== COMPANY STATISTICS ===" << endl;
    cout << "Total Clients: " << getTotalClients() << endl;
    cout << "Total Employees: " << getTotalEmployees() << endl;
    cout << "Active Tours: " << getActiveTours() << endl;
    cout << "Average Tour Rating: " << fixed << setprecision(1) << getAverageTourRating() << "/5" << endl;
    cout << "Total Equipment: " << getEquipmentCount() << endl;
    cout << "Resolved Complaints: " << getResolvedComplaintsCount() << endl;
    cout << "==========================" << endl;
}

void Statistics::displayTourStatistics() const {
    auto toursByDestination = getToursByDestination();
    
    cout << "=== TOUR DESTINATION STATISTICS ===" << endl;
    for (const auto& [destination, count] : toursByDestination) {
        cout << destination << ": " << count << " tours" << endl;
    }
    cout << "===================================" << endl;
}