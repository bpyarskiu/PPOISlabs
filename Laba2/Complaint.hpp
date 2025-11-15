#pragma once
#include <string>
#include <chrono>

class Complaint {
private:
    std::string title;
    std::string description;
    std::string status;
    std::chrono::system_clock::time_point date;

public:
    Complaint(const std::string& title, const std::string& description);
    
    // Геттеры
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getStatus() const;
    std::chrono::system_clock::time_point getDate() const;
    
    // Методы для изменения состояния
    void resolve();
    void escalate();
    
    // Вспомогательные методы
    bool isResolved() const;
    void display() const;
};