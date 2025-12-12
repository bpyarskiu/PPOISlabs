#include <UnitTest++/UnitTest++.h>
#include "../Booking.hpp"
#include "../DateRange.hpp"
#include "../Currency.hpp"
#include "../Manager.hpp"
#include "HELPERFILE.cpp"
#include <string>
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace std;

TEST(DateRangeTest_DateRangeCreation) {
    auto now = system_clock::now();
    
    // Создаем диапазон: завтра -> послезавтра + 2 дня
    DateRange dateRange(now + 24h, now + 72h);
    
    // Проверяем что начальная дата раньше конечной
    CHECK(dateRange.getStartDate() < dateRange.getEndDate());
    
    // Проверяем длительность (примерно 2 дня)
    auto duration = dateRange.getEndDate() - dateRange.getStartDate();
    auto days_count = duration_cast<hours>(duration).count() / 24;
    CHECK_EQUAL(2, days_count);  // 72h - 24h = 48h = 2 дня
}

TEST(BookingTest_BookingCreation) {
     auto now = system_clock::now();
      DateRange dateRange(now + 24h, now + 72h);
    ContactInfo info(std::string("john@email.com"),std::string("+375444873445"));
    auto client = std::make_shared<Client>(1, std::string("John"), std::string("Doe"), info,1);
    auto tour = std::make_shared<Tour>(1, std::string("Beach Tour"), std::string("Relaxing beach vacation"),Price(1000.,"RUB"),dateRange);
    vector<string> responsibilities = {"Booking Management"};
    auto manager = make_shared<Manager>(
        2, "Glob", "Galab", info, 112, "Manager", 50000.0,
        responsibilities, 5, 10000.0
    );
    Booking booking(1, client, tour,manager);
    CHECK_EQUAL(booking.getClient()->getContactInfo().getEmail(), std::string("john@email.com"));
    CHECK_EQUAL(booking.getTour()->getName(),std::string("Beach Tour"));
}
TEST(TestBookingPriceCalculation) {
     auto now = system_clock::now();
      DateRange dateRange(now + 24h, now + 72h);
        ContactInfo info(std::string("ilyushka390@gmail.com"),std::string("+375444873445"));
        auto client = std::make_shared<Client>(1, std::string("Jane"), std::string("Smith"), info,2);
        auto tour = std::make_shared<Tour>(1, std::string("City Tour"),std::string("City exploration"),Price(500.,"RUB"),dateRange);
        vector<string> responsibilities = {"Tour Management"};
    auto manager = make_shared<Manager>(
        3, "Alex", "Manager", info, 113, "Tour Manager", 45000.0,
        responsibilities, 3, 5000.0
    );
        Booking booking(1, client, tour, manager);
        
        // Проверяем базовую цену
        CHECK_CLOSE(booking.getTour()->calculateTotalPrice().getAmount(), 500.0, 0.01);


}

TEST(BookingTest_NullPointerChecks) {
    ContactInfo info("test@test.com", "+375291112233");
    auto now = system_clock::now();
    DateRange dateRange(now + 24h, now + 72h);
    
    vector<string> responsibilities = {"Test"};
    auto validManager = make_shared<Manager>(
        1, "Test", "Manager", info, 100, "Test", 30000.0,
        responsibilities, 1, 0.0
    );
    
    auto validClient = make_shared<Client>(1, "Test", "Client", info, 100);
    auto validTour = make_shared<Tour>(1, "Test", "Test", Price(100, "RUB"), dateRange);
    
    // Проверяем исключения при null указателях
    CHECK_THROW(Booking(1, nullptr, validTour, validManager), invalid_argument);
    CHECK_THROW(Booking(1, validClient, nullptr, validManager), invalid_argument);
    CHECK_THROW(Booking(1, validClient, validTour, nullptr), invalid_argument);
  
}

TEST(BookingTest_DisplayInfo) {
    auto now = system_clock::now();
    DateRange dateRange(now + 24h, now + 72h);
    
    ContactInfo info("booking@test.com", "+375291112233");
    auto client = make_shared<Client>(1, "Booking", "Test", info, 200);
    auto tour = make_shared<Tour>(1, "Display Tour", "Test display", Price(750., "RUB"), dateRange);
    
    vector<string> responsibilities = {"Booking Display"};
    auto manager = make_shared<Manager>(
        2, "Display", "Manager", info, 201, "Display Manager", 40000.0,
        responsibilities, 2, 2000.0
    );
    
    Booking booking(1, client, tour, manager);
    
    // Проверяем displayBookingInfo() через StdoutRedirect
    StdoutRedirect redirect;
    booking.displayBookingInfo();
    string output = redirect.getOutput();
    
    CHECK(output.find("Booking ID: 1") != string::npos);
    CHECK(output.find("Client: Booking Test") != string::npos);
    CHECK(output.find("Tour: Display Tour") != string::npos);
    CHECK(output.find("Manager: Display Manager") != string::npos);
}

TEST(BookingTest_GetMethods) {
    auto now = system_clock::now();
    DateRange dateRange(now + 24h, now + 72h);
    
    ContactInfo info("get@test.com", "+375291112233");
    auto client = make_shared<Client>(1, "Get", "Client", info, 300);
    auto tour = make_shared<Tour>(1, "Get Tour", "Get test", Price(300., "RUB"), dateRange);
    
    vector<string> responsibilities = {"Get Test"};
    auto manager = make_shared<Manager>(
        2, "Get", "Manager", info, 301, "Get Manager", 35000.0,
        responsibilities, 1, 1000.0
    );
    
    Booking booking(10, client, tour, manager);
    
    // Проверяем все геттеры
    CHECK_EQUAL(10, booking.getBookingId());
    CHECK_EQUAL("Get Client", booking.getClient()->getFullName());
    CHECK_EQUAL("Get Tour", booking.getTour()->getName());
    CHECK_EQUAL("Get Manager", booking.getManager()->getFullName());
    
    // Проверяем дату (должна быть не позже текущего времени)
    CHECK(booking.getBookingDate() <= system_clock::now());
}