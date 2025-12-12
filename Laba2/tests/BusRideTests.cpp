#include <UnitTest++/UnitTest++.h>
#include "../BusRide.hpp"
#include "../Route.hpp"
#include "../Price.hpp"
#include "HELPERFILE.cpp"
#include <string>

using namespace std;

TEST(BusRide_Constructor_Valid) {
    Price price(50.0, "USD");
    Route route("Minsk", "Gomel");
    
    BusRide bus(1, "Bus", "Comfort bus with AC", price,
               "AA1234BC", "BelAvto", route,
               true, true, 45);
    
    CHECK_EQUAL("AA1234BC", bus.getBusNumber());
    CHECK_EQUAL("BelAvto", bus.getCompany());
    CHECK_EQUAL(45, bus.getCapacity());
    CHECK(bus.getHasWC());
    CHECK(bus.getHasAirConditioning());
    CHECK_EQUAL(1, bus.getTransportId());
    CHECK_EQUAL("Bus", bus.getType());
}

TEST(BusRide_Constructor_Invalid) {
    Price price(50.0, "USD");
    Route route("A", "B");
    
    // Пустой номер автобуса
    CHECK_THROW(
        BusRide(1, "Bus", "Desc", price, "", "Company", route),
        invalid_argument
    );
    
    // Неположительная вместимость
    CHECK_THROW(
        BusRide(1, "Bus", "Desc", price, "AB1234", "Company", route, false, false, 0),
        invalid_argument
    );
    
    CHECK_THROW(
        BusRide(1, "Bus", "Desc", price, "AB1234", "Company", route, false, false, -10),
        invalid_argument
    );
}

TEST(BusRide_CalculatePrice_NoAmenities) {
    Price price(100.0, "USD");
    Route route("A", "B");
    
    BusRide bus(1, "Bus", "Standard bus", price,
               "BUS001", "Company", route,
               false, false, 40); // без удобств
    
    // 2 пассажира * 100 = 200
    CHECK_EQUAL(200.0, bus.calculatePrice(2));
}

TEST(BusRide_CalculatePrice_WithAmenities) {
    Price price(100.0, "USD");
    Route route("A", "B");
    
    // Только туалет: +5%
    BusRide busWithWC(1, "Bus", "Bus with WC", price,
                     "BUS002", "Company", route,
                     true, false, 40);
    CHECK_CLOSE(210.0, busWithWC.calculatePrice(2), 0.001); // 200 * 1.05 = 210
    
    // Только кондиционер: +10%
    BusRide busWithAC(2, "Bus", "Bus with AC", price,
                     "BUS003", "Company", route,
                     false, true, 40);
    CHECK_CLOSE(220.0, busWithAC.calculatePrice(2), 0.001); // 200 * 1.1 = 220
    
    // Все удобства: +15.5% (1.05 * 1.1 = 1.155)
    BusRide busWithAll(3, "Bus", "Luxury bus", price,
                      "BUS004", "Company", route,
                      true, true, 40);
    CHECK_CLOSE(231.0, busWithAll.calculatePrice(2), 0.001); // 200 * 1.155 = 231
}

TEST(BusRide_GetTransportInfo) {
    Price price(75.0, "EUR");
    Route route("Berlin", "Paris");
    
    BusRide bus(1, "Bus", "International bus", price,
               "EURO001", "EuroLines", route,
               true, true, 55);
    
    string info = bus.getTransportInfo();
    
    // Проверяем наличие ключевых строк
    CHECK(info.find("Transport ID: 1") != string::npos);
    CHECK(info.find("Type: Bus") != string::npos);
    CHECK(info.find("Description: International bus") != string::npos);
    CHECK(info.find("EURO001") != string::npos);
    CHECK(info.find("EuroLines") != string::npos);
    CHECK(info.find("55") != string::npos);
    CHECK(info.find("WC: Yes") != string::npos);
    CHECK(info.find("AC: Yes") != string::npos);
}

TEST(BusRide_DisplayTransportInfo) {
    Price price(60.0, "BYN");
    Route route("Minsk", "Brest");
    
    BusRide bus(1, "Bus", "Local bus", price,
               "BY001", "MinskTrans", route,
               false, true, 35);
    
    StdoutRedirect redirect;
    bus.displayTransportInfo();
    string output = redirect.getOutput();
    
    // Проверяем ключевые элементы вывода
    CHECK(output.find("Transport ID: 1") != string::npos);
    CHECK(output.find("Type: Bus") != string::npos);
    CHECK(output.find("Description: Local bus") != string::npos);
    CHECK(output.find("Bus Number: BY001") != string::npos);
    CHECK(output.find("Company: MinskTrans") != string::npos);
    CHECK(output.find("Capacity: 35 passengers") != string::npos);
    CHECK(output.find("Amenities:") != string::npos);
    CHECK(output.find("Air Conditioning") != string::npos);
}

TEST(BusRide_DisplayTransportInfo_WithAllAmenities) {
    Price price(80.0, "USD");
    Route route("City A", "City B");
    
    BusRide bus(2, "Bus", "Premium service", price,
               "PREMIUM1", "LuxuryLines", route,
               true, true, 20);
    
    StdoutRedirect redirect;
    bus.displayTransportInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Bus Number: PREMIUM1") != string::npos);
    CHECK(output.find("Company: LuxuryLines") != string::npos);
    CHECK(output.find("Capacity: 20 passengers") != string::npos);
    CHECK(output.find("Amenities:") != string::npos);
    CHECK(output.find("WC") != string::npos);
    CHECK(output.find("Air Conditioning") != string::npos);
}

TEST(BusRide_DisplayTransportInfo_NoAmenities) {
    Price price(40.0, "EUR");
    Route route("Start", "End");
    
    BusRide bus(3, "Bus", "Basic bus", price,
               "BASIC01", "BasicCo", route,
               false, false, 50);
    
    StdoutRedirect redirect;
    bus.displayTransportInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Amenities:") != string::npos);
    // Проверяем, что нет упоминаний о удобствах
    CHECK(output.find("WC") == string::npos);
    CHECK(output.find("Air Conditioning") == string::npos);
}

TEST(BusRide_Getters) {
    Price price(80.0, "USD");
    Route route("Start", "End");
    
    BusRide bus(1, "Bus", "Test bus", price,
               "TEST01", "TestCompany", route,
               true, false, 30);
    
    CHECK_EQUAL("TEST01", bus.getBusNumber());
    CHECK_EQUAL("TestCompany", bus.getCompany());
    CHECK_EQUAL(30, bus.getCapacity());
    CHECK(bus.getHasWC());
    CHECK(!bus.getHasAirConditioning());
    
    Route retrievedRoute = bus.getRoute();
    CHECK_EQUAL("Start", retrievedRoute.getStartPoint());
    CHECK_EQUAL("End", retrievedRoute.getEndPoint());
}

TEST(BusRide_CalculatePrice_EdgeCases) {
    Price price(100.0, "USD");
    Route route("A", "B");
    
    BusRide bus(1, "Bus", "Test", price, "BUS001", "Co", route, true, true, 50);
    
    // 0 пассажиров
    CHECK_EQUAL(0.0, bus.calculatePrice(0));
    
    // 1 пассажир
    CHECK_CLOSE(115.5, bus.calculatePrice(1), 0.001); // 100 * 1.155 = 115.5
}
