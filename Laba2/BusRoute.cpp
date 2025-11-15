#include "BusRoute.hpp"
#include <iostream>

using namespace std;

BusRoute::BusRoute(const string& routeName, const Route& mainRoute)
    : routeName(routeName), mainRoute(mainRoute) {
    
    if (routeName.empty()) {
        throw invalid_argument("Route name cannot be empty");
    }
}

void BusRoute::addStop(const shared_ptr<BusStop>& stop) {
    if (!stop) {
        throw invalid_argument("Cannot add null stop");
    }
    stops.push_back(stop);
}

void BusRoute::displayRouteInfo() const {
    cout << "=== BUS ROUTE ===" << endl;
    cout << "Route: " << routeName << endl;
    mainRoute.displayRouteInfo();
    cout << "Total stops: " << getTotalStops() << endl;
    cout << "Total stop time: " << getTotalStopTime().count() << " minutes" << endl;
    cout << "=================" << endl;
}

int BusRoute::getTotalStops() const {
    return stops.size();
}

chrono::minutes BusRoute::getTotalStopTime() const {
    chrono::minutes total(0);
    for (const auto& stop : stops) {
        total += stop->getStopDuration();
    }
    return total;
}

void BusRoute::listAllStops() const {
    cout << "Stops on route '" << routeName << "':" << endl;
    for (const auto& stop : stops) {
        cout << "- " << stop->getStopSummary() << endl;
    }
}