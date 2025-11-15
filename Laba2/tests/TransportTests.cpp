#include <UntiTest++/UnitTest++.h>
#include "../BusRide.hpp"
#include "../Flight.hpp"
TEST(TransportTest, BusRideCreation) {
    BusRide bus(1, "Luxury Bus", "Comfortable bus with AC", 
                Price(5000, Currency::RUB), "BUS123", "TransCompany",
                Route("Moscow", "SPB"), true, true, 50);
    
    EXPECT_EQ(bus.getBusNumber(), "BUS123");
    EXPECT_TRUE(bus.getHasAirConditioning());
    EXPECT_EQ(bus.getCapacity(), 50);
}

TEST(TransportTest, FlightCreation) {
    Flight flight(1, "Boeing 737", "International flight",
                  Price(15000, Currency::RUB), "FL456", "AeroFlot",
                  Route("Moscow", "Paris"), true, 23.0);
    
    EXPECT_EQ(flight.getFlightNumber(), "FL456");
    EXPECT_TRUE(flight.getHasMeal());
    EXPECT_DOUBLE_EQ(flight.getBaggageAllowance(), 23.0);
}