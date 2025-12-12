#include "Validator.hpp"
#include <stdexcept>

using namespace std;

bool Validator::isValidEmail(const std::string& email) {
        if (email.empty()) return false;
        
        // Простая проверка email
        size_t at_pos = email.find('@');
        size_t dot_pos = email.find('.', at_pos);
        
        return (at_pos != std::string::npos && 
                dot_pos != std::string::npos &&
                at_pos > 0 && 
                dot_pos > at_pos + 1 &&
                dot_pos < email.length() - 1);
    }

  bool Validator::isValidPhone(const std::string& phone) {
        if (phone.empty()) return false;
        
        // Простая проверка телефона
        // Должен начинаться с + и иметь достаточно цифр
        if (phone[0] != '+') return false;
        if (phone.length() < 10) return false;
        
        // Проверяем что остальные символы - цифры
        for (size_t i = 1; i < phone.length(); ++i) {
            if (!std::isdigit(phone[i])) return false;
        }
        
        return true;
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