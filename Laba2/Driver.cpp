#include "Driver.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Driver::Driver(int id, const string& firstName, const string& lastName,
               const ContactInfo& contact, int employeeId, 
               const string& position, double salary,
               const string& licenseCategory,
               const vector<string>& permittedVehicleTypes,
               int drivingExperience, double safetyRating,
               const shared_ptr<License>& license)
    : Employee(id, firstName, lastName, contact, employeeId, position, salary),
      licenseCategory(licenseCategory), permittedVehicleTypes(permittedVehicleTypes),
      drivingExperience(drivingExperience), safetyRating(safetyRating), license(license) {
    
    if (licenseCategory.empty()) {
        throw invalid_argument("License category cannot be empty");
    }

    if (permittedVehicleTypes.empty()) {
        throw invalid_argument("Driver must have at least one permitted vehicle type");
    }
}

string Driver::getLicenseCategory() const { return licenseCategory; }
const vector<string>& Driver::getPermittedVehicleTypes() const { return permittedVehicleTypes; }
int Driver::getDrivingExperience() const { return drivingExperience; }
double Driver::getSafetyRating() const { return safetyRating; }

bool Driver::canDriveVehicle(const string& vehicleType) const {
    return find(permittedVehicleTypes.begin(), permittedVehicleTypes.end(), vehicleType) != permittedVehicleTypes.end();
}
void Driver::setLicense(const shared_ptr<License>& newLicense) {
    license = newLicense;
}

bool Driver::hasValidLicense() const {
    return license && license->isValid() && license->canDriveCategory(licenseCategory);
}

void Driver::completeTrip() {
    if (safetyRating < 4.9) {
        safetyRating += 0.1;
    }
}

void Driver::displayInfo() const {
    display();
     cout << "Employee ID: " << employeeId << endl;
    cout << "Position: " << position << endl;
    cout << "Salary: " << salary << " RUB" << endl;
    cout << "License Category: " << licenseCategory << endl;
    cout << "Driving Experience: " << drivingExperience << " years" << endl;
    cout << "Safety Rating: " << safetyRating << "/5" << endl;
    cout << "Permitted Vehicles: ";
    for (const auto& vehicle : permittedVehicleTypes) {
        cout << vehicle << " ";
    }
    cout << endl;
    if (license) {
        cout << "Driver License: " << (hasValidLicense() ? "Valid" : "Invalid") << endl;
    }
}