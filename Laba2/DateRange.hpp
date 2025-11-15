#pragma once
#include <chrono>

class DateRange {
private:
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;

public:
    DateRange(const std::chrono::system_clock::time_point& start, 
              const std::chrono::system_clock::time_point& end);
    
    std::chrono::system_clock::time_point getStartDate() const;
    std::chrono::system_clock::time_point getEndDate() const;
    
    int getDurationDays() const;
    bool isDateInRange(const std::chrono::system_clock::time_point& date) const;
    void displayDateRange() const;
};