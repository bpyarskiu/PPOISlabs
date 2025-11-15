#pragma once
#include <string>

class Coordinates {
private:
    double latitude;
    double longitude;

public:
    Coordinates(double latitude = 0.0, double longitude = 0.0);
    
    // Геттеры
    double getLatitude() const;
    double getLongitude() const;
    
    // Основной метод - не изменяет состояние
    double calculateDistance(const Coordinates& other) const;
    
    // Вспомогательные методы
    bool isValid() const;
    void display() const;

private:
    bool validateLatitude(double latitude) const;
    bool validateLongitude(double longitude) const;
};