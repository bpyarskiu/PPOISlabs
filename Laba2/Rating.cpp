#include "Rating.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Rating::Rating() : value(0.0), votesCount(0) {}

Rating::Rating(double value, int totalVotes) : value(value), votesCount(totalVotes) {
    if (value < 0 || value > 5) {
        throw invalid_argument("Rating value must be between 0 and 5");
    }
    if (totalVotes < 0) {
        throw invalid_argument("Total votes cannot be negative");
    }
}


double Rating::getValue() const { 
    return value; 
}

int Rating::getVotesCount() const { 
    return votesCount; 
}

void Rating::addVote(double vote) {
    if (!validateVote(vote)) {
        throw invalid_argument("Invalid vote value");
    }
    
    double total = value * votesCount;
    votesCount++;
    value = (total + vote) / votesCount;
}

bool Rating::isValid() const {
    return votesCount > 0;
}

void Rating::display() const {
    cout << "Rating: " << value << "/5 (" << votesCount << " votes)" << endl;
}

bool Rating::validateVote(double vote) const {
    return vote >= 0.0 && vote <= 5.0;
}