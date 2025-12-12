#include <UnitTest++/UnitTest++.h>
#include "../BusStop.hpp"
#include "HELPERFILE.cpp"
#include <chrono>

using namespace std;
using namespace chrono;

TEST(BusStop_Constructor_Valid) {
    BusStop stop("Central Station", "Main Street", minutes(5), 1);
    
    CHECK_EQUAL("Central Station", stop.getName());
    CHECK_EQUAL("Main Street", stop.getLocation());
    CHECK_EQUAL(5, stop.getStopDuration().count());
    CHECK_EQUAL(1, stop.getSequenceNumber());
}

TEST(BusStop_Constructor_Invalid) {
    // Пустое имя
    CHECK_THROW(BusStop("", "Location", minutes(5), 1), invalid_argument);
    
    // Пустая локация
    CHECK_THROW(BusStop("Name", "", minutes(5), 1), invalid_argument);
    
    // Некорректная продолжительность
    CHECK_THROW(BusStop("Name", "Location", minutes(0), 1), invalid_argument);
    
    // Некорректный порядковый номер
    CHECK_THROW(BusStop("Name", "Location", minutes(5), 0), invalid_argument);
    CHECK_THROW(BusStop("Name", "Location", minutes(5), -1), invalid_argument);
}

TEST(BusStop_IsLongStop) {
    // Короткая остановка
    BusStop shortStop("Stop 1", "Loc 1", minutes(10), 1);
    CHECK(!shortStop.isLongStop());
    
    // Длинная остановка
    BusStop longStop("Stop 2", "Loc 2", minutes(20), 2);
    CHECK(longStop.isLongStop());
    
    // Граничный случай (ровно 15 минут)
    BusStop borderStop("Stop 3", "Loc 3", minutes(15), 3);
    CHECK(!borderStop.isLongStop()); // > 15, а не >=
}

TEST(BusStop_GetStopSummary) {
    BusStop stop("Airport", "Airport Road", minutes(10), 3);
    string expected = "Stop 3: Airport (Airport Road) - 10 min";
    CHECK_EQUAL(expected, stop.getStopSummary());
}

TEST(BusStop_DisplayStopInfo) {
    BusStop stop("Test Stop", "Test Location", minutes(25), 5);
    
    StdoutRedirect redirect;
    stop.displayStopInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Stop #5: Test Stop") != string::npos);
    CHECK(output.find("Location: Test Location") != string::npos);
    CHECK(output.find("Duration: 25 minutes") != string::npos);
    CHECK(output.find("Type: Long stop") != string::npos);
}

TEST(BusStop_DisplayStopInfo_ShortStop) {
    BusStop stop("Short Stop", "Short Street", minutes(5), 2);
    
    StdoutRedirect redirect;
    stop.displayStopInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Stop #2: Short Stop") != string::npos);
    CHECK(output.find("Type: Short stop") != string::npos);
}

TEST(BusStop_Getters) {
    BusStop stop("University", "Campus", minutes(7), 2);
    
    CHECK_EQUAL("University", stop.getName());
    CHECK_EQUAL("Campus", stop.getLocation());
    CHECK_EQUAL(7, stop.getStopDuration().count());
    CHECK_EQUAL(2, stop.getSequenceNumber());
}