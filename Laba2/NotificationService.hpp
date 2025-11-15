#pragma once
#include "Client.hpp"
#include "Booking.hpp"
#include <string>
#include <chrono>
#include <vector>

enum class NotificationType {
    BOOKING_CONFIRMATION,
    PAYMENT_REMINDER,
    TOUR_REMINDER,
    VISA_UPDATE,
    SPECIAL_OFFER,
    SYSTEM_ALERT
};

class NotificationService {
private:
    int notificationId;
    std::shared_ptr<Client> client;
    NotificationType type;
    std::string message;
    std::chrono::system_clock::time_point sentDate;
    bool isRead;

public:
    NotificationService(int notificationId, const std::shared_ptr<Client>& client,
                       NotificationType type, const std::string& message);

    // Геттеры
    int getNotificationId() const;
    std::shared_ptr<Client> getClient() const;
    NotificationType getType() const;
    std::string getMessage() const;
    std::chrono::system_clock::time_point getSentDate() const;
    bool getIsRead() const;

    // Методы
    void sendNotification();
    void markAsRead();
    void markAsUnread();
    std::string getNotificationTitle() const;
    void displayNotification() const;

    // Статические методы
    static void sendBookingConfirmation(const std::shared_ptr<Client>& client, 
                                       const std::shared_ptr<Booking>& booking);
    static void sendPaymentReminder(const std::shared_ptr<Client>& client,
                                   const std::shared_ptr<Booking>& booking);
    static void sendTourReminder(const std::shared_ptr<Client>& client,
                                const std::shared_ptr<Booking>& booking);

private:
    void validateNotificationData() const;
};