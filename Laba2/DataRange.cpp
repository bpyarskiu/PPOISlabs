#include "DateRange.hpp"
#include <iostream>

using namespace std;
using namespace chrono;

DateRange::DateRange(const system_clock::time_point& start, 
                     const system_clock::time_point& end)
    : startDate(start), endDate(end) {
    
    if (start >= end) {
        throw invalid_argument("Start date must be before end date");
    }
}

system_clock::time_point DateRange::getStartDate() const { return startDate; }
system_clock::time_point DateRange::getEndDate() const { return endDate; }

int DateRange::getDurationDays() const {
    auto duration = endDate - startDate;
    return duration_cast<hours>(duration).count() / 24;
}

bool DateRange::isDateInRange(const system_clock::time_point& date) const {
    return date >= startDate && date <= endDate;
}

void DateRange::displayDateRange() const {
    auto startTime = system_clock::to_time_t(startDate);
    auto endTime = system_clock::to_time_t(endDate);
    
    cout << "From: " << ctime(&startTime);
    cout << "To: " << ctime(&endTime);
    cout << "Duration: " << getDurationDays() << " days" << endl;
}