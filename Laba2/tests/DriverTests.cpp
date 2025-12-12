#include <UnitTest++/UnitTest++.h>
#include "../Driver.hpp"
#include "../License.hpp"
#include "../ContactInfo.hpp"
#include "../Address.hpp"
#include "HELPERFILE.cpp"
#include <string>
#include <iostream>

using namespace std;


TEST(DriverTest_VehiclePermission) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus", "Minivan", "Car"};
    auto license = std::make_shared<License>("DL123456", "D", "2025-12-31");
    
    Driver driver(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                 "D", permittedVehicles, 5, 4.8, license);
    
    // Тест canDriveVehicle с разрешенными типами
    CHECK(driver.canDriveVehicle("Bus"));
    CHECK(driver.canDriveVehicle("Minivan"));
    CHECK(driver.canDriveVehicle("Car"));
    
    // Тест canDriveVehicle с запрещенными типами
    CHECK(!driver.canDriveVehicle("Truck"));
    CHECK(!driver.canDriveVehicle("Motorcycle"));
}

TEST(DriverTest_LicenseValidation) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus"};
    
    // Тест с валидной лицензией
    auto validLicense = std::make_shared<License>("DL123456", "D", "2025-12-31");
    Driver driverValid(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                      "D", permittedVehicles, 5, 4.8, validLicense);
    CHECK(driverValid.hasValidLicense());
    
    // Тест с просроченной лицензией
    auto expiredLicense = std::make_shared<License>("DL123457", "D", "EXPIRED");
    Driver driverExpired(2, "Jane", "Driver", contact, 2002, "Bus Driver", 50000.0,
                        "D", permittedVehicles, 3, 4.5, expiredLicense);
    CHECK(!driverExpired.hasValidLicense());
    
    // Тест без лицензии
    Driver driverNoLicense(3, "Bob", "Driver", contact, 2003, "Bus Driver", 50000.0,
                          "D", permittedVehicles, 2, 4.2, nullptr);
    CHECK(!driverNoLicense.hasValidLicense());
}

TEST(DriverTest_SafetyRatingImprovement) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus"};
    
    Driver driver(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                 "D", permittedVehicles, 5, 4.5, nullptr);
    
    // Тест completeTrip - улучшение рейтинга
    double initialRating = driver.getSafetyRating();
    driver.completeTrip();
    CHECK(driver.getSafetyRating() > initialRating);
    
    // Тест что рейтинг не превышает максимум
    Driver maxRatingDriver(2, "Jane", "Driver", contact, 2002, "Bus Driver", 50000.0,
                          "D", permittedVehicles, 10, 4.9, nullptr);
    maxRatingDriver.completeTrip();
    CHECK(maxRatingDriver.getSafetyRating() <= 5.0);
}

TEST(DriverTest_SetLicense) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus"};
    
    Driver driver(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                 "D", permittedVehicles, 5, 4.5, nullptr);
    
    // Изначально лицензии нет
    CHECK(!driver.hasValidLicense());
    
    // Устанавливаем лицензию
    auto license = std::make_shared<License>("DL123456", "D", "2025-12-31");
    driver.setLicense(license);
    
    // Проверяем что лицензия установилась
    CHECK(driver.hasValidLicense());
}

TEST(DriverTest_DisplayInfo) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus", "Minivan"};
    auto license = std::make_shared<License>("DL123456", "D", "2025-12-31");
    
    Driver driver(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                 "D", permittedVehicles, 5, 4.8, license);
    
    StdoutRedirect redirect;
    driver.displayInfo();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("License Category: D") != std::string::npos);
    CHECK(output.find("Driving Experience: 5 years") != std::string::npos);
    CHECK(output.find("Safety Rating: 4.80/5") != std::string::npos);
    CHECK(output.find("Bus") != std::string::npos);
    CHECK(output.find("Minivan") != std::string::npos);
    CHECK(output.find("Driver License: Valid") != std::string::npos);
}
    TEST(AddressTest_Display) {
    Address address("Minsk", "Lenina", "10", "220030");
    
    StdoutRedirect redirect;
    address.display();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Address: Minsk, Lenina, 10, 220030") != std::string::npos);
    CHECK(output.find("Minsk") != std::string::npos);
    CHECK(output.find("Lenina") != std::string::npos);
    CHECK(output.find("10") != std::string::npos);
}

TEST(AddressTest_GetFullAddress) {
    Address address("Grodno", "Sovetskaya", "25", "230025");
    
    CHECK_EQUAL("Grodno, Sovetskaya, 25, 230025", address.getFullAddress());
}

TEST(DriverTest_Constructor) {
   ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus", "Minivan", "Car"};
    auto license = std::make_shared<License>("DL123456", "D", "2025-12-31");
    
    Driver driver(1, "John", "Driver", contact, 2001, "Bus Driver", 50000.0,
                 "D", permittedVehicles, 5, 4.8, license);
    
    CHECK_EQUAL("D", driver.getLicenseCategory());
    CHECK_EQUAL(5, driver.getDrivingExperience());
    CHECK_EQUAL(3u, driver.getPermittedVehicleTypes().size());
}

TEST(DriverTest_InvalidConstructor) {
    ContactInfo contact("driver@test.com", "+375292223344");
    vector<string> permittedVehicles = {"Bus", "Minivan", "Car"};
    auto license = std::make_shared<License>("DL123456", "D", "2025-12-31");

    
    CHECK_THROW(
        Driver(1, "John", "Doe", contact, 7001, "Driver", 30000.0,
              "", permittedVehicles, 3,4,license),  // Пустая категория прав
        std::invalid_argument
    );
    
    CHECK_THROW(
        Driver(1, "John", "Doe", contact, 7001, "Driver", 30000.0,
              "B", vector<string>(), 3,4,license),  // Пустые типы ТС
        std::invalid_argument
    );
}