#include "Accommodation.hpp"
#include <iostream>

using namespace std;

Accommodation::Accommodation(int accommodationId, const string& name, 
                             const Address& address, const Coordinates& coordinates,
                             AccommodationType type, const Price& pricePerNight, 
                             const Rating& rating, int capacity)
    : accommodationId(accommodationId), name(name), address(address), 
      coordinates(coordinates), type(type), pricePerNight(pricePerNight), 
      rating(rating), capacity(capacity) {}


int Accommodation::getAccommodationId() const { return accommodationId; }
string Accommodation::getName() const { return name; }
Address Accommodation::getAddress() const { return address; }
AccommodationType Accommodation::getType() const { return type; }
Price Accommodation::getPricePerNight() const { return pricePerNight; }
int Accommodation::getCapacity() const { return capacity; }

Price Accommodation::calculateTotalCost(int nights) const {
    if (nights <= 0) {
        throw invalid_argument("Number of nights must be positive");
    }
    return pricePerNight.multiply(nights);
}

string Accommodation::getTypeString() const {
    switch (type) {
        case AccommodationType::HOTEL: return "Hotel";
        case AccommodationType::HOSTEL: return "Hostel";
        case AccommodationType::APARTMENT: return "Apartment";
        case AccommodationType::VILLA: return "Villa";
        default: return "Unknown";
    }
}
void Accommodation::addRatingVote(double vote) {
    rating.addVote(vote);
}

void Accommodation::displayAccommodationInfo() const {
    cout << "=== ACCOMMODATION ===" << endl;
    cout << "ID: " << accommodationId << endl;
    cout << "Name: " << name << endl;
    cout << "Type: " << getTypeString() << endl;
    address.display();
    coordinates.display();
    rating.display();
    cout << "Price per night: ";
    pricePerNight.display();
    cout << "Capacity: " << capacity << " people" << endl;
    cout << "====================" << endl;
}
