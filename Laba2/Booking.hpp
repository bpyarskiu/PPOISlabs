#pragma once
#include "Client.hpp"
#include "Tour.hpp"
#include "Employee.hpp"
#include <chrono>
#include <memory>


class Booking {
private:
    int bookingId;
    std::chrono::system_clock::time_point bookingDate;
    std::shared_ptr<Client> client;
    std::shared_ptr<Tour> tour;
    std::shared_ptr<Employee> manager;

public:
    Booking(int bookingId, const std::shared_ptr<Client>& client, 
                  const std::shared_ptr<Tour>& tour, 
                  const std::shared_ptr<Employee>& manager);
    
    int getBookingId() const;
    std::chrono::system_clock::time_point getBookingDate() const;
    std::shared_ptr<Client> getClient() const;
    std::shared_ptr<Tour> getTour() const;
    std::shared_ptr<Employee> getManager() const;
    
    void displayBookingInfo() const;
};