#include "Insurance.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Insurance::Insurance(const string& type, const Price& price, 
                     const string& coverage, const Duration& duration)
    : type(type), price(price), coverage(coverage), duration(duration) {
    
    if (!validateType(type)) {
        throw invalid_argument("Invalid insurance type");
    }
}

string Insurance::getType() const { 
    return type; 
}

Price Insurance::getPrice() const { 
    return price; 
}

string Insurance::getCoverage() const { 
    return coverage; 
}

Duration Insurance::getDuration() const { 
    return duration; 
}

void Insurance::display() const {
    cout << "=== INSURANCE ===" << endl;
    cout << "Type: " << type << endl;
    cout << "Coverage: " << coverage << endl;
    cout << "Price: ";
    price.display();
    duration.display();
    cout << "=================" << endl;
}

bool Insurance::validateType(const string& type) const {
    return !type.empty();
}