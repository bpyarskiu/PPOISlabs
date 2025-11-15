#include "Address.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Address::Address(const string& street, const string& city, 
                 const string& country, const string& postalCode)
    : street(street), city(city), country(country), postalCode(postalCode) {
    
    if (!validateAddressComponents()) {
        throw invalid_argument("Invalid address components");
    }
}

string Address::getStreet() const { return street; }
string Address::getCity() const { return city; }
string Address::getCountry() const { return country; }
string Address::getPostalCode() const { return postalCode; }

string Address::getFullAddress() const {
    return street + ", " + city + ", " + country + " " + postalCode;
}

void Address::display() const {
    cout << "Address: " << getFullAddress() << endl;
}

bool Address::validateAddressComponents() const {
    return !street.empty() && !city.empty() && !country.empty();
}