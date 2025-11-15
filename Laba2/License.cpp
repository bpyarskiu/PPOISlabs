#include "License.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

License::License(const string& number, const string& category,
                 const string& expirationDate)
    : number(number), category(category), expirationDate(expirationDate) {
    
    if (!validateNumber(number)) {
        throw invalid_argument("Invalid license number");
    }
    if (category.empty()) {
        throw invalid_argument("License category cannot be empty");
    }
}

string License::getNumber() const { 
    return number; 
}

string License::getCategory() const { 
    return category; 
}

string License::getExpirationDate() const { 
    return expirationDate; 
}

bool License::isValid() const {
    return !expirationDate.empty() && expirationDate != "EXPIRED";
}

bool License::canDriveCategory(const string& requiredCategory) const {
    return category.find(requiredCategory) != string::npos;
}

void License::display() const {
    cout << "License: " << number << endl;
    cout << "Category: " << category << endl;
    cout << "Expires: " << expirationDate << endl;
    cout << "Status: " << (isValid() ? "Valid" : "Invalid") << endl;
}

bool License::validateNumber(const string& number) const {
    return !number.empty() && number.length() >= 5;
}