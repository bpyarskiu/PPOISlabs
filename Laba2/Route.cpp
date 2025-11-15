#include "Route.hpp"
#include <iostream>

using namespace std;

Route::Route(const string& startPoint, const string& endPoint, int distanceKm)
    : startPoint(startPoint), endPoint(endPoint), distanceKm(distanceKm) {
    
    if (startPoint.empty() || endPoint.empty()) {
        throw invalid_argument("Start and end points cannot be empty");
    }
    if (distanceKm < 0) {
        throw invalid_argument("Distance cannot be negative");
    }
}

string Route::getStartPoint() const { return startPoint; }
string Route::getEndPoint() const { return endPoint; }
int Route::getDistanceKm() const { return distanceKm; }

string Route::getRouteDescription() const {
    return startPoint + " → " + endPoint + " (" + to_string(distanceKm) + " km)";
}

void Route::setDistanceKm(int distance) {
    if (distance < 0) {
        throw invalid_argument("Distance cannot be negative");
    }
    distanceKm = distance;
}

void Route::displayRouteInfo() const {
    cout << "Route: " << getRouteDescription() << endl;
}