#pragma once
#include "Price.hpp"
#include "DateRange.hpp"
#include "Accommodation.hpp"
#include "Transport.hpp"
#include "Review.hpp"
#include "Insurance.hpp"
#include "MealPlan.hpp"
#include <string>
#include <vector>
#include <memory>

class Tour {
private:
    int tourId;
    std::string name;
    std::string destination;
    Price basePrice;
    DateRange dateRange;
    std::vector<std::shared_ptr<Accommodation>> accommodations;
    std::vector<std::shared_ptr<Transport>> transports;
    std::vector<std::shared_ptr<Review>> reviews;
    std::shared_ptr<Insurance> insurance;
    std::shared_ptr<MealPlan> mealPlan;

public:
    Tour(int tourId, const std::string& name, const std::string& destination, 
         const Price& basePrice, const DateRange& dateRange);
    
    // Геттеры
    int getTourId() const;
    std::string getName() const;
    std::string getDestination() const;
    Price getBasePrice() const;
    DateRange getDateRange() const;
    const std::vector<std::shared_ptr<Accommodation>>& getAccommodations() const;
    const std::vector<std::shared_ptr<Transport>>& getTransports() const;
    const std::vector<std::shared_ptr<Review>>& getReviews() const;
    std::shared_ptr<Insurance> getInsurance() const;
    std::shared_ptr<MealPlan> getMealPlan() const;
    
    // Методы добавления
    void addAccommodation(const std::shared_ptr<Accommodation>& accommodation);
    void addTransport(const std::shared_ptr<Transport>& transport);
    void addReview(const std::shared_ptr<Review>& review);
    void setInsurance(const std::shared_ptr<Insurance>& insurance);
    void setMealPlan(const std::shared_ptr<MealPlan>& mealPlan);
    
    // Расчетные методы
    Price calculateTotalPrice() const;
    double getAverageRating() const;
    bool isActive() const;
    
    // Отображение
    void displayTourInfo() const;
    void displayReviews() const;

private:
    int getTourDurationDays() const;
};