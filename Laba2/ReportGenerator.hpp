// ReportGenerator.hpp
#pragma once
#include "Company.hpp"
#include "Booking.hpp"
#include "PaymentSystem.hpp"
#include "Driver.hpp"
#include "ServerStatus.hpp" // Добавляем новый класс
#include <vector>
#include <memory>
#include <string>

enum class ReportType {
    FINANCIAL,
    BOOKING_STATISTICS,
    CLIENT_ACTIVITY,
    TOUR_PERFORMANCE,
    EMPLOYEE_PERFORMANCE
};

class ReportGenerator {
private:
    std::shared_ptr<Company> company;
    ReportType type;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    std::shared_ptr<ServerStatus> serverStatus; // Добавляем статус сервера

public:
    ReportGenerator(const std::shared_ptr<Company>& company, ReportType type,
                    const std::chrono::system_clock::time_point& startDate,
                    const std::chrono::system_clock::time_point& endDate,
                    const std::shared_ptr<ServerStatus>& serverStatus = nullptr);

    // Геттеры
    std::shared_ptr<Company> getCompany() const;
    ReportType getType() const;
    std::chrono::system_clock::time_point getStartDate() const;
    std::chrono::system_clock::time_point getEndDate() const;

    // Методы генерации отчетов
    void generateFinancialReport() const;
    void generateBookingStatisticsReport() const;
    void generateClientActivityReport() const;
    void generateTourPerformanceReport() const;
    void generateEmployeePerformanceReport() const;
    void generateDriverWaybill(const std::shared_ptr<Driver>& driver, 
                              const std::shared_ptr<Transport>& vehicle,
                              const std::string& route,
                              const std::chrono::system_clock::time_point& tripStart,
                              const std::chrono::system_clock::time_point& tripEnd,
                              int passengersCount) const;
    
    void generateAllReports() const;
    void displayReportSummary() const;
    void checkSystemStatus() const; // Новый метод для проверки статуса системы

private:
    void validateReportPeriod() const;
    double calculateTotalRevenueInPeriod() const;
    int calculateBookingsCountInPeriod() const;
    int calculateNewClientsInPeriod() const;
};