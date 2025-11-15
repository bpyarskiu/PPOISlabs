#include "NotificationService.hpp"
#include "CustomExceptions.hpp"
#include <iostream>

using namespace std;

NotificationService::NotificationService(int notificationId, const shared_ptr<Client>& client,
                                         NotificationType type, const string& message)
    : notificationId(notificationId), client(client), type(type), message(message),
      sentDate(chrono::system_clock::now()), isRead(false) {
    
    validateNotificationData();
}

int NotificationService::getNotificationId() const { return notificationId; }

shared_ptr<Client> NotificationService::getClient() const { return client; }

NotificationType NotificationService::getType() const { return type; }

string NotificationService::getMessage() const { return message; }

chrono::system_clock::time_point NotificationService::getSentDate() const { return sentDate; }

bool NotificationService::getIsRead() const { return isRead; }

void NotificationService::sendNotification() {
    if (!client) {
        throw ResourceNotFoundException("Client not found for notification");
    }
    
    cout << "Sending notification to " << client->getEmail()<< ":" << endl
         << "Title: " << getNotificationTitle() << endl
         << "Message: " << message << endl
         << "Notification sent successfully!" << endl;
}

void NotificationService::markAsRead() {
    isRead = true;
}

void NotificationService::markAsUnread() {
    isRead = false;
}

string NotificationService::getNotificationTitle() const {
    switch (type) {
        case NotificationType::BOOKING_CONFIRMATION: return "Booking Confirmation";
        case NotificationType::PAYMENT_REMINDER: return "Payment Reminder";
        case NotificationType::TOUR_REMINDER: return "Tour Reminder";
        case NotificationType::VISA_UPDATE: return "Visa Status Update";
        case NotificationType::SPECIAL_OFFER: return "Special Offer";
        case NotificationType::SYSTEM_ALERT: return "System Alert";
        default: return "Notification";
    }
}

void NotificationService::displayNotification() const {
    validateNotificationData();
    
    auto time = chrono::system_clock::to_time_t(sentDate);
    cout << "[" << (isRead ? "READ" : "UNREAD") << "] "
         << getNotificationTitle() << " - " << ctime(&time)
         << "Message: " << message << endl;
}

void NotificationService::sendBookingConfirmation(const shared_ptr<Client>& client, 
                                                  const shared_ptr<Booking>& booking) {
    if (!client || !booking) {
        throw ResourceNotFoundException("Client or booking not found");
    }
    
    string message = "Your booking #" + to_string(booking->getBookingId()) + " has been confirmed!";
    NotificationService notification(0, client, NotificationType::BOOKING_CONFIRMATION, message);
    notification.sendNotification();
}

void NotificationService::sendPaymentReminder(const shared_ptr<Client>& client,
                                              const shared_ptr<Booking>& booking) {
    if (!client || !booking) {
        throw ResourceNotFoundException("Client or booking not found");
    }
    
    string message = "Reminder: Payment for booking #" + to_string(booking->getBookingId()) + " is due.";
    NotificationService notification(0, client, NotificationType::PAYMENT_REMINDER, message);
    notification.sendNotification();
}

void NotificationService::sendTourReminder(const shared_ptr<Client>& client,
                                           const shared_ptr<Booking>& booking) {
    if (!client || !booking) {
        throw ResourceNotFoundException("Client or booking not found");
    }
    
    string message = "Reminder: Your tour starts soon! Booking #" + to_string(booking->getBookingId());
    NotificationService notification(0, client, NotificationType::TOUR_REMINDER, message);
    notification.sendNotification();
}

void NotificationService::validateNotificationData() const {
    if (notificationId <= 0) {
        throw DataValidationException("Invalid notification ID");
    }
    
    if (!client) {
        throw ResourceNotFoundException("Client not specified for notification");
    }
    
    if (message.empty()) {
        throw DataValidationException("Notification message cannot be empty");
    }
}