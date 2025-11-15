#pragma once
#include "Company.hpp"
#include <memory>
#include <map>

class Statistics {
private:
    std::shared_ptr<Company> company;

public:
    Statistics(const std::shared_ptr<Company>& company);
    
    int getTotalClients() const;
    int getTotalEmployees() const;
    int getActiveTours() const;
    double getAverageTourRating() const;
    std::map<std::string, int> getToursByDestination() const;
    int getEquipmentCount() const;
    int getResolvedComplaintsCount() const;
    
    void displaySummary() const;
    void displayTourStatistics() const;
};