#include "NotificationManager.hpp"
#include <iostream>

using namespace std;

NotificationManager::NotificationManager(const shared_ptr<Company>& company) 
    : company(company) {}

void NotificationManager::sendTourReminders() const {
    auto clients = company->getClients();
    string message = generateTourReminderMessage();
    
    cout << "=== SENDING TOUR REMINDERS ===" << endl;
    for (const auto& client : clients) {
        if (client) {
            cout << "To: " << client->getContactInfo().getEmail() << endl;
            cout << "Message: " << message << endl;
            cout << "---" << endl;
        }
    }
    cout << "Sent to " << clients.size() << " clients" << endl;
}

void NotificationManager::sendPaymentReminders() const {
    cout << "=== SENDING PAYMENT REMINDERS ===" << endl;
    
    auto bookings = company->getBookings();
    int count = 0;
    
    for (const auto& booking : bookings) {
        if (booking) {
            // В реальной системе здесь была бы проверка статуса оплаты
            cout << "Payment reminder for booking #" << booking->getBookingId() << endl;
            count++;
        }
    }
    
    cout << "Sent " << count << " payment reminders" << endl;
}

void NotificationManager::sendSpecialOffers() const {
    auto clients = company->getClients();
    string message = generateSpecialOfferMessage();
    
    cout << "=== SENDING SPECIAL OFFERS ===" << endl;
    for (const auto& client : clients) {
        if (client) {
            cout << "To: " << client->getContactInfo().getEmail() << endl;
            cout << "Offer: " << message << endl;
            cout << "---" << endl;
        }
    }
    cout << "Sent to " << clients.size() << " clients" << endl;
}

void NotificationManager::sendSystemMaintenanceNotice() const {
    cout << "=== SYSTEM MAINTENANCE NOTICE ===" << endl;
    cout << "Sending maintenance notification to all employees..." << endl;
    
    auto employees = company->getEmployees();
    for (const auto& employee : employees) {
        if (employee) {
            cout << "Notified: " << employee->getFullName() << endl;
        }
    }
    cout << "Notifications sent: " << employees.size() << endl;
}

void NotificationManager::sendBirthdayGreetings() const {
    cout << "=== BIRTHDAY GREETINGS ===" << endl;
    cout << "Sending birthday greetings to clients..." << endl;
    
    // В реальной системе здесь была бы проверка дат рождения
    auto clients = company->getClients();
    int birthdayCount = min(3, (int)clients.size()); // Имитация
    
    cout << "Sent birthday greetings to " << birthdayCount << " clients" << endl;
}

void NotificationManager::sendAllNotifications() const {
    cout << "\n" << string(40, '=') << endl;
    cout << "SENDING ALL NOTIFICATIONS" << endl;
    cout << string(40, '=') << endl;
    
    sendTourReminders();
    cout << endl;
    sendPaymentReminders();
    cout << endl;
    sendSpecialOffers();
    cout << endl;
    sendSystemMaintenanceNotice();
    cout << endl;
    sendBirthdayGreetings();
    
    cout << string(40, '=') << endl;
    cout << "ALL NOTIFICATIONS COMPLETED" << endl;
}

vector<string> NotificationManager::getClientEmails() const {
    vector<string> emails;
    for (const auto& client : company->getClients()) {
        if (client) {
            emails.push_back(client->getContactInfo().getEmail());
        }
    }
    return emails;
}

string NotificationManager::generateTourReminderMessage() const {
    return "Don't forget about your upcoming tour! Check your booking details.";
}

string NotificationManager::generateSpecialOfferMessage() const {
    return "Special 20% discount on all tours this month! Book now!";
}