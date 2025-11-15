#include "Booking.hpp"
#include <iostream>

using namespace std;

Booking::Booking(int bookingId, const shared_ptr<Client>& client, 
                 const shared_ptr<Tour>& tour, 
                 const shared_ptr<Employee>& manager)
    : bookingId(bookingId), client(client), tour(tour), manager(manager) {
    
    bookingDate = chrono::system_clock::now();
    
    if (!client || !tour || !manager) {
        throw invalid_argument("Client, tour and manager cannot be null");
    }
}

int Booking::getBookingId() const { return bookingId; }
chrono::system_clock::time_point Booking::getBookingDate() const { return bookingDate; }

shared_ptr<Client> Booking::getClient() const { return client; }
shared_ptr<Tour> Booking::getTour() const { return tour; }
shared_ptr<Employee> Booking::getManager() const { return manager; }

void Booking::displayBookingInfo() const {
    auto bookingTime = chrono::system_clock::to_time_t(bookingDate);
    
    cout << "Booking ID: " << bookingId << endl;
    cout << "Booking Date: " << ctime(&bookingTime);
    cout << "Client: " << client->getFullName() << endl;
    cout << "Tour: " << tour->getName() << endl;
    cout << "Manager: " << manager->getFullName() << endl;
}