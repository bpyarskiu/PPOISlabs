#include "MealPlan.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

MealPlan::MealPlan(const string& type, const Price& price, const string& description)
    : type(type), pricePerDay(price), description(description) {
    
    if (type.empty()) {
        throw invalid_argument("Meal plan type cannot be empty");
    }
}

string MealPlan::getType() const { 
    return type; 
}

Price MealPlan::getPricePerDay() const { 
    return pricePerDay; 
}

string MealPlan::getDescription() const { 
    return description; 
}

Price MealPlan::calculateTotalCost(int days) const {
    if (!validateDays(days)) {
        throw invalid_argument("Invalid number of days");
    }
    return pricePerDay.multiply(days);
}

void MealPlan::display() const {
    cout << "Meal Plan: " << type << endl;
    if (!description.empty()) {
        cout << "Description: " << description << endl;
    }
    cout << "Price per day: ";
    pricePerDay.display();
    cout << endl;
}

bool MealPlan::validateDays(int days) const {
    return days > 0;
}