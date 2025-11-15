#pragma once
#include "Transport.hpp"
#include "Route.hpp"
#include <string>

class Flight : public Transport {
private:
    std::string flightNumber;
    std::string airline;
    Route route;
    bool hasMeal;
    double baggageAllowance;

public:
    Flight(int transportId, const std::string& type, 
           const std::string& description, const Price& price,
           const std::string& flightNumber, const std::string& airline,
           const Route& route, bool hasMeal = false, 
           double baggageAllowance = 20.0);

    std::string getTransportInfo() const override;
    double calculatePrice(int passengers) const override;
    std::string getFlightNumber() const;
    std::string getAirline() const;
    Route getRoute() const;
    bool getHasMeal() const;
    double getBaggageAllowance() const; 

    void displayTransportInfo() const override;
};