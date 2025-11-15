#pragma once
#include "Person.hpp"
#include "Discount.hpp"
#include "Passport.hpp"
#include <string>
#include <memory>

class Client : public Person {
private:
    int clientId;
    std::string preferences;
    std::shared_ptr<Discount> discount;
    std::shared_ptr<Passport> passport;

public:
    Client(int id, const std::string& firstName, const std::string& lastName, 
           const ContactInfo& contact, int clientId, 
           const std::string& preferences = "",
           const std::shared_ptr<Discount>& discount = nullptr,
           const std::shared_ptr<Passport>& passport = nullptr);
    
    int getClientId() const;
    std::string getPreferences() const;
    std::shared_ptr<Discount> getDiscount() const;
    std::shared_ptr<Passport> getPassport() const;
    
    void setDiscount(const std::shared_ptr<Discount>& newDiscount);
    void setPassport(const std::shared_ptr<Passport>& newPassport);
    double applyDiscountToPrice(double price) const;
    bool hasValidPassport() const;
    void displayClientInfo() const;
};