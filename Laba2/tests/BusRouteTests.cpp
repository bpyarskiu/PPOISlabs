#include <UnitTest++/UnitTest++.h>
#include "../BusRoute.hpp"
#include "../BusStop.hpp"
#include "../Route.hpp"
#include "HELPERFILE.cpp"
#include <memory>
#include <chrono>

using namespace std;
using namespace chrono;

TEST(BusRoute_Constructor_Valid) {
    Route mainRoute("Downtown", "Uptown");
    BusRoute busRoute("Bus 100", mainRoute);
    
    // Проверяем, что объект создан
    CHECK(true); // Или нужен геттер для routeName
}

TEST(BusRoute_AddStop_Valid) {
    Route mainRoute("Start", "End");
    BusRoute busRoute("Bus 200", mainRoute);
    
    auto stop1 = make_shared<BusStop>("Stop 1", "Street 1", minutes(5), 1);
    auto stop2 = make_shared<BusStop>("Stop 2", "Street 2", minutes(3), 2);
    
    busRoute.addStop(stop1);
    busRoute.addStop(stop2);
    
    CHECK_EQUAL(2, busRoute.getTotalStops());
}

TEST(BusRoute_AddStop_Invalid) {
    Route mainRoute("Start", "End");
    BusRoute busRoute("Bus 200", mainRoute);
    
    // Нулевой указатель
    CHECK_THROW(busRoute.addStop(nullptr), invalid_argument);
}

TEST(BusRoute_GetTotalStopTime) {
    Route mainRoute("Start", "End");
    BusRoute busRoute("Bus 300", mainRoute);
    
    auto stop1 = make_shared<BusStop>("Stop 1", "Loc 1", minutes(5), 1);
    auto stop2 = make_shared<BusStop>("Stop 2", "Loc 2", minutes(10), 2);
    auto stop3 = make_shared<BusStop>("Stop 3", "Loc 3", minutes(7), 3);
    
    busRoute.addStop(stop1);
    busRoute.addStop(stop2);
    busRoute.addStop(stop3);
    
    // 5 + 10 + 7 = 22 минуты
    CHECK_EQUAL(22, busRoute.getTotalStopTime().count());
}

TEST(BusRoute_ListAllStops) {
    Route mainRoute("Start", "End");
    BusRoute busRoute("Bus 400", mainRoute);
    
    auto stop1 = make_shared<BusStop>("Terminal", "Main", minutes(15), 1);
    auto stop2 = make_shared<BusStop>("Station", "Center", minutes(5), 2);
    
    busRoute.addStop(stop1);
    busRoute.addStop(stop2);
    
    StdoutRedirect redirect;
    busRoute.listAllStops();
    string output = redirect.getOutput();
    
    CHECK(output.find("Stops on route 'Bus 400':") != string::npos);
    CHECK(output.find("Stop 1: Terminal (Main) - 15 min") != string::npos);
    CHECK(output.find("Stop 2: Station (Center) - 5 min") != string::npos);
}

TEST(BusRoute_DisplayRouteInfo) {
    Route mainRoute("Station A", "Station B");
    BusRoute busRoute("Express Bus", mainRoute);
    
    auto stop1 = make_shared<BusStop>("Stop A", "Location A", minutes(10), 1);
    busRoute.addStop(stop1);
    
    StdoutRedirect redirect;
    busRoute.displayRouteInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== BUS ROUTE ===") != string::npos);
    CHECK(output.find("Route: Express Bus") != string::npos);
    CHECK(output.find("Total stops: 1") != string::npos);
    CHECK(output.find("Total stop time: 10 minutes") != string::npos);
    CHECK(output.find("=================") != string::npos);
}

TEST(BusRoute_DisplayRouteInfo_NoStops) {
    Route mainRoute("Start", "End");
    BusRoute busRoute("Bus 500", mainRoute);
    
    StdoutRedirect redirect;
    busRoute.displayRouteInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Total stops: 0") != string::npos);
    CHECK(output.find("Total stop time: 0 minutes") != string::npos);
}