#pragma once
#include "Employee.hpp"
#include "License.hpp"
#include <vector>
#include <string>
#include <memory>

class Driver : public Employee {
private:
    std::string licenseCategory;
    std::vector<std::string> permittedVehicleTypes;
    int drivingExperience;
    double safetyRating;
    std::shared_ptr<License> license;

public:
    Driver(int id, const std::string& firstName, const std::string& lastName,
           const ContactInfo& contact, int employeeId, 
           const std::string& position, double salary,
           const std::string& licenseCategory,
           const std::vector<std::string>& permittedVehicleTypes,
           int drivingExperience, double safetyRating,
           const std::shared_ptr<License>& license = nullptr);

    std::string getLicenseCategory() const;
    const std::vector<std::string>& getPermittedVehicleTypes() const;
    int getDrivingExperience() const;
    double getSafetyRating() const;
    std::shared_ptr<License> getLicense() const;
    
    void setLicense(const std::shared_ptr<License>& newLicense);
    bool hasValidLicense() const;
    bool canDriveVehicle(const std::string& vehicleType) const;
    void completeTrip();
    void displayInfo() const;
};