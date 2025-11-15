#pragma once
#include "BusStop.hpp"
#include "Route.hpp"
#include <vector>
#include <memory>

class BusRoute {
private:
    std::string routeName;
    Route mainRoute;
    std::vector<std::shared_ptr<BusStop>> stops;

public:
    BusRoute(const std::string& routeName, const Route& mainRoute);

    void addStop(const std::shared_ptr<BusStop>& stop);
    void displayRouteInfo() const;
    int getTotalStops() const;
    std::chrono::minutes getTotalStopTime() const;
    void listAllStops() const;
};