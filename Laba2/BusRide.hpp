#pragma once
#include "Transport.hpp"
#include "Route.hpp"
#include <string>

class BusRide : public Transport {
private:
    std::string busNumber;
    std::string company;
    Route route;
    bool hasWC;
    bool hasAirConditioning;
    int capacity;

public:
    BusRide(int transportId, const std::string& type, 
            const std::string& description, const Price& price,
            const std::string& busNumber, const std::string& company,
            const Route& route, bool hasWC = false, 
            bool hasAirConditioning = false, int capacity = 50);
    std::string getTransportInfo() const override;
    double calculatePrice(int passengers) const override;
    void displayTransportInfo() const override;
    std::string getBusNumber() const;
    std::string getCompany() const;
    Route getRoute() const;
    bool getHasWC() const;
    bool getHasAirConditioning() const;
    int getCapacity() const;
};