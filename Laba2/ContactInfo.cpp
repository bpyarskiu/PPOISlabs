#include "ContactInfo.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

ContactInfo::ContactInfo(const string& email, const string& phone)
    : email(email), phone(phone) {
    
    if (!validateEmail(email)) {
        throw invalid_argument("Invalid email format");
    }
    if (!validatePhone(phone)) {
        throw invalid_argument("Invalid phone format");
    }
}

string ContactInfo::getEmail() const { 
    return email; 
}

string ContactInfo::getPhone() const { 
    return phone; 
}

bool ContactInfo::isValidEmail() const {
    return email.find('@') != string::npos && email.find('.') != string::npos;
}

bool ContactInfo::isValidPhone() const {
    return phone.length() >= 7;
}

void ContactInfo::display() const {
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
}

bool ContactInfo::validateEmail(const string& email) const {
    return !email.empty() && email.find('@') != string::npos;
}

bool ContactInfo::validatePhone(const string& phone) const {
    return !phone.empty() && phone.length() >= 7;
}