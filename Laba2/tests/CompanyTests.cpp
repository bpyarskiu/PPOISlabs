#include <UnitTest++/UnitTest++.h>
#include "../Company.hpp"
#include "../Client.hpp"
#include "../Employee.hpp"
#include "../Address.hpp"
#include "../ContactInfo.hpp"

SUITE(CompanyTests) {
    TEST(ValidCompanyCreation) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_EQUAL("Test Company", company.getName());
        CHECK_EQUAL(2020, company.getFoundationYear());
    }
    
    TEST(InvalidCompanyNameThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        CHECK_THROW(Company("", 2020, address), std::invalid_argument);
    }
    
    TEST(InvalidFoundationYearThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        CHECK_THROW(Company("Test", 1700, address), std::invalid_argument);
        CHECK_THROW(Company("Test", 2030, address), std::invalid_argument);
    }
    
    TEST(AddClientToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        ContactInfo contact("client@email.com", "+79161234567");
        auto client = std::make_shared<Client>(1, "John", "Doe", contact, 1001);
        
        company.addClient(client);
        
        CHECK_EQUAL(1, company.getClients().size());
        CHECK_EQUAL("John Doe", company.getClients()[0]->getFullName());
    }
    
    TEST(AddNullClientThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addClient(nullptr), std::invalid_argument);
    }
    
    TEST(AddEmployeeToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        ContactInfo contact("employee@company.com", "+79161234567");
        auto employee = std::make_shared<Employee>(1, "Alice", "Smith", contact, 1001, "Manager", 50000.0);
        
        company.addEmployee(employee);
        
        CHECK_EQUAL(1, company.getEmployees().size());
        CHECK_EQUAL("Alice Smith", company.getEmployees()[0]->getFullName());
    }
    
    TEST(AddNullEmployeeThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addEmployee(nullptr), std::invalid_argument);
    }
}