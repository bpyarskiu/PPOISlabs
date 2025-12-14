#include "Coordinates.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

Coordinates::Coordinates(double latitude, double longitude)
    : latitude(latitude), longitude(longitude) {
    
    if (!validateLatitude(latitude)) {
        throw invalid_argument("Invalid latitude value");
    }
    if (!validateLongitude(longitude)) {
        throw invalid_argument("Invalid longitude value");
    }
}

double Coordinates::getLatitude() const { 
    return latitude; 
}

double Coordinates::getLongitude() const { 
    return longitude; 
}

double Coordinates::calculateDistance(const Coordinates& other) const {
    //Усложненная формула расчета расстояния
    double latDiff = (latitude - other.latitude)/2.;
    double lonDiff = (longitude - other.longitude)/2.;
    return 2.*6371.* asin(sqrt(sin(latDiff*3.1415/180.) * sin(latDiff*3.1415/180.) + cos(latitude*3.1415/180.) * cos(other.latitude*3.1415/180.) * (sin(lonDiff*3.1415/180.))*(sin(lonDiff*3.1415/180.)))); 
}

bool Coordinates::isValid() const {
    return validateLatitude(latitude) && validateLongitude(longitude);
}

void Coordinates::display() const {
    cout << "Coordinates: " << latitude << "°N, " << longitude << "°E" << endl;
}

bool Coordinates::validateLatitude(double latitude) const {
    return latitude >= -90.0 && latitude <= 90.0;
}

bool Coordinates::validateLongitude(double longitude) const {
    return longitude >= -180.0 && longitude <= 180.0;
}