#include <UnitTest++/UnitTest++.h>
#include "../BusRide.hpp"
#include "../Flight.hpp"
#include "../Currency.hpp"
#include "../Transport.hpp"
#include <string>
#include "HELPERFILE.cpp"
using namespace std;

TEST(TransportTest_BusRideCreation) {
    BusRide bus(1, "Luxury Bus", "Comfortable bus with AC", 
                Price(5000., "RUB"), "BUS123", "TransCompany",
                Route("Moscow", "SPB"), true, true, 50);
    
    CHECK_EQUAL(bus.getBusNumber(), "BUS123");
    CHECK(bus.getHasAirConditioning());
    CHECK_EQUAL(bus.getCapacity(), 50);
}

TEST(TransportTest_FlightCreation) {
    Flight flight(1, "Boeing 737", "International flight",
                  Price(15000., "RUB"), "FL456", "AeroFlot",
                  Route("Moscow", "Paris"), true, 23.0);
    
    CHECK_EQUAL(flight.getFlightNumber(), "FL456");
    CHECK(flight.getHasMeal());
    CHECK_EQUAL(flight.getBaggageAllowance(), 23.0);
}

// Тестовый класс для тестирования абстрактных методов
class TestTransport : public Transport {
public:
    TestTransport(int transportId, const string& type, 
                  const string& description, const Price& price)
        : Transport(transportId, type, description, price) {}
    
    // Переопределяем, если нужно
};

TEST(Transport_Constructor_Valid) {
    Price price(100.0, "USD");
    TestTransport transport(1, "Bus", "Test bus", price);
    
    CHECK_EQUAL(1, transport.getTransportId());
    CHECK_EQUAL("Bus", transport.getType());
    CHECK_EQUAL("Test bus", transport.getDescription());
    CHECK_EQUAL(100.0, transport.getPrice().getAmount());
}

TEST(Transport_Constructor_Invalid) {
    Price price(100.0, "USD");
    
    // Пустой тип
    CHECK_THROW(TestTransport(1, "", "Description", price), invalid_argument);
}

TEST(Transport_GetTransportInfo) {
    Price price(150.0, "EUR");
    TestTransport transport(5, "Train", "High-speed train", price);
    
    string info = transport.getTransportInfo();
    
    CHECK(info.find("Transport ID: 5") != string::npos);
    CHECK(info.find("Type: Train") != string::npos);
    CHECK(info.find("Description: High-speed train") != string::npos);
}

TEST(Transport_CalculatePrice) {
    Price price(50.0, "USD");
    TestTransport transport(1, "Bus", "Test", price);
    
    // 2 пассажира * 50 = 100
    CHECK_EQUAL(100.0, transport.calculatePrice(2));
    
    // 0 пассажиров
    CHECK_EQUAL(0.0, transport.calculatePrice(0));
    
    // 1 пассажир
    CHECK_EQUAL(50.0, transport.calculatePrice(1));
    
    // 10 пассажиров
    CHECK_EQUAL(500.0, transport.calculatePrice(10));
}

TEST(Transport_DisplayTransportInfo) {
    Price price(75.0, "GBP");
    TestTransport transport(3, "Plane", "Commercial flight", price);
    
    StdoutRedirect redirect;
    transport.displayTransportInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Transport ID: 3") != string::npos);
    CHECK(output.find("Type: Plane") != string::npos);
    CHECK(output.find("Description: Commercial flight") != string::npos);
    CHECK(output.find("Price:") != string::npos);
    CHECK(output.find("75") != string::npos);
    CHECK(output.find("GBP") != string::npos);
}

TEST(Transport_Getters) {
    Price price(200.0, "JPY");
    TestTransport transport(10, "Ship", "Cruise liner", price);
    
    CHECK_EQUAL(10, transport.getTransportId());
    CHECK_EQUAL("Ship", transport.getType());
    CHECK_EQUAL("Cruise liner", transport.getDescription());
    
    Price retrievedPrice = transport.getPrice();
    CHECK_EQUAL(200.0, retrievedPrice.getAmount());
    CHECK_EQUAL("JPY", retrievedPrice.getCurrency());
}