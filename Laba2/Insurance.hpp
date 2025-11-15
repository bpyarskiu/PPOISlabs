#pragma once
#include "Price.hpp"
#include "Duration.hpp"
#include <string>

class Insurance {
private:
    std::string type;
    Price price;
    std::string coverage;
    Duration duration;

public:
    Insurance(const std::string& type, const Price& price, 
              const std::string& coverage, const Duration& duration);
    
    // Геттеры
    std::string getType() const;
    Price getPrice() const;
    std::string getCoverage() const;
    Duration getDuration() const;
    
    // Вспомогательные методы
    void display() const;

private:
    bool validateType(const std::string& type) const;
};