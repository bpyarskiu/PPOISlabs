#include "BusStop.hpp"
#include <iostream>

using namespace std;

BusStop::BusStop(const string& name, const string& location, 
                 const chrono::minutes& stopDuration, int sequenceNumber)
    : name(name), location(location), stopDuration(stopDuration), sequenceNumber(sequenceNumber) {
    
    // Простые проверки
    if (name.empty()) {
        throw invalid_argument("Stop name cannot be empty");
    }
    if (location.empty()) {
        throw invalid_argument("Stop location cannot be empty");
    }
    if (stopDuration.count() <= 0) {
        throw invalid_argument("Stop duration must be positive");
    }
    if (sequenceNumber <= 0) {
        throw invalid_argument("Sequence number must be positive");
    }
}

string BusStop::getName() const { return name; }

string BusStop::getLocation() const { return location; }

chrono::minutes BusStop::getStopDuration() const { return stopDuration; }

int BusStop::getSequenceNumber() const { return sequenceNumber; }

void BusStop::displayStopInfo() const {
    cout << "Stop #" << sequenceNumber << ": " << name << endl
         << "Location: " << location << endl
         << "Duration: " << stopDuration.count() << " minutes" << endl
         << "Type: " << (isLongStop() ? "Long stop" : "Short stop") << endl;
}

bool BusStop::isLongStop() const {
    return stopDuration > chrono::minutes(15);
}

string BusStop::getStopSummary() const {
    return "Stop " + to_string(sequenceNumber) + ": " + name + " (" + location + ") - " + 
           to_string(stopDuration.count()) + " min";
}