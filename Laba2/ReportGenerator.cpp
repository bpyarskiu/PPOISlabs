#include "ReportGenerator.hpp"
#include "CustomExceptions.hpp"
#include "BusRide.hpp"
#include "Flight.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

ReportGenerator::ReportGenerator(const shared_ptr<Company>& company, ReportType type,
                                 const chrono::system_clock::time_point& startDate,
                                 const chrono::system_clock::time_point& endDate,
                                 const shared_ptr<ServerStatus>& serverStatus)
    : company(company), type(type), startDate(startDate), endDate(endDate), 
      serverStatus(serverStatus ? serverStatus : make_shared<ServerStatus>()) {
    
    validateReportPeriod();
}

shared_ptr<Company> ReportGenerator::getCompany() const { return company; }

ReportType ReportGenerator::getType() const { return type; }

chrono::system_clock::time_point ReportGenerator::getStartDate() const { return startDate; }

chrono::system_clock::time_point ReportGenerator::getEndDate() const { return endDate; }

void ReportGenerator::generateFinancialReport() const {
    validateReportPeriod();
    
    double totalRevenue = calculateTotalRevenueInPeriod();
    int bookingsCount = calculateBookingsCountInPeriod();
    
    auto startTime = chrono::system_clock::to_time_t(startDate);
    auto endTime = chrono::system_clock::to_time_t(endDate);
    
    cout << "=== FINANCIAL REPORT ===" << endl
         << "Period: " << ctime(&startTime) << "       to " << ctime(&endTime)
         << "Total Revenue: " << fixed << setprecision(2) << totalRevenue << " RUB" << endl
         << "Number of Bookings: " << bookingsCount << endl
         << "Average Booking Value: " << (bookingsCount > 0 ? totalRevenue / bookingsCount : 0) << " RUB" << endl
         << "=========================" << endl;
}

void ReportGenerator::generateBookingStatisticsReport() const {
    validateReportPeriod();
    
    int confirmed = 0, cancelled = 0, completed = 0, pending = 0;
    
    // Здесь была бы логика подсчета статусов бронирований
    // Для прототипа используем заглушки
    confirmed = rand() % 50 + 20;
    cancelled = rand() % 10 + 5;
    completed = rand() % 30 + 15;
    pending = rand() % 15 + 5;
    
    int total = confirmed + cancelled + completed + pending;
    
    cout << "=== BOOKING STATISTICS ===" << endl
         << "Total Bookings: " << total << endl
         << "Confirmed: " << confirmed << " (" << (total > 0 ? (confirmed * 100 / total) : 0) << "%)" << endl
         << "Completed: " << completed << " (" << (total > 0 ? (completed * 100 / total) : 0) << "%)" << endl
         << "Cancelled: " << cancelled << " (" << (total > 0 ? (cancelled * 100 / total) : 0) << "%)" << endl
         << "Pending: " << pending << " (" << (total > 0 ? (pending * 100 / total) : 0) << "%)" << endl
         << "==========================" << endl;
}

void ReportGenerator::generateClientActivityReport() const {
    validateReportPeriod();
    
    int newClients = calculateNewClientsInPeriod();
    int activeClients = rand() % 100 + 50;
    int returningClients = rand() % 30 + 10;
    
    cout << "=== CLIENT ACTIVITY REPORT ===" << endl
         << "New Clients: " << newClients << endl
         << "Active Clients: " << activeClients << endl
         << "Returning Clients: " << returningClients << endl
         << "Client Retention Rate: " << (activeClients > 0 ? (returningClients * 100 / activeClients) : 0) << "%" << endl
         << "==============================" << endl;
}

void ReportGenerator::generateTourPerformanceReport() const {
    validateReportPeriod();
    
    // Заглушка для отчета по турам
    cout << "=== TOUR PERFORMANCE REPORT ===" << endl
         << "Most Popular Destination: Turkey" << endl
         << "Average Tour Rating: 4.2/5" << endl
         << "Tour Completion Rate: 92%" << endl
         << "Customer Satisfaction: 88%" << endl
         << "===============================" << endl;
}

void ReportGenerator::generateEmployeePerformanceReport() const {
    validateReportPeriod();
    
    // Заглушка для отчета по сотрудникам
    cout << "=== EMPLOYEE PERFORMANCE REPORT ===" << endl
         << "Top Performing Guide: Ivan Petrov (Rating: 4.8/5)" << endl
         << "Average Employee Rating: 4.3/5" << endl
         << "Total Bookings Handled: 156" << endl
         << "Client Satisfaction: 91%" << endl
         << "===================================" << endl;
}

#include "ReportGenerator.hpp"
#include "CustomExceptions.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


