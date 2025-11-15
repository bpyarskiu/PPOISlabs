#pragma once
#include <string>

class Price {
private:
    double amount;
    std::string currency;

public:
    Price(double amount = 0.0, const std::string& currency = "RUB");
    
    // Геттеры
    double getAmount() const;
    std::string getCurrency() const;
    
    // Методы, возвращающие новые объекты (не изменяют текущий)
    Price add(const Price& other) const;
    Price multiply(double factor) const;
    
    // Вспомогательные методы
    void display() const;

private:
    bool validateAmount(double amount) const;
    bool validateCurrency(const std::string& currency) const;
};