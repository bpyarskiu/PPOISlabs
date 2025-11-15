#pragma once
#include "Price.hpp"
#include <string>

class MealPlan {
private:
    std::string type;
    Price pricePerDay;
    std::string description;

public:
    MealPlan(const std::string& type, const Price& price, const std::string& description = "");
    
    // Геттеры
    std::string getType() const;
    Price getPricePerDay() const;
    std::string getDescription() const;
    
    // Основной метод - не изменяет состояние
    Price calculateTotalCost(int days) const;
    
    // Вспомогательные методы
    void display() const;

private:
    bool validateDays(int days) const;
};