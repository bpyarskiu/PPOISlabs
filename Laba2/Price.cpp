#include "Price.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Price::Price(double amount, const string& currency) 
    : amount(amount), currency(currency) {
    
    if (!validateAmount(amount)) {
        throw invalid_argument("Invalid price amount");
    }
    if (!validateCurrency(currency)) {
        throw invalid_argument("Invalid currency");
    }
}

double Price::getAmount() const { 
    return amount; 
}

string Price::getCurrency() const { 
    return currency; 
}

Price Price::add(const Price& other) const {
    if (currency != other.currency) {
        throw invalid_argument("Cannot add prices with different currencies");
    }
    return Price(amount + other.amount, currency);
}

Price Price::multiply(double factor) const {
    if (factor < 0) {
        throw invalid_argument("Multiplication factor cannot be negative");
    }
    return Price(amount * factor, currency);
}

void Price::display() const {
    cout << amount << " " << currency;
}

bool Price::validateAmount(double amount) const {
    return amount >= 0.0;
}

bool Price::validateCurrency(const string& currency) const {
    return !currency.empty() && currency.length() == 3;
}