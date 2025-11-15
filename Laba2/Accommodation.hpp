#pragma once
#include "Address.hpp"
#include "Price.hpp"
#include "Coordinates.hpp"
#include "Rating.hpp"
#include <string>
#include <memory>

enum class AccommodationType {
    HOTEL,
    HOSTEL, 
    APARTMENT,
    VILLA
};

class Accommodation {
private:
    int accommodationId;
    std::string name;
    Address address;
    Coordinates coordinates;
    AccommodationType type;
    Price pricePerNight;
    Rating rating;
    int capacity;

public:
    Accommodation(int accommodationId, const std::string& name, 
                  const Address& address, const Coordinates& coordinates,
                  AccommodationType type, const Price& pricePerNight, 
                  const Rating& rating, int capacity = 2);
    
    int getAccommodationId() const;
    std::string getName() const;
    Address getAddress() const;
    Coordinates getCoordinates() const;
    AccommodationType getType() const;
    Price getPricePerNight() const;
    Rating getRating() const;
    int getCapacity() const;
    
    void addRatingVote(double vote);
    Price calculateTotalCost(int nights) const;
    std::string getTypeString() const;
    void displayAccommodationInfo() const;
};