#pragma once
#include "Client.hpp"
#include <string>
#include <chrono>
#include <vector>
#include <memory>

enum class VisaType {
    TOURIST,
    BUSINESS,
    TRANSIT,
    STUDENT
};

enum class VisaStatus {
    NOT_REQUIRED,
    APPLIED,
    APPROVED,
    REJECTED,
    IN_PROGRESS
};

class VisaService {
private:
    int visaId;
    std::shared_ptr<Client> client;
    std::string destinationCountry;
    VisaType type;
    VisaStatus status;
    std::chrono::system_clock::time_point applicationDate;
    std::chrono::system_clock::time_point decisionDate;
    double serviceFee;
    std::string requirements;

public:
    VisaService(int visaId, const std::shared_ptr<Client>& client,
                const std::string& destinationCountry, VisaType type,
                double serviceFee, const std::string& requirements = "");

    // Геттеры
    int getVisaId() const;
    std::shared_ptr<Client> getClient() const;
    std::string getDestinationCountry() const;
    VisaType getType() const;
    VisaStatus getStatus() const;
    std::chrono::system_clock::time_point getApplicationDate() const;
    std::chrono::system_clock::time_point getDecisionDate() const;
    double getServiceFee() const;
    std::string getRequirements() const;

    // Бизнес-методы
    void applyForVisa();
    void approveVisa();
    void rejectVisa(const std::string& reason);
    bool isVisaRequired() const;
    int getProcessingDays() const;
    void displayVisaInfo() const;

private:
    void validateVisaData() const;
};