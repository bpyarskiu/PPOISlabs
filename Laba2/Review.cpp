#include "Review.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>

using namespace std;

Review::Review(const string& author, int rating, const string& comment)
    : author(author), rating(rating), comment(comment) {
    
    date = chrono::system_clock::now();
    
    if (author.empty()) {
        throw invalid_argument("Review author cannot be empty");
    }
    if (!validateRating(rating)) {
        throw invalid_argument("Invalid rating value");
    }
}

string Review::getAuthor() const { 
    return author; 
}

int Review::getRating() const { 
    return rating; 
}

string Review::getComment() const { 
    return comment; 
}

chrono::system_clock::time_point Review::getDate() const { 
    return date; 
}

bool Review::isPositive() const {
    return rating >= 4;
}

void Review::display() const {
    auto time = chrono::system_clock::to_time_t(date);
    
    cout << "Author: " << author << endl;
    cout << "Rating: " << rating << "/5" << endl;
    if (!comment.empty()) {
        cout << "Comment: " << comment << endl;
    }
    cout << "Date: " << ctime(&time);
    cout << "Type: " << (isPositive() ? "Positive" : "Needs improvement") << endl;
}

bool Review::validateRating(int rating) const {
    return rating >= 1 && rating <= 5;
}