#include "Equipment.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Equipment::Equipment(const string& name, const string& condition, int quantity)
    : name(name), condition(condition), quantity(quantity) {
    
    if (name.empty()) {
        throw invalid_argument("Equipment name cannot be empty");
    }
    if (!validateQuantity(quantity)) {
        throw invalid_argument("Invalid equipment quantity");
    }
}

string Equipment::getName() const { 
    return name; 
}

string Equipment::getCondition() const { 
    return condition; 
}

int Equipment::getQuantity() const { 
    return quantity; 
}

void Equipment::use() {
    if (quantity > 0 && condition != "Broken") {
        if (condition == "Good") {
            condition = "Worn";
        } else if (condition == "Worn") {
            condition = "Poor";
        }
    }
}

void Equipment::repair() {
    condition = "Good";
}

void Equipment::addQuantity(int amount) {
    if (amount < 0) {
        throw invalid_argument("Cannot add negative quantity");
    }
    quantity += amount;
}

bool Equipment::isUsable() const {
    return quantity > 0 && condition != "Broken";
}

void Equipment::display() const {
    cout << "Equipment: " << name << endl;
    cout << "Condition: " << condition << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Status: " << (isUsable() ? "Usable" : "Not usable") << endl;
}

bool Equipment::validateQuantity(int quantity) const {
    return quantity >= 0;
}