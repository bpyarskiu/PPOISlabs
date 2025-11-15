#pragma once
#include <string>

class Discount {
private:
    double percentage;
    std::string description;

public:
    Discount(double percentage = 0.0, const std::string& description = "");
    
    // Геттеры
    double getPercentage() const;
    std::string getDescription() const;
    
    // Основной метод - не изменяет состояние, а возвращает результат
    double calculateDiscountedPrice(double originalPrice) const;
    
    // Вспомогательные методы
    bool isValid() const;
    void display() const;

private:
    bool validatePercentage(double percentage) const;
    bool validatePrice(double price) const;
};