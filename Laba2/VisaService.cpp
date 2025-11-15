#include "VisaService.hpp"
#include "CustomExceptions.hpp"
#include <iostream>
#include <set>

using namespace std;

VisaService::VisaService(int visaId, const shared_ptr<Client>& client,
                         const string& destinationCountry, VisaType type,
                         double serviceFee, const string& requirements)
    : visaId(visaId), client(client), destinationCountry(destinationCountry),
      type(type), status(VisaStatus::APPLIED), serviceFee(serviceFee),
      requirements(requirements) {
    
    applicationDate = chrono::system_clock::now();
    validateVisaData();
}

int VisaService::getVisaId() const { return visaId; }

shared_ptr<Client> VisaService::getClient() const { return client; }

string VisaService::getDestinationCountry() const { return destinationCountry; }

VisaType VisaService::getType() const { return type; }

VisaStatus VisaService::getStatus() const { return status; }

chrono::system_clock::time_point VisaService::getApplicationDate() const { return applicationDate; }

chrono::system_clock::time_point VisaService::getDecisionDate() const { return decisionDate; }

double VisaService::getServiceFee() const { return serviceFee; }

string VisaService::getRequirements() const { return requirements; }

void VisaService::applyForVisa() {
    if (status != VisaStatus::APPLIED) {
        throw VisaProcessingException("Visa already processed");
    }
    
    // Имитация проверки требований
    if (requirements.empty()) {
        throw VisaProcessingException("Visa requirements not specified");
    }
    
    cout << "Visa application submitted for " << destinationCountry << endl;
}

void VisaService::approveVisa() {
    if (status != VisaStatus::APPLIED && status != VisaStatus::IN_PROGRESS) {
        throw VisaProcessingException("Cannot approve visa in current status");
    }
    
    status = VisaStatus::APPROVED;
    decisionDate = chrono::system_clock::now();
    cout << "Visa approved for " << destinationCountry << endl;
}

void VisaService::rejectVisa(const string& reason) {
    if (status != VisaStatus::APPLIED && status != VisaStatus::IN_PROGRESS) {
        throw VisaProcessingException("Cannot reject visa in current status");
    }
    
    if (reason.empty()) {
        throw VisaProcessingException("Rejection reason must be provided");
    }
    
    status = VisaStatus::REJECTED;
    decisionDate = chrono::system_clock::now();
    cout << "Visa rejected for " << destinationCountry << ". Reason: " << reason << endl;
}

bool VisaService::isVisaRequired() const {
    // Упрощенная логика - для некоторых стран виза не нужна
    static const std::set<std::string> noVisaCountries = {"Turkey", "Egypt", "Thailand", "UAE"};
    return noVisaCountries.find(destinationCountry) == noVisaCountries.end();
}

int VisaService::getProcessingDays() const {
    auto now = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::hours>(now - applicationDate);
    return static_cast<int>(duration.count() / 24);
}

void VisaService::displayVisaInfo() const {
    validateVisaData();
    
    auto appTime = chrono::system_clock::to_time_t(applicationDate);
    string typeStr[] = {"Tourist", "Business", "Transit", "Student"};
    string statusStr[] = {"Not Required", "Applied", "Approved", "Rejected", "In Progress"};
    
    cout << "Visa ID: " << visaId << endl
         << "Country: " << destinationCountry << endl
         << "Type: " << typeStr[static_cast<int>(type)] << endl
         << "Status: " << statusStr[static_cast<int>(status)] << endl
         << "Service Fee: " << serviceFee << " RUB" << endl
         << "Application Date: " << ctime(&appTime)
         << "Requirements: " << requirements << endl
         << "Processing Days: " << getProcessingDays() << endl;
}

void VisaService::validateVisaData() const {
    if (visaId <= 0) {
        throw DataValidationException("Invalid visa ID");
    }
    
    if (!client) {
        throw ResourceNotFoundException("Client not found for visa service");
    }
    
    if (destinationCountry.empty()) {
        throw DataValidationException("Destination country cannot be empty");
    }
    
    if (serviceFee < 0) {
        throw DataValidationException("Service fee cannot be negative");
    }
}