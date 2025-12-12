#include "Tour.hpp"
#include <iostream>

using namespace std;

Tour::Tour(int tourId, const string& name, const string& destination, 
           const Price& basePrice, const DateRange& dateRange)
    : tourId(tourId), name(name), destination(destination), 
      basePrice(basePrice), dateRange(dateRange) {
    
    if (name.empty() || destination.empty()) {
        throw invalid_argument("Tour name and destination cannot be empty");
    }
}

int Tour::getTourId() const { return tourId; }
string Tour::getName() const { return name; }
string Tour::getDestination() const { return destination; }
Price Tour::getBasePrice() const { return basePrice; }
DateRange Tour::getDateRange() const { return dateRange; }
const vector<shared_ptr<Accommodation>>& Tour::getAccommodations() const { return accommodations; }
const vector<shared_ptr<Transport>>& Tour::getTransports() const { return transports; }
std::shared_ptr<Insurance> Tour::getInsurance() const{return insurance;}
std::shared_ptr<MealPlan> Tour::getMealPlan() const{return mealPlan;}
const std::vector<std::shared_ptr<Review>>& Tour::getReviews() const{return reviews;}

void Tour::addAccommodation(const shared_ptr<Accommodation>& accommodation) {
    if (!accommodation) {
        throw invalid_argument("Cannot add null accommodation");
    }
    accommodations.push_back(accommodation);
}

void Tour::addTransport(const shared_ptr<Transport>& transport) {
    if (!transport) {
        throw invalid_argument("Cannot add null transport");
    }
    transports.push_back(transport);
}

void Tour::addReview(const std::shared_ptr<Review>& review){
  if (!review) {
        throw invalid_argument("Cannot add null review");
    }
    reviews.push_back(review);
}

void Tour::setMealPlan(const shared_ptr<MealPlan>& mealPlan) {
    this->mealPlan = mealPlan;
}

void Tour::setInsurance(const std::shared_ptr<Insurance>& insurance){
    this->insurance=insurance;
}

Price Tour::
calculateTotalPrice() const {
    Price total = basePrice;
    int nights = getTourDurationDays();
    
    // Стоимость проживания
    for (const auto& accommodation : accommodations) {
        if (accommodation) {
            total = total.add(accommodation->calculateTotalCost(nights));
        }
    }
    
    // Стоимость транспорта
    for (const auto& transport : transports) {
        if (transport) {
            total = total.add(transport->getPrice());
        }
    }
    
    // Стоимость страховки
    if (insurance) {
        total = total.add(insurance->getPrice());
    }
    
    // Стоимость питания
    if (mealPlan) {
        total = total.add(mealPlan->calculateTotalCost(nights));
    }
    
    return total;
}


bool Tour::isActive() const {
    auto now = chrono::system_clock::now();
    return dateRange.isDateInRange(now);
}

double Tour::getAverageRating() const{
    // Если отзывов нет, возвращаем 0.0
    if (reviews.empty()) {
        return 0.0;
    }
    
    int totalRating = 0;
    int validReviewsCount = 0;
    
    // Проходим по всем отзывам
    for (const auto& reviewPtr : reviews) {
        // Проверяем, что shared_ptr не nullptr
        if (reviewPtr) {
            totalRating += reviewPtr->getRating();
            validReviewsCount++;
        }
    }
    
    // Если все shared_ptr были nullptr
    if (validReviewsCount == 0) {
        return 0.0;
    }
    
    // Вычисляем среднее значение
    return static_cast<double>(totalRating) / validReviewsCount;

}

void Tour::displayTourInfo() const {
    cout << "=== TOUR INFORMATION ===" << endl;
    cout << "Tour ID: " << tourId << endl;
    cout << "Name: " << name << endl;
    cout << "Destination: " << destination << endl;
    cout << "Duration: " << getTourDurationDays() << " days" << endl;
    cout << "Base Price: ";
    basePrice.display();
    cout << "Total Price: ";
    calculateTotalPrice().display();
    cout << "Status: " << (isActive() ? "Active" : "Inactive") << endl;
    cout << "Accommodations: " << accommodations.size() << endl;
    cout << "Transports: " << transports.size() << endl;
    cout << "Insurance: " << (insurance ? "Included" : "Not included") << endl;
    cout << "Meal Plan: " << (mealPlan ? mealPlan->getType() : "Not included") << endl;
    cout << "Reviews: " << reviews.size() << endl;
    cout << "========================" << endl;
}

void Tour::displayReviews() const{
    if (reviews.empty()) {
        std::cout << "No reviews available.\n";
        return;
    }
    for (size_t i = 0; i < reviews.size(); ++i) {
        std::cout << "\n--- Review #" << (i + 1) << " ---\n";
        if (reviews[i]) {
            reviews[i]->display();
        } else {
            std::cout << "[Invalid review pointer]\n";
        }
    }
    std::cout << "========================\n";
}

int Tour::getTourDurationDays() const {
    return dateRange.getDurationDays();
}