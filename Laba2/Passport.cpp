#include "Passport.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Passport::Passport(const string& number, const string& nationality, 
                   const string& expirationDate)
    : number(number), nationality(nationality), expirationDate(expirationDate) {
    
    if (!validateNumber(number)) {
        throw invalid_argument("Invalid passport number");
    }
    if (!validateDate(expirationDate)) {
        throw invalid_argument("Invalid expiration date");
    }
}

string Passport::getNumber() const { 
    return number; 
}

string Passport::getNationality() const { 
    return nationality; 
}

string Passport::getExpirationDate() const { 
    return expirationDate; 
}

bool Passport::isValid() const {
    // Простая проверка - в реальной системе была бы проверка даты
    return !expirationDate.empty() && expirationDate != "EXPIRED";
}

void Passport::display() const {
    cout << "Passport: " << number << endl;
    cout << "Nationality: " << nationality << endl;
    cout << "Expires: " << expirationDate << endl;
    cout << "Status: " << (isValid() ? "Valid" : "Invalid") << endl;
}

bool Passport::validateNumber(const string& number) const {
    return !number.empty() && number.length() >= 6;
}

bool Passport::validateDate(const string& date) const {
    return !date.empty();
}