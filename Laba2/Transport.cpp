#include "Transport.hpp"
#include <iostream>

using namespace std;

Transport::Transport(int transportId, const string& type, 
                     const string& description, const Price& price)
    : transportId(transportId), type(type), description(description), price(price) {
    
    if (type.empty()) {
        throw invalid_argument("Transport type cannot be empty");
    }
}

int Transport::getTransportId() const { return transportId; }
string Transport::getType() const { return type; }
string Transport::getDescription() const { return description; }
Price Transport::getPrice() const { return price; }

string Transport::getTransportInfo() const {
    return "Transport ID: " + to_string(transportId) + ", Type: " + type + ", Description: " + description;
}

double Transport::calculatePrice(int passengers) const {
    // Базовая реализация - умножаем цену на количество пассажиров
    return price.getAmount() * passengers;
}

void Transport::displayTransportInfo() const {
    cout << "Transport ID: " << transportId << endl;
    cout << "Type: " << type << endl;
    cout << "Description: " << description << endl;
    cout << "Price: ";
    price.display();
}