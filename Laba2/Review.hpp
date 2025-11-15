#pragma once
#include <string>
#include <chrono>

class Review {
private:
    std::string author;
    int rating;
    std::string comment;
    std::chrono::system_clock::time_point date;

public:
    Review(const std::string& author, int rating, const std::string& comment = "");
    
    // Геттеры
    std::string getAuthor() const;
    int getRating() const;
    std::string getComment() const;
    std::chrono::system_clock::time_point getDate() const;
    
    // Вспомогательные методы
    bool isPositive() const;
    void display() const;

private:
    bool validateRating(int rating) const;
};