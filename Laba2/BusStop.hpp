#pragma once
#include <string>
#include <chrono>

class BusStop {
private:
    std::string name;
    std::string location;
    std::chrono::minutes stopDuration; // Время остановки в минутах
    int sequenceNumber; // Порядковый номер остановки в маршруте

public:
    BusStop(const std::string& name, const std::string& location, 
            const std::chrono::minutes& stopDuration, int sequenceNumber);

    // Геттеры
    std::string getName() const;
    std::string getLocation() const;
    std::chrono::minutes getStopDuration() const;
    int getSequenceNumber() const;

    // Простые методы
    void displayStopInfo() const;
    bool isLongStop() const; // Длительная остановка (> 15 минут)
    std::string getStopSummary() const;
};