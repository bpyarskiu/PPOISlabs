#pragma once
#include <stdexcept>
#include <string>

class PaymentProcessingException : public std::runtime_error {
public:
    explicit PaymentProcessingException(const std::string& message)
        : std::runtime_error("Payment Processing Error: " + message) {}
};

class CurrencyConversionException : public std::runtime_error {
public:
    explicit CurrencyConversionException(const std::string& message)
        : std::runtime_error("Currency Conversion Error: " + message) {}
};

class VisaProcessingException : public std::runtime_error {
public:
    explicit VisaProcessingException(const std::string& message)
        : std::runtime_error("Visa Processing Error: " + message) {}
};

class GuideNotAvailableException : public std::runtime_error {
public:
    explicit GuideNotAvailableException(const std::string& message)
        : std::runtime_error("Guide Not Available: " + message) {}
};

class TransportNotAvailableException : public std::runtime_error {
public:
    explicit TransportNotAvailableException(const std::string& message)
        : std::runtime_error("Transport Not Available: " + message) {}
};

class DataValidationException : public std::runtime_error {
public:
    explicit DataValidationException(const std::string& message)
        : std::runtime_error("Data Validation Error: " + message) {}
};

class ResourceNotFoundException : public std::runtime_error {
public:
    explicit ResourceNotFoundException(const std::string& message)
        : std::runtime_error("Resource Not Found: " + message) {}
};

class DatabaseConnectionException : public std::runtime_error {
public:
    explicit DatabaseConnectionException(const std::string& message)
        : std::runtime_error("Database Connection Error: " + message) {}
};

class AuthorizationException : public std::runtime_error {
public:
    explicit AuthorizationException(const std::string& message)
        : std::runtime_error("Authorization Error: " + message) {}
};

class BookingConflictException : public std::runtime_error {
public:
    explicit BookingConflictException(const std::string& message)
        : std::runtime_error("Booking Conflict: " + message) {}
};

class InvalidDateException : public std::runtime_error {
public:
    explicit InvalidDateException(const std::string& message)
        : std::runtime_error("Invalid Date: " + message) {}
};

class NetworkCommunicationException : public std::runtime_error {
public:
    explicit NetworkCommunicationException(const std::string& message)
        : std::runtime_error("Network Communication Error: " + message) {}
};