#include <UnitTest++/UnitTest++.h>
#include "../Accommodation.hpp"
#include "../Address.hpp"
#include "../Coordinates.hpp"
#include "../Rating.hpp"
#include "../Price.hpp"
#include "HELPERFILE.cpp"
#include <memory>

using namespace std;

std::ostream& operator<<(std::ostream& os,  AccommodationType type) {
        switch (type) {
            case AccommodationType::HOTEL: return os << "HOTEL";
            case AccommodationType::HOSTEL: return os << "HOSTEL";
            case AccommodationType::APARTMENT: return os << "APARTMENT";
            case AccommodationType::VILLA: return os << "VILLA";
            default: return os << "UNKNOWN";
        }
    }


TEST(Accommodation_Constructor_Valid) {
    Address address("Main Street", "New York", "USA", "10001");
    Coordinates coordinates(40.7128, -74.0060);
    Price price(200.0, "USD");
    Rating rating(4.5, 100);
    
    Accommodation accommodation(1, "Grand Hotel", address, coordinates,
                                AccommodationType::HOTEL, price, rating, 4);
    
    CHECK_EQUAL(1, accommodation.getAccommodationId());
    CHECK_EQUAL("Grand Hotel", accommodation.getName());
    CHECK_EQUAL(AccommodationType::HOTEL, accommodation.getType());
    CHECK_EQUAL(4, accommodation.getCapacity());
    CHECK_EQUAL(200.0, accommodation.getPricePerNight().getAmount());
    CHECK_EQUAL("USD", accommodation.getPricePerNight().getCurrency());
}

TEST(Accommodation_GetTypeString) {
    Address address("Street", "City", "Country", "12345");
    Coordinates coordinates(0.0, 0.0);
    Price price(100.0, "EUR");
    Rating rating(3.5, 50);
    
    Accommodation hotel(1, "Hotel", address, coordinates,
                        AccommodationType::HOTEL, price, rating, 2);
    CHECK_EQUAL("Hotel", hotel.getTypeString());
    
    Accommodation hostel(2, "Hostel", address, coordinates,
                         AccommodationType::HOSTEL, price, rating, 6);
    CHECK_EQUAL("Hostel", hostel.getTypeString());
    
    Accommodation apartment(3, "Apartment", address, coordinates,
                            AccommodationType::APARTMENT, price, rating, 4);
    CHECK_EQUAL("Apartment", apartment.getTypeString());
    
    Accommodation villa(4, "Villa", address, coordinates,
                        AccommodationType::VILLA, price, rating, 8);
    CHECK_EQUAL("Villa", villa.getTypeString());
}

TEST(Accommodation_CalculateTotalCost_Valid) {
    Address address("Beach Road", "Miami", "USA", "33139");
    Coordinates coordinates(25.7617, -80.1918);
    Price price(150.0, "EUR");
    Rating rating(4.2, 80);
    
    Accommodation accommodation(1, "Beach Resort", address, coordinates,
                                AccommodationType::HOTEL, price, rating, 2);
    
    // 3 ночи * 150 = 450
    Price cost = accommodation.calculateTotalCost(3);
    CHECK_EQUAL(450.0, cost.getAmount());
    CHECK_EQUAL("EUR", cost.getCurrency());
    
    // 1 ночь
    Price cost2 = accommodation.calculateTotalCost(1);
    CHECK_EQUAL(150.0, cost2.getAmount());
    
    // 0 ночей (должно быть исключение)
    CHECK_THROW(accommodation.calculateTotalCost(0), invalid_argument);
    
    // Отрицательное количество ночей
    CHECK_THROW(accommodation.calculateTotalCost(-1), invalid_argument);
}


TEST(Accommodation_DisplayAccommodationInfo) {
    Address address("Park Avenue", "London", "UK", "SW1A 1AA");
    Coordinates coordinates(51.5074, -0.1278);
    Price price(250.0, "GBP");
    Rating rating(4.6, 150);
    
    Accommodation accommodation(1, "Royal Hotel", address, coordinates,
                                AccommodationType::HOTEL, price, rating, 3);
    
    StdoutRedirect redirect;
    accommodation.displayAccommodationInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== ACCOMMODATION ===") != string::npos);
    CHECK(output.find("ID: 1") != string::npos);
    CHECK(output.find("Name: Royal Hotel") != string::npos);
    CHECK(output.find("Type: Hotel") != string::npos);
    CHECK(output.find("Price per night:") != string::npos);
    CHECK(output.find("Capacity: 3 people") != string::npos);
    CHECK(output.find("====================") != string::npos);
}

TEST(Accommodation_DisplayAccommodationInfo_DifferentTypes) {
    Address address("Backpacker Street", "Berlin", "Germany", "10178");
    Coordinates coordinates(52.5200, 13.4050);
    Price price(30.0, "EUR");
    Rating rating(3.8, 120);
    
    Accommodation hostel(1, "Youth Hostel", address, coordinates,
                         AccommodationType::HOSTEL, price, rating, 8);
    
    StdoutRedirect redirect;
    hostel.displayAccommodationInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Type: Hostel") != string::npos);
    
    Accommodation villa(2, "Luxury Villa", address, coordinates,
                        AccommodationType::VILLA, price, rating, 6);
    
    StdoutRedirect redirect2;
    villa.displayAccommodationInfo();
    string output2 = redirect2.getOutput();
    
    CHECK(output2.find("Type: Villa") != string::npos);
}

TEST(Accommodation_Getters) {
    Address address("Sakura Street", "Tokyo", "Japan", "100-0001");
    Coordinates coordinates(35.6762, 139.6503);
    Price price(15000.0, "JPY");
    Rating rating(4.3, 90);
    
    Accommodation accommodation(10, "Tokyo Inn", address, coordinates,
                                AccommodationType::HOTEL, price, rating, 3);
    
    CHECK_EQUAL(10, accommodation.getAccommodationId());
    CHECK_EQUAL("Tokyo Inn", accommodation.getName());
    CHECK_EQUAL(AccommodationType::HOTEL, accommodation.getType());
    CHECK_EQUAL(3, accommodation.getCapacity());
    
    Price retrievedPrice = accommodation.getPricePerNight();
    CHECK_EQUAL(15000.0, retrievedPrice.getAmount());
    CHECK_EQUAL("JPY", retrievedPrice.getCurrency());
    
    // Проверяем, что возвращаемые объекты корректны
    Address retrievedAddress = accommodation.getAddress();
    CHECK_EQUAL("Sakura Street", retrievedAddress.getStreet());
    CHECK_EQUAL("Tokyo", retrievedAddress.getCity());
    
    Coordinates retrievedCoords = accommodation.getCoordinates();
    CHECK_CLOSE(35.6762, retrievedCoords.getLatitude(), 0.0001);
    CHECK_CLOSE(139.6503, retrievedCoords.getLongitude(), 0.0001);
    
    Rating retrievedRating = accommodation.getRating();
    CHECK(retrievedRating.isValid());
}