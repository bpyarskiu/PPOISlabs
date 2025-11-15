#include "Flight.hpp"
#include <iostream>

using namespace std;

Flight::Flight(int transportId, const string& type, 
               const string& description, const Price& price,
               const string& flightNumber, const string& airline,
               const Route& route, bool hasMeal, double baggageAllowance)
    : Transport(transportId, type, description, price),
      flightNumber(flightNumber), airline(airline), route(route),
      hasMeal(hasMeal), baggageAllowance(baggageAllowance) {
    
    if (flightNumber.empty()) {
        throw invalid_argument("Flight number cannot be empty");
    }
    if (baggageAllowance < 0) {
        throw invalid_argument("Baggage allowance cannot be negative");
    }
}

string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getAirline() const { return airline; }
Route Flight::getRoute() const { return route; }
bool Flight::getHasMeal() const { return hasMeal; }
double Flight::getBaggageAllowance() const { return baggageAllowance; }

string Flight::getTransportInfo() const {
    string info = Transport::getTransportInfo();
    info += ", Flight: " + flightNumber + ", Airline: " + airline;
    info += ", Baggage: " + to_string(baggageAllowance) + "kg";
    info += hasMeal ? ", Meal: Yes" : ", Meal: No";
    return info;
}

double Flight::calculatePrice(int passengers) const {
   
    double basePrice = Transport::calculatePrice(passengers);
    if (hasMeal) basePrice += 500.0 * passengers; 
    return basePrice;
}

void Flight::displayTransportInfo() const {
    Transport::displayTransportInfo();
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Airline: " << airline << endl;
    cout << "Baggage Allowance: " << baggageAllowance << " kg" << endl;
    cout << "Meal Included: " << (hasMeal ? "Yes" : "No") << endl;
    route.displayRouteInfo();
}