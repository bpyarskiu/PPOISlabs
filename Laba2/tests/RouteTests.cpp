#include <UnitTest++/UnitTest++.h>
#include "../Coordinates.hpp"
#include "../Route.hpp"
#include <string>
#include "HELPERFILE.cpp"
using namespace std;
TEST(CoordinatesTest_DistanceCalculation) {
    Coordinates moscow(55.7558, 37.6173);
    Coordinates spb(59.9343, 30.3351);
    
    double distance = moscow.calculateDistance(spb);
    CHECK(distance > 600.); // Расстояние Москва-СПб > 600 км
    CHECK(distance < 700.);
}

TEST(RouteTest_RouteCreation) {
    Route route("Moscow", "Saint Petersburg");
    CHECK_EQUAL(route.getStartPoint(), "Moscow");
    CHECK_EQUAL(route.getEndPoint(), "Saint Petersburg");
    CHECK(!route.getStartPoint().empty());
}
TEST(Route_Constructor_Valid) {
    Route route("Minsk", "Vitebsk", 200);
    
    CHECK_EQUAL("Minsk", route.getStartPoint());
    CHECK_EQUAL("Vitebsk", route.getEndPoint());
    CHECK_EQUAL(200, route.getDistanceKm());
}

TEST(Route_Constructor_Valid_DefaultDistance) {
    Route route("Minsk", "Gomel");
    
    CHECK_EQUAL("Minsk", route.getStartPoint());
    CHECK_EQUAL("Gomel", route.getEndPoint());
    CHECK_EQUAL(0, route.getDistanceKm()); // По умолчанию 0
}

TEST(Route_Constructor_Invalid) {
    // Пустая начальная точка
    CHECK_THROW(Route("", "Vitebsk", 200), invalid_argument);
    
    // Пустая конечная точка
    CHECK_THROW(Route("Minsk", "", 200), invalid_argument);
    
    // Обе точки пустые
    CHECK_THROW(Route("", "", 200), invalid_argument);
    
    // Отрицательное расстояние
    CHECK_THROW(Route("Minsk", "Vitebsk", -100), invalid_argument);
}

TEST(Route_GetRouteDescription) {
    Route route("Berlin", "Paris", 1050);
    
    string expected = "Berlin → Paris (1050 km)";
    CHECK_EQUAL(expected, route.getRouteDescription());
    
    // С нулевым расстоянием
    Route route2("Moscow", "Saint Petersburg");
    string expected2 = "Moscow → Saint Petersburg (0 km)";
    CHECK_EQUAL(expected2, route2.getRouteDescription());
}

TEST(Route_DisplayRouteInfo) {
    Route route("London", "Manchester", 300);
    
    StdoutRedirect redirect;
    route.displayRouteInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Route: London → Manchester (300 km)") != string::npos);
}

TEST(Route_SetDistanceKm_Valid) {
    Route route("Minsk", "Brest");
    CHECK_EQUAL(0, route.getDistanceKm());
    
    route.setDistanceKm(350);
    CHECK_EQUAL(350, route.getDistanceKm());
    
    route.setDistanceKm(0);
    CHECK_EQUAL(0, route.getDistanceKm());
}

TEST(Route_SetDistanceKm_Invalid) {
    Route route("Minsk", "Grodno");
    
    // Отрицательное расстояние
    CHECK_THROW(route.setDistanceKm(-100), invalid_argument);
    
    // Убедимся, что расстояние не изменилось
    CHECK_EQUAL(0, route.getDistanceKm());
}

TEST(Route_Getters) {
    Route route("New York", "Boston", 350);
    
    CHECK_EQUAL("New York", route.getStartPoint());
    CHECK_EQUAL("Boston", route.getEndPoint());
    CHECK_EQUAL(350, route.getDistanceKm());
}