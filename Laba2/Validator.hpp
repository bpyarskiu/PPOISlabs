#pragma once
#include <string>
#include <regex>
#include <stdexcept>

class Validator {
public:
    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
    static bool isValidName(const std::string& name);
    static bool isValidPrice(double price);
    static bool isValidRating(double rating);
    static bool isValidId(int id);
    
    static void validateEmail(const std::string& email);
    static void validatePhone(const std::string& phone);
    static void validateName(const std::string& name);
    static void validatePrice(double price);
    static void validateRating(double rating);
    static void validateId(int id);
};