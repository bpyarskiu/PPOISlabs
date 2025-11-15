#include <UntiTest++/UnitTest++.h>
#include "../Coordinates.hpp"
#include "../Route.hpp"
TEST(CoordinatesTest, DistanceCalculation) {
    Coordinates moscow(55.7558, 37.6173);
    Coordinates spb(59.9343, 30.3351);
    
    double distance = moscow.distanceTo(spb);
    EXPECT_GT(distance, 600); // Расстояние Москва-СПб > 600 км
    EXPECT_LT(distance, 700);
}

TEST(RouteTest, RouteCreation) {
    Route route("Moscow", "Saint Petersburg");
    EXPECT_EQ(route.getStartPoint(), "Moscow");
    EXPECT_EQ(route.getEndPoint(), "Saint Petersburg");
    EXPECT_FALSE(route.getWaypoints().empty());
}