void ReportGenerator::generateDriverWaybill(const shared_ptr<Driver>& driver, 
                                           const shared_ptr<Transport>& vehicle,
                                           const string& route,
                                           const chrono::system_clock::time_point& tripStart,
                                           const chrono::system_clock::time_point& tripEnd,
                                           int passengersCount) const {
    
    if (!driver) {
        throw ResourceNotFoundException("Driver not found for waybill generation");
    }
    
    if (!vehicle) {
        throw ResourceNotFoundException("Vehicle not found for waybill generation");
    }
    
    if (route.empty()) {
        throw DataValidationException("Route cannot be empty for waybill");
    }
    
    if (tripStart >= tripEnd) {
        throw DataValidationException("Trip start time must be before end time");
    }
    
    if (passengersCount < 0) {
        throw DataValidationException("Passengers count cannot be negative");
    }
    
    auto startTime = chrono::system_clock::to_time_t(tripStart);
    auto endTime = chrono::system_clock::to_time_t(tripEnd);
    auto generationTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    
    // Расчет продолжительности поездки
    auto duration = chrono::duration_cast<chrono::hours>(tripEnd - tripStart);
    
    cout << "=== DRIVER WAYBILL ===" << endl
         << "Waybill ID: WB" << generationTime << endl
         << "Generation Date: " << ctime(&generationTime)
         << "Driver: " << driver->getFullName() << endl
         << "Driver ID: " << driver->getEmployeeId() << endl
         << "License Category: " << driver->getLicenseCategory() << endl
         << "Experience: " << driver->getDrivingExperience() << " years" << endl
         << "Safety Rating: " << driver->getSafetyRating() << "/5" << endl
         << endl
         << "Vehicle Information:" << endl
         << "Type: " << (dynamic_pointer_cast<BusRide>(vehicle) ? "Bus" : "Other Transport") << endl;
    
    if (auto bus = dynamic_pointer_cast<BusRide>(vehicle)) {
        cout << "Bus Number: " << bus->getBusNumber() << endl
             << "Company: " << bus->getCompany() << endl
             << "Capacity: " << bus->getCapacity() << " passengers" << endl;
    }
    
    if (auto flight = dynamic_pointer_cast<Flight>(vehicle)) {
        cout << "Flight Number: " << flight->getFlightNumber() << endl
             << "Airline: " << flight->getAirline() << endl;
    }
    
    cout << endl
         << "Trip Details:" << endl
         << "Route: " << route << endl
         << "Departure: " << ctime(&startTime)
         << "Arrival: " << ctime(&endTime)
         << "Duration: " << duration.count() << " hours" << endl
         << "Passengers: " << passengersCount << endl
         << endl
         << "Vehicle Amenities: ";
    
    if (auto bus = dynamic_pointer_cast<BusRide>(vehicle)) {
        cout << (bus->getHasWC() ? "WC " : "")
             << (bus->getHasAirConditioning() ? "AC " : "");
    }
    
    cout << endl
         << "Trip Status: COMPLETED" << endl
         << "Driver Signature: ________________" << endl
         << "Supervisor Signature: _____________" << endl
         << "=========================" << endl;
    
    // Обновляем статистику водителя
    driver->completeTrip();
}


void ReportGenerator::generateAllReports() const {
    if (serverStatus) {
        serverStatus->checkServerStatus();
        serverStatus->checkWebsiteStatus();
        cout << endl;
    }
    
    cout << "Generating comprehensive report package..." << endl << endl;
    
    generateFinancialReport();
    cout << endl;
    generateBookingStatisticsReport();
    cout << endl;
    generateClientActivityReport();
    cout << endl;
    generateTourPerformanceReport();
    cout << endl;
    generateEmployeePerformanceReport();
    
    if (serverStatus) {
        cout << endl;
        serverStatus->systemReady();
    }
}

void ReportGenerator::checkSystemStatus() const {
    if (serverStatus) {
        cout << "=== SYSTEM STATUS CHECK ===" << endl;
        serverStatus->checkServerStatus();
        serverStatus->checkWebsiteStatus();
        serverStatus->checkDatabaseStatus();
        serverStatus->systemReady();
        cout << "===========================" << endl;
    } else {
        cout << "System status monitor not available" << endl;
    }
}
void ReportGenerator::displayReportSummary() const {
    auto startTime = chrono::system_clock::to_time_t(startDate);
    auto endTime = chrono::system_clock::to_time_t(endDate);
    
    cout << "Report Summary:" << endl
         << "Type: " << static_cast<int>(type) << endl
         << "Period: " << ctime(&startTime) << "  to  " << ctime(&endTime)
         << "Company: " << (company ? company->getName() : "N/A") << endl;
}

void ReportGenerator::validateReportPeriod() const {
    if (startDate >= endDate) {
        throw DataValidationException("Report start date must be before end date");
    }
    
    if (!company) {
        throw ResourceNotFoundException("Company not specified for report generation");
    }
    
    auto now = chrono::system_clock::now();
    if (endDate > now) {
        throw DataValidationException("Report end date cannot be in the future");
    }
}

double ReportGenerator::calculateTotalRevenueInPeriod() const {
    // Заглушка - в реальной системе здесь был бы расчет по платежам
    return rand() % 1000000 + 500000; // Случайная сумма от 500к до 1.5м
}

int ReportGenerator::calculateBookingsCountInPeriod() const {
    // Заглушка
    return rand() % 100 + 50; // Случайное количество от 50 до 150
}

int ReportGenerator::calculateNewClientsInPeriod() const {
    // Заглушка
    return rand() % 50 + 20; // Случайное количество от 20 до 70
}