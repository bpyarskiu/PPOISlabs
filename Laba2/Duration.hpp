#pragma once
#include <chrono>
#include <string>

class Duration {
private:
    std::chrono::hours hours;

public:
    Duration(int hours = 0);
    
    // Геттеры
    int getHours() const;
    int getDays() const;
    
    // Метод для изменения состояния
    void addHours(int additionalHours);
    
    // Вспомогательные методы
    std::string getFormatted() const;
    void display() const;

private:
    bool validateHours(int hours) const;
};