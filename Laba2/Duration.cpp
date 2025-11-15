#include "Duration.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Duration::Duration(int hours) {
    if (!validateHours(hours)) {
        throw invalid_argument("Invalid hours value");
    }
    this->hours = chrono::hours(hours);
}

int Duration::getHours() const { 
    return hours.count(); 
}

int Duration::getDays() const { 
    return hours.count() / 24; 
}

void Duration::addHours(int additionalHours) {
    if (!validateHours(additionalHours)) {
        throw invalid_argument("Invalid additional hours");
    }
    hours += chrono::hours(additionalHours);
}

string Duration::getFormatted() const {
    int days = getDays();
    int remainingHours = getHours() % 24;
    
    if (days > 0 && remainingHours > 0) {
        return to_string(days) + "d " + to_string(remainingHours) + "h";
    } else if (days > 0) {
        return to_string(days) + " days";
    } else {
        return to_string(getHours()) + " hours";
    }
}

void Duration::display() const {
    cout << "Duration: " << getFormatted() << endl;
}

bool Duration::validateHours(int hours) const {
    return hours >= 0;
}