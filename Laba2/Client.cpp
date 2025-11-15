#include "Client.hpp"
#include <iostream>

using namespace std;

Client::Client(int id, const string& firstName, const string& lastName, 
               const ContactInfo& contact, int clientId, 
               const string& preferences,
               const shared_ptr<Discount>& discount,
               const shared_ptr<Passport>& passport)
    : Person(id, firstName, lastName, contact), 
      clientId(clientId), preferences(preferences), 
      discount(discount), passport(passport) {}


int Client::getClientId() const { return clientId; }
string Client::getPreferences() const { return preferences; }
shared_ptr<Discount> Client::getDiscount() const { return discount; }

void Client::setDiscount(const shared_ptr<Discount>& newDiscount) {
    discount = newDiscount;
}

double Client::applyDiscountToPrice(double price) const {
    if (discount && discount->isValid()) {
        return discount->calculateDiscountedPrice(price);
    }
    return price;
}
void Client::setPassport(const shared_ptr<Passport>& newPassport) {
    passport = newPassport;
}

bool Client::hasValidPassport() const {
    return passport && passport->isValid();
}

void Client::displayClientInfo() const {
    Person::display();
    cout << "Client ID: " << clientId << endl;
    if (!preferences.empty()) {
        cout << "Preferences: " << preferences << endl;
    }
    if (discount && discount->isValid()) {
        discount->display();
    }
    if (passport) {
        cout << "Passport: " << (hasValidPassport() ? "Valid" : "Invalid") << endl;
    }
}