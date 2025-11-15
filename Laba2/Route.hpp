#pragma once
#include <string>

class Route {
private:
    std::string startPoint;
    std::string endPoint;
    int distanceKm;

public:
    Route(const std::string& startPoint, const std::string& endPoint, int distanceKm = 0);
    
    std::string getStartPoint() const;
    std::string getEndPoint() const;
    int getDistanceKm() const;
    std::string getRouteDescription() const;
    
    void setDistanceKm(int distance);
    void displayRouteInfo() const;
};