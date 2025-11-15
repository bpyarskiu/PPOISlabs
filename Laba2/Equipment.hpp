#pragma once
#include <string>

class Equipment {
private:
    std::string name;
    std::string condition;
    int quantity;

public:
    Equipment(const std::string& name, const std::string& condition = "Good", int quantity = 1);
    
    // Геттеры
    std::string getName() const;
    std::string getCondition() const;
    int getQuantity() const;
    
    // Методы для изменения состояния
    void use();
    void repair();
    void addQuantity(int amount);
    
    // Вспомогательные методы
    bool isUsable() const;
    void display() const;

private:
    bool validateQuantity(int quantity) const;
};