#include "Tour.hpp"
#include <iostream>

using namespace std;

Tour::Tour(int tourId, const string& name, const string& destination, 
           const Price& basePrice, const DateRange& dateRange)
    : tourId(tourId), name(name), destination(destination), 
      basePrice(basePrice), dateRange(dateRange) {
    
    if (name.empty() || destination.empty()) {
        throw invalid_argument("Tour name and destination cannot be empty");
    }
}

int Tour::getTourId() const { return tourId; }
string Tour::getName() const { return name; }
string Tour::getDestination() const { return destination; }
Price Tour::getBasePrice() const { return basePrice; }
DateRange Tour::getDateRange() const { return dateRange; }
const vector<shared_ptr<Accommodation>>& Tour::getAccommodations() const { return accommodations; }
const vector<shared_ptr<Transport>>& Tour::getTransports() const { return transports; }

void Tour::addAccommodation(const shared_ptr<Accommodation>& accommodation) {
    if (!accommodation) {
        throw invalid_argument("Cannot add null accommodation");
    }
    accommodations.push_back(accommodation);
}

void Tour::addTransport(const shared_ptr<Transport>& transport) {
    if (!transport) {
        throw invalid_argument("Cannot add null transport");
    }
    transports.push_back(transport);
}

void Tour::setMealPlan(const shared_ptr<MealPlan>& mealPlan) {
    this->mealPlan = mealPlan;
}

Price Tour::calculateTotalPrice() const {
    Price total = basePrice;
    int nights = getTourDurationDays();
    
    // Стоимость проживания
    for (const auto& accommodation : accommodations) {
        if (accommodation) {
            total = total.add(accommodation->calculateTotalCost(nights));
        }
    }
    
    // Стоимость транспорта
    for (const auto& transport : transports) {
        if (transport) {
            total = total.add(transport->getPrice());
        }
    }
    
    // Стоимость страховки
    if (insurance) {
        total = total.add(insurance->getPrice());
    }
    
    // Стоимость питания
    if (mealPlan) {
        total = total.add(mealPlan->calculateTotalCost(nights));
    }
    
    return total;
}


bool Tour::isActive() const {
    auto now = chrono::system_clock::now();
    return dateRange.isDateInRange(now);
}

void Tour::displayTourInfo() const {
    cout << "=== TOUR INFORMATION ===" << endl;
    cout << "Tour ID: " << tourId << endl;
    cout << "Name: " << name << endl;
    cout << "Destination: " << destination << endl;
    cout << "Duration: " << getTourDurationDays() << " days" << endl;
    cout << "Base Price: ";
    basePrice.display();
    cout << "Total Price: ";
    calculateTotalPrice().display();
    cout << "Average Rating: " << getAverageRating() << "/5" << endl;
    cout << "Status: " << (isActive() ? "Active" : "Inactive") << endl;
    cout << "Accommodations: " << accommodations.size() << endl;
    cout << "Transports: " << transports.size() << endl;
    cout << "Insurance: " << (insurance ? "Included" : "Not included") << endl;
    cout << "Meal Plan: " << (mealPlan ? mealPlan->getType() : "Not included") << endl;
    cout << "Reviews: " << reviews.size() << endl;
    cout << "========================" << endl;
}

int Tour::getTourDurationDays() const {
    return dateRange.getDurationDays();
}