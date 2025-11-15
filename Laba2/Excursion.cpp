#include "Excursion.hpp"

using namespace std;

Excursion::Excursion(int excursionId, const string& title, 
                     const string& description, const string& city,
                     double durationHours, double pricePerPerson) {
    setExcursionId(excursionId);
    setTitle(title);
    setDescription(description);
    setCity(city);
    setDurationHours(durationHours);
    setPricePerPerson(pricePerPerson);
}

int Excursion::getExcursionId() const { return excursionId; }

string Excursion::getTitle() const { return title; }

string Excursion::getDescription() const { return description; }

string Excursion::getCity() const { return city; }

double Excursion::getDurationHours() const { return durationHours; }

double Excursion::getPricePerPerson() const { return pricePerPerson; }

void Excursion::setExcursionId(int excursionId) {
    Validator::validateId(excursionId);
    this->excursionId = excursionId;
}

void Excursion::setTitle(const string& title) {
    if (title.empty()) {
        throw invalid_argument("Excursion title cannot be empty");
    }
    this->title = title;
}

void Excursion::setDescription(const string& description) {
    if (description.empty()) {
        throw invalid_argument("Description cannot be empty");
    }
    this->description = description;
}

void Excursion::setCity(const string& city) {
    if (city.empty()) {
        throw invalid_argument("City cannot be empty");
    }
    this->city = city;
}

void Excursion::setDurationHours(double durationHours) { 
    if (durationHours <= 0) {
        throw invalid_argument("Duration must be positive: " + to_string(durationHours));
    }
    this->durationHours = durationHours; 
}

void Excursion::setPricePerPerson(double pricePerPerson) { 
    Validator::validatePrice(pricePerPerson);
    this->pricePerPerson = pricePerPerson; 
}