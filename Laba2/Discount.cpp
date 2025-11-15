#include "Discount.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Discount::Discount(double percentage, const string& description) 
    : percentage(percentage), description(description) {
    
    if (!validatePercentage(percentage)) {
        throw invalid_argument("Invalid discount percentage");
    }
}

double Discount::getPercentage() const { 
    return percentage; 
}

string Discount::getDescription() const { 
    return description; 
}

double Discount::calculateDiscountedPrice(double originalPrice) const {
    if (!validatePrice(originalPrice)) {
        throw invalid_argument("Invalid price");
    }
    return originalPrice * (1.0 - percentage / 100.0);
}

bool Discount::isValid() const {
    return percentage > 0.0;
}

void Discount::display() const {
    cout << "Discount: " << percentage << "%";
    if (!description.empty()) {
        cout << " (" << description << ")";
    }
    cout << endl;
}

bool Discount::validatePercentage(double percentage) const {
    return percentage >= 0.0 && percentage <= 100.0;
}

bool Discount::validatePrice(double price) const {
    return price >= 0.0;
}