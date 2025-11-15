#pragma once
#include "Employee.hpp"
#include "Client.hpp"
#include "Tour.hpp"
#include "Booking.hpp"
#include "Accommodation.hpp"
#include "Equipment.hpp"
#include "Complaint.hpp"
#include <vector>
#include <memory>
#include <string>

class Company {
private:
    std::string name;
    int foundationYear;
    Address headquarters;
    
    std::vector<std::shared_ptr<Employee>> employees;
    std::vector<std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<Tour>> tours;
    std::vector<std::shared_ptr<Booking>> bookings;
    std::vector<std::shared_ptr<Accommodation>> accommodations;
    std::vector<std::shared_ptr<Equipment>> equipment;
    std::vector<std::shared_ptr<Complaint>> complaints;

public:
    Company(const std::string& name, int foundationYear, const Address& headquarters);

    std::string getName() const;
    int getFoundationYear() const;
    Address getHeadquarters() const;
    
    const std::vector<std::shared_ptr<Employee>>& getEmployees() const;
    const std::vector<std::shared_ptr<Client>>& getClients() const;
    const std::vector<std::shared_ptr<Tour>>& getTours() const;
    const std::vector<std::shared_ptr<Booking>>& getBookings() const;
    const std::vector<std::shared_ptr<Accommodation>>& getAccommodations() const;
    const std::vector<std::shared_ptr<Equipment>>& getEquipment() const;
    const std::vector<std::shared_ptr<Complaint>>& getComplaints() const;

    void addEmployee(const std::shared_ptr<Employee>& employee);
    void addClient(const std::shared_ptr<Client>& client);
    void addTour(const std::shared_ptr<Tour>& tour);
    void addBooking(const std::shared_ptr<Booking>& booking);
    void addAccommodation(const std::shared_ptr<Accommodation>& accommodation);
    void addEquipment(const std::shared_ptr<Equipment>& equipment);
    void addComplaint(const std::shared_ptr<Complaint>& complaint);
    
    void resolveComplaint(int index);
    Equipment* findEquipment(const std::string& name);
    
    void displayCompanyInfo() const;
    void displayAllEquipment() const;
    void displayAllAccommodations() const;
    void displayPendingComplaints() const;
};