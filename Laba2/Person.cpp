#include "Person.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Person::Person(int id, const string& firstName, const string& lastName, 
               const ContactInfo& contact)
    : id(id), firstName(firstName), lastName(lastName), contact(contact) {
    
    if (id <= 0) {
        throw invalid_argument("Invalid person ID");
    }
    if (!validateName(firstName) || !validateName(lastName)) {
        throw invalid_argument("Invalid person name");
    }
}

int Person::getId() const { 
    return id; 
}

string Person::getFirstName() const { 
    return firstName; 
}

string Person::getLastName() const { 
    return lastName; 
}

ContactInfo Person::getContactInfo() const { 
    return contact; 
}

string Person::getFullName() const {
    return firstName + " " + lastName;
}

void Person::display() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << getFullName() << endl;
    contact.display();
}

bool Person::validateName(const string& name) const {
    return !name.empty() && name.length() >= 2;
}