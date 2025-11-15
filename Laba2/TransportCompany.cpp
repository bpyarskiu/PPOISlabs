#include "TransportCompany.hpp"
#include "CustomExceptions.hpp"
#include <iostream>

using namespace std;

TransportCompany::TransportCompany(int companyId, const string& name,
                                   const string& contactPhone, const string& email,
                                   const string& address, double reliabilityRating) {
    setCompanyId(companyId);
    setName(name);
    setContactPhone(contactPhone);
    setEmail(email);
    setAddress(address);
    setReliabilityRating(reliabilityRating);
}

int TransportCompany::getCompanyId() const { return companyId; }

string TransportCompany::getName() const { return name; }

string TransportCompany::getContactPhone() const { return contactPhone; }

string TransportCompany::getEmail() const { return email; }

string TransportCompany::getAddress() const { return address; }

double TransportCompany::getReliabilityRating() const { return reliabilityRating; }

void TransportCompany::setCompanyId(int companyId) {
    if (companyId <= 0) {
        throw DataValidationException("Company ID must be positive");
    }
    this->companyId = companyId;
}

void TransportCompany::setName(const string& name) {
    if (name.empty()) {
        throw DataValidationException("Company name cannot be empty");
    }
    this->name = name;
}

void TransportCompany::setContactPhone(const string& phone) {
    if (!Validator::isValidPhone(phone)) {
        throw DataValidationException("Invalid contact phone format");
    }
    this->contactPhone = phone;
}

void TransportCompany::setEmail(const string& email) {
    if (!Validator::isValidEmail(email)) {
        throw DataValidationException("Invalid email format");
    }
    this->email = email;
}

void TransportCompany::setAddress(const string& address) {
    if (address.empty()) {
        throw DataValidationException("Address cannot be empty");
    }
    this->address = address;
}

void TransportCompany::setReliabilityRating(double rating) {
    if (rating < 0.0 || rating > 10.0) {
        throw DataValidationException("Reliability rating must be between 0 and 10");
    }
    this->reliabilityRating = rating;
}

void TransportCompany::displayCompanyInfo() const {
    validateCompanyData();
    
    cout << "Transport Company: " << name << endl
         << "ID: " << companyId << endl
         << "Contact: " << contactPhone << endl
         << "Email: " << email << endl
         << "Address: " << address << endl
         << "Reliability Rating: " << reliabilityRating << "/10" << endl;
}

void TransportCompany::validateCompanyData() const {
    if (companyId <= 0) {
        throw DataValidationException("Invalid company ID");
    }
    if (name.empty()) {
        throw DataValidationException("Company name is empty");
    }
    if (!Validator::isValidPhone(contactPhone)) {
        throw DataValidationException("Invalid contact phone");
    }
    if (!Validator::isValidEmail(email)) {
        throw DataValidationException("Invalid email");
    }
    if (reliabilityRating < 0.0 || reliabilityRating > 10.0) {
        throw DataValidationException("Invalid reliability rating");
    }
}