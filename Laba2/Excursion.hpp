#pragma once
#include <string>
#include "Validator.hpp"

class Excursion {
private:
    int excursionId;
    std::string title;
    std::string description;
    std::string city;
    double durationHours;
    double pricePerPerson;

public:
    Excursion(int excursionId, const std::string& title, 
              const std::string& description, const std::string& city,
              double durationHours, double pricePerPerson);

    // Геттеры
    int getExcursionId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getCity() const;
    double getDurationHours() const;
    double getPricePerPerson() const;

    // Сеттеры
    void setExcursionId(int excursionId);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setCity(const std::string& city);
    void setDurationHours(double durationHours);
    void setPricePerPerson(double pricePerPerson);
};
