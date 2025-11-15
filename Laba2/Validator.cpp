#include "Validator.hpp"
#include <stdexcept>

using namespace std;

bool Validator::isValidEmail(const string& email) {
    // Простая проверка email с помощью regex
    regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, emailRegex);
}

bool Validator::isValidPhone(const string& phone) {
    // Проверка телефона: +7(XXX)XXX-XX-XX или 8XXXXXXXXXX или другие форматы
    regex phoneRegex(R"(^(\+7|8|+375)?[\s\-]?\(?[0-9]{3}\)?[\s\-]?[0-9]{3}[\s\-]?[0-9]{2}[\s\-]?[0-9]{2}$)");
    return regex_match(phone, phoneRegex);
}

bool Validator::isValidName(const string& name) {
    // Имя должно содержать только буквы, пробелы, дефисы и апострофы
    if (name.empty() || name.length() < 2) return false;
    regex nameRegex(R"(^[a-zA-Zа-яА-ЯёЁ\s\-']+$)");
    return regex_match(name, nameRegex);
}

bool Validator::isValidPrice(double price) {
    return price >= 0.0;
}

bool Validator::isValidRating(double rating) {
    return rating >= 0.0 && rating <= 5.0;
}

bool Validator::isValidId(int id) {
    return id > 0;
}

void Validator::validateEmail(const string& email) {
    if (!isValidEmail(email)) {
        throw invalid_argument("Invalid email format: " + email);
    }
}

void Validator::validatePhone(const string& phone) {
    if (!isValidPhone(phone)) {
        throw invalid_argument("Invalid phone format: " + phone);
    }
}

void Validator::validateName(const string& name) {
    if (!isValidName(name)) {
        throw invalid_argument("Invalid name format: " + name);
    }
}

void Validator::validatePrice(double price) {
    if (!isValidPrice(price)) {
        throw invalid_argument("Price cannot be negative: " + to_string(price));
    }
}

void Validator::validateRating(double rating) {
    if (!isValidRating(rating)) {
        throw invalid_argument("Rating must be between 0 and 5: " + to_string(rating));
    }
}

void Validator::validateId(int id) {
    if (!isValidId(id)) {
        throw invalid_argument("ID must be positive: " + to_string(id));
    }
}