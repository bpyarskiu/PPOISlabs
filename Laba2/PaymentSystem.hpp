#pragma once
#include "Booking.hpp"
#include <string>
#include <chrono>
#include <random>

enum class PaymentMethod {
    CREDIT_CARD,
    DEBIT_CARD, 
    BANK_TRANSFER
};

enum class PaymentStatus {
    PENDING,
    COMPLETED,
    FAILED
};

class PaymentResult {
private:
    bool success;
    std::string transactionId;
    std::string message;

public:
    PaymentResult(bool success, const std::string& transactionId, const std::string& message = "")
        : success(success), transactionId(transactionId), message(message) {}
    
    bool isSuccess() const { return success; }
    std::string getTransactionId() const { return transactionId; }
    std::string getMessage() const { return message; }
};

class PaymentDetails {
private:
    double amount;
    std::string currency;
    std::string cardNumber;
    std::string expiryDate;

public:
    PaymentDetails(double amount, const std::string& currency, 
                   const std::string& cardNumber, const std::string& expiryDate)
        : amount(amount), currency(currency), cardNumber(cardNumber), expiryDate(expiryDate) {}
    
    double getAmount() const { return amount; }
    std::string getCurrency() const { return currency; }
    std::string getCardNumber() const { return cardNumber; }
    std::string getExpiryDate() const { return expiryDate; }
};

class PaymentSystem {
public:
    PaymentSystem() = default;  // Конструктор по умолчанию
    
    PaymentResult processPayment(const PaymentDetails& details) {
        // Валидация данных
        if (details.getAmount() <= 0) {
            return PaymentResult(false, "", "Invalid amount");
        }
        
        if (details.getCardNumber().length() != 16) {
            return PaymentResult(false, "", "Invalid card number");
        }
        
        // Имитация обработки платежа (90% успеха)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 9);
        
        bool success = (dis(gen) < 9); // 90% chance of success
        
        if (success) {
            std::string transactionId = generateTransactionId();
            return PaymentResult(true, transactionId, "Payment processed successfully");
        } else {
            return PaymentResult(false, "", "Payment processing failed");
        }
    }

private:
    std::string generateTransactionId() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        
        return "TXN" + std::to_string(dis(gen));
    }
};