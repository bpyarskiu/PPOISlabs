#include "Guide.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Guide::Guide(int id, const string& firstName, const string& lastName,
             const ContactInfo& contact, int employeeId, 
             const string& position, double salary,
             const vector<string>& languages,
             const vector<string>& specializations,
             int experienceYears, double rating)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      languages(languages), specializations(specializations),
      experienceYears(experienceYears), rating(rating) {
    
    if (languages.empty()) {
        throw invalid_argument("Guide must speak at least one language");
    }
}

const vector<string>& Guide::getLanguages() const { return languages; }
const vector<string>& Guide::getSpecializations() const { return specializations; }
int Guide::getExperienceYears() const { return experienceYears; }
double Guide::getRating() const { return rating; }

void Guide::addLanguage(const string& language) {
    if (language.empty()) {
        throw invalid_argument("Language cannot be empty");
    }
    if (find(languages.begin(), languages.end(), language) == languages.end()) {
        languages.push_back(language);
    }
}

void Guide::addSpecialization(const string& specialization) {
    if (specialization.empty()) {
        throw invalid_argument("Specialization cannot be empty");
    }
    if (find(specializations.begin(), specializations.end(), specialization) == specializations.end()) {
        specializations.push_back(specialization);
    }
}

bool Guide::speaksLanguage(const string& language) const {
    return find(languages.begin(), languages.end(), language) != languages.end();
}

void Guide::displayInfo() const {
    display();
     cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
    cout << "Experience: " << experienceYears << " years" << endl;
    cout << "Rating: " << rating << "/5" << endl;
    cout << "Languages: ";
    for (const auto& lang : languages) {
        cout << lang << " ";
    }
    cout << endl << "Specializations: ";
    for (const auto& spec : specializations) {
        cout << spec << " ";
    }
    cout << endl;
}