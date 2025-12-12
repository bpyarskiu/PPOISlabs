#pragma once
#include "Employee.hpp"
#include <vector>
#include <string>

enum class SupportLevel {
    BASIC,
    STANDARD,
    PREMIUM,
    URGENT
};

std::ostream& operator<<(std::ostream& os, SupportLevel level);

class Supporter : public Employee {
private:
    SupportLevel supportLevel;
    std::vector<std::string> supportedLanguages;
    int resolvedTickets;
    double satisfactionRating;

public:
    Supporter(int id, const std::string& firstName, const std::string& lastName,
              const ContactInfo& contact, int employeeId, 
              const std::string& position, double salary,
              SupportLevel supportLevel,
              const std::vector<std::string>& supportedLanguages,
              int resolvedTickets, double satisfactionRating);

    SupportLevel getSupportLevel() const;
    const std::vector<std::string>& getSupportedLanguages() const;
    int getResolvedTickets() const;
    double getSatisfactionRating() const;

    void addSupportedLanguage(const std::string& language);
    void resolveTicket();
    void displayInfo() const;
    std::string getSupportLevelString() const;
};