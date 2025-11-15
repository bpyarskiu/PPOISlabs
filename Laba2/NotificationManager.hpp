#pragma once
#include "Company.hpp"
#include <memory>
#include <string>
#include <vector>

class NotificationManager {
private:
    std::shared_ptr<Company> company;

public:
    NotificationManager(const std::shared_ptr<Company>& company);
    
    void sendTourReminders() const;
    void sendPaymentReminders() const;
    void sendSpecialOffers() const;
    void sendSystemMaintenanceNotice() const;
    void sendBirthdayGreetings() const;
    
    void sendAllNotifications() const;

private:
    std::vector<std::string> getClientEmails() const;
    std::string generateTourReminderMessage() const;
    std::string generateSpecialOfferMessage() const;
};