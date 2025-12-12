#include "Supporter.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

std::ostream& operator<<(std::ostream& os, SupportLevel level) {
    switch(level) {
        case SupportLevel::BASIC:
            os << "Basic";
            break;
        case SupportLevel::PREMIUM:
            os << "Premium";
            break;
        case SupportLevel::STANDARD:
             os << "Standard";
            break;
        case SupportLevel::URGENT:
            os << "Urgent";
            break;
        default:
            os << "SupportLevel::Unknown(" << static_cast<int>(level) << ")";
    }
    return os;
}

Supporter::Supporter(int id, const string& firstName, const string& lastName,
                     const ContactInfo& contact, int employeeId, 
                     const string& position, double salary,
                     SupportLevel supportLevel,
                     const vector<string>& supportedLanguages,
                     int resolvedTickets, double satisfactionRating)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      supportLevel(supportLevel), supportedLanguages(supportedLanguages),
      resolvedTickets(resolvedTickets), satisfactionRating(satisfactionRating) {
    
    if (supportedLanguages.empty()) {
        throw invalid_argument("Supporter must support at least one language");
    }
}

SupportLevel Supporter::getSupportLevel() const { return supportLevel; }
const vector<string>& Supporter::getSupportedLanguages() const { return supportedLanguages; }
int Supporter::getResolvedTickets() const { return resolvedTickets; }
double Supporter::getSatisfactionRating() const { return satisfactionRating; }

void Supporter::addSupportedLanguage(const string& language) {
    if (language.empty()) {
        throw invalid_argument("Language cannot be empty");
    }
    if (find(supportedLanguages.begin(), supportedLanguages.end(), language) == supportedLanguages.end()) {
        supportedLanguages.push_back(language);
    }
}

void Supporter::resolveTicket() {
    resolvedTickets++;
    if (satisfactionRating < 4.9) {
        satisfactionRating += 0.05;
    }
}

void Supporter::displayInfo() const {
    display();
     cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
    cout << "Support Level: " << getSupportLevelString() << endl;
    cout << "Resolved Tickets: " << resolvedTickets << endl;
    cout << "Satisfaction Rating: " << satisfactionRating << "/5" << endl;
    cout << "Supported Languages: ";
    for (const auto& language : supportedLanguages) {
        cout << language << " ";
    }
    cout << endl;
}

string Supporter::getSupportLevelString() const {
    switch (supportLevel) {
        case SupportLevel::BASIC: return "Basic";
        case SupportLevel::STANDARD: return "Standard";
        case SupportLevel::PREMIUM: return "Premium";
        case SupportLevel::URGENT: return "Urgent";
        default: return "Unknown";
    }
}