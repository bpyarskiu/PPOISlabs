#include "Complaint.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>

using namespace std;

Complaint::Complaint(const string& title, const string& description)
    : title(title), description(description), status("Pending") {
    
    date = chrono::system_clock::now();
    
    if (title.empty()) {
        throw invalid_argument("Complaint title cannot be empty");
    }
}

string Complaint::getTitle() const { 
    return title; 
}

string Complaint::getDescription() const { 
    return description; 
}

string Complaint::getStatus() const { 
    return status; 
}

chrono::system_clock::time_point Complaint::getDate() const { 
    return date; 
}

void Complaint::resolve() {
    status = "Resolved";
}

void Complaint::escalate() {
    status = "Escalated";
}

bool Complaint::isResolved() const {
    return status == "Resolved";
}

void Complaint::display() const {
    auto time = chrono::system_clock::to_time_t(date);
    
    cout << "=== COMPLAINT ===" << endl;
    cout << "Title: " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Status: " << status << endl;
    cout << "Date: " << ctime(&time);
    cout << "=================" << endl;
}