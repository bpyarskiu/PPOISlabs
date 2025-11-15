#pragma once
#include "Employee.hpp"
#include <vector>
#include <string>

class Guide : public Employee {
private:
    std::vector<std::string> languages;
    std::vector<std::string> specializations;
    int experienceYears;
    double rating;

public:
    Guide(int id, const std::string& firstName, const std::string& lastName,
          const ContactInfo& contact, int employeeId, 
          const std::string& position, double salary,
          const std::vector<std::string>& languages,
          const std::vector<std::string>& specializations,
          int experienceYears, double rating);

    const std::vector<std::string>& getLanguages() const;
    const std::vector<std::string>& getSpecializations() const;
    int getExperienceYears() const;
    double getRating() const;

    void addLanguage(const std::string& language);
    void addSpecialization(const std::string& specialization);
    bool speaksLanguage(const std::string& language) const;
    void displayInfo() const;
};