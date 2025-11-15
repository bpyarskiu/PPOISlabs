#include "BusRide.hpp"
#include <iostream>

using namespace std;

BusRide::BusRide(int transportId, const string& type, 
                 const string& description, const Price& price,
                 const string& busNumber, const string& company,
                 const Route& route, bool hasWC, 
                 bool hasAirConditioning, int capacity)
    : Transport(transportId, type, description, price),
      busNumber(busNumber), company(company), route(route),
      hasWC(hasWC), hasAirConditioning(hasAirConditioning), capacity(capacity) {
    
    if (busNumber.empty()) {
        throw invalid_argument("Bus number cannot be empty");
    }
    if (capacity <= 0) {
        throw invalid_argument("Capacity must be positive");
    }
}

string BusRide::getBusNumber() const { return busNumber; }
string BusRide::getCompany() const { return company; }
Route BusRide::getRoute() const { return route; }
bool BusRide::getHasWC() const { return hasWC; }
bool BusRide::getHasAirConditioning() const { return hasAirConditioning; }
int BusRide::getCapacity() const { return capacity; }

string BusRide::getTransportInfo() const {
    string info = Transport::getTransportInfo();
    info += ", Bus: " + busNumber + ", Company: " + company + ", Capacity: " + to_string(capacity);
    info += hasWC ? ", WC: Yes" : ", WC: No";
    info += hasAirConditioning ? ", AC: Yes" : ", AC: No";
    return info;
}

double BusRide::calculatePrice(int passengers) const {
    double basePrice = Transport::calculatePrice(passengers);
    if (hasAirConditioning) basePrice *= 1.1;
    if (hasWC) basePrice *= 1.05;
    return basePrice;
}

void BusRide::displayTransportInfo() const {
    Transport::displayTransportInfo();
    cout << "Bus Number: " << busNumber << endl;
    cout << "Company: " << company << endl;
    cout << "Capacity: " << capacity << " passengers" << endl;
    cout << "Amenities: ";
    cout << (hasWC ? "WC " : "");
    cout << (hasAirConditioning ? "Air Conditioning " : "");
    cout << endl;
    route.displayRouteInfo();
}
