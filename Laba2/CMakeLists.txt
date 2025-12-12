cmake_minimum_required(VERSION 3.10)
project(TourismCompanyTests)

find_package(PkgConfig REQUIRED)
pkg_check_modules(UNITTESTPP REQUIRED UnitTest++)

set(UNITTESTPP_INCLUDE_DIR "/usr/include/UnitTest++")
set(UNITTESTPP_LIBRARY "/usr/lib/libgtest.a")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")



# Основная библиотека
add_library(TourismCompany 
    Address.cpp ContactInfo.cpp Person.cpp Employee.cpp Client.cpp 
    Price.cpp Discount.cpp Rating.cpp Duration.cpp Accomodation.cpp BackupManager.cpp Booking.cpp BusRide.cpp BusRoute.cpp BusStop.cpp 
    Company.cpp Complaint.cpp Consultant.cpp Coordinates.cpp CurrencyConverter.cpp CurrencyPair.cpp 
    DataRange.cpp Department.cpp Driver.cpp Equipment.cpp Excursion.cpp 
    Flight.cpp Guide.cpp HumanResources.cpp Insurance.cpp
    License.cpp Logger.cpp Manager.cpp MealPlan.cpp NotificationManager.cpp
    NotificationService.cpp Passport.cpp
    ReportGenerator.cpp Review.cpp Route.cpp ServerStatus.cpp Statistics.cpp Supporter.cpp
    Tour.cpp Transport.cpp TransportCompany.cpp Validator.cpp VisaService.cpp 
)

# Исполняемый файл тестов
add_executable(run_tests
    tests/main.cpp
    tests/BasicClassesTests.cpp
    tests/PersonnelTests.cpp
    tests/UtilityClassesTests.cpp
    tests/CompanyTests.cpp
    tests/CurrencyTests.cpp
    tests/RouteTests.cpp
    tests/BookingTests.cpp
    tests/TransportTests.cpp
    tests/LoggerTests.cpp
    tests/ValidatorTests.cpp
    tests/PaymentTests.cpp
    tests/ReportTests.cpp
    tests/ClientTests.cpp
    tests/EmployeeTests.cpp
    tests/DriverTests.cpp
    tests/PassporLicesnceDiscountTests.cpp
    tests/SupporterTests.cpp
    tests/HELPERFILE.cpp
    tests/ReviewTests.cpp
    tests/StatisticsTests.cpp
    tests/GuideTests.cpp
    tests/ManagerTests.cpp
    tests/HRTests.cpp
    tests/ConsultantTests.cpp
    tests/BusRideTests.cpp
    tests/BusRouteTests.cpp
    tests/BusStopTests.cpp
    tests/NotificationManagerTests.cpp
    tests/NotificationServiceTests.cpp
    tests/AccommodationTests.cpp
    tests/TransportCompanyTests.cpp
    tests/TourTests.cpp
    tests/VisaServiceTests.cpp
    CustomExceptions.hpp
)

# Связываем тесты с библиотекой и UnitTest++
target_link_libraries(run_tests TourismCompany ${UNITTESTPP_LIBRARIES})
target_include_directories(run_tests PRIVATE ${UNITTESTPP_INCLUDE_DIRS})

# Добавляем цель для запуска тестов
add_custom_target(test
    COMMAND ./run_tests
    DEPENDS run_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)