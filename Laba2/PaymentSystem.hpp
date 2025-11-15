#pragma once
#include "Booking.hpp"
#include <string>
#include <chrono>

enum class PaymentMethod {
    CREDIT_CARD,
    DEBIT_CARD,
    BANK_TRANSFER,
    CASH,
    ELECTRONIC_WALLET,
    PHONE_NUMBER
};

enum class PaymentStatus {
    PENDING,
    COMPLETED,
    FAILED,
    REFUNDED
};

class PaymentSystem {
private:
    int paymentId;
    std::shared_ptr<Booking> booking;
    double amount;
    PaymentMethod method;
    PaymentStatus status;
    std::chrono::system_clock::time_point paymentDate;
    std::string transactionId;

public:
    PaymentSystem(int paymentId, const std::shared_ptr<Booking>& booking,
                  double amount, PaymentMethod method);

    // Геттеры
    int getPaymentId() const;
    std::shared_ptr<Booking> getBooking() const;
    double getAmount() const;
    PaymentMethod getMethod() const;
    PaymentStatus getStatus() const;
    std::chrono::system_clock::time_point getPaymentDate() const;
    std::string getTransactionId() const;

    // Бизнес-методы
    bool processPayment();
    bool refundPayment();
    bool validatePayment() const;
    void generateReceipt() const;
    void displayPaymentInfo() const;

private:
    void validatePaymentData() const;
    std::string generateTransactionId() const;
};