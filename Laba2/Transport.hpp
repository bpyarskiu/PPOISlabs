#pragma once
#include "Price.hpp"
#include <string>
#include <memory>

class Transport {
protected:
    int transportId;
    std::string type;
    std::string description;
    Price price;

public:
    Transport(int transportId, const std::string& type, 
                    const std::string& description, const Price& price);
    virtual ~Transport() = default;
    virtual std::string getTransportInfo() const;
    virtual double calculatePrice(int passengers) const;
    int getTransportId() const;
    std::string getType() const;
    std::string getDescription() const;
    Price getPrice() const;
    
    virtual void displayTransportInfo() const;
};