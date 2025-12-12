#include <UnitTest++/UnitTest++.h>
#include "../Company.hpp"
#include "../Client.hpp"
#include "../Manager.hpp"  // Используем конкретный класс вместо Employee
#include "../Address.hpp"
#include "../ContactInfo.hpp"
#include "../Consultant.hpp"  // Или другой конкретный класс
#include <memory>
#include "HELPERFILE.cpp"

using namespace std;

SUITE(CompanyTests) {
    TEST(ValidCompanyCreation) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_EQUAL("Test Company", company.getName());
        CHECK_EQUAL(2020, company.getFoundationYear());
    }
    
    TEST(InvalidCompanyNameThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        CHECK_THROW(Company("", 2020, address), invalid_argument);
    }
    
    TEST(InvalidFoundationYearThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        CHECK_THROW(Company("Test", 1700, address), invalid_argument);
        CHECK_THROW(Company("Test", 2030, address), invalid_argument);
    }
    
    TEST(AddClientToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        ContactInfo contact("client@email.com", "+79161234567");
        auto client = make_shared<Client>(1, "John", "Doe", contact, 1001);
        
        company.addClient(client);
        
        CHECK_EQUAL(1, company.getClients().size());
        CHECK_EQUAL("John Doe", company.getClients()[0]->getFullName());
    }
    
    TEST(AddNullClientThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addClient(nullptr), invalid_argument);
    }
    
    TEST(AddEmployeeToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        ContactInfo contact("employee@company.com", "+79161234567");
        
        // Используем конкретный класс Manager вместо абстрактного Employee
        vector<string> responsibilities = {"Management", "Planning"};
        auto manager = make_shared<Manager>(
            1, "Alice", "Smith", contact, 1001, 
            "Manager", 50000.0, responsibilities, 5, 10000.0
        );
        
        company.addEmployee(manager);
        
        CHECK_EQUAL(1, company.getEmployees().size());
        CHECK_EQUAL("Alice Smith", company.getEmployees()[0]->getFullName());
    }
    
    TEST(AddDifferentTypesOfEmployees) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        ContactInfo contact1("manager@company.com", "+79161234567");
        ContactInfo contact2("consultant@company.com", "+79161234568");
        
        // Добавляем Manager
        vector<string> managerResponsibilities = {"Team Management"};
        auto manager = make_shared<Manager>(
            1, "Alice", "Smith", contact1, 1001, 
            "Manager", 50000.0, managerResponsibilities, 3, 5000.0
        );
        
        // Добавляем Consultant
        vector<string> specializations = {"Travel", "Hotels"};
        auto consultant = make_shared<Consultant>(
            2, "Bob", "Johnson", contact2, 1002,
            "Senior Consultant", 45000.0, specializations, 10, 0.1
        );
        
        company.addEmployee(manager);
        company.addEmployee(consultant);
        
        CHECK_EQUAL(2, company.getEmployees().size());
        
        // Проверяем, что оба объекта имеют правильные типы через dynamic_cast
        auto emp1 = company.getEmployees()[0];
        auto emp2 = company.getEmployees()[1];
        
        CHECK(dynamic_cast<Manager*>(emp1.get()) != nullptr);
        CHECK(dynamic_cast<Consultant*>(emp2.get()) != nullptr);
    }
    
    TEST(AddNullEmployeeThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addEmployee(nullptr), invalid_argument);
    }
    
    TEST(AddTourToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        // Создаем DateRange для тура
        auto now = chrono::system_clock::now();
        auto start = now + chrono::hours(24 * 7);  // Через неделю
        auto end = start + chrono::hours(24 * 10); // 10 дней
        DateRange dateRange(start, end);
        
        Price price(1000.0, "RUB");
        auto tour = make_shared<Tour>(
            1, "Moscow Tour", "Moscow", price, dateRange
        );
        
        company.addTour(tour);
        
        CHECK_EQUAL(1, company.getTours().size());
        CHECK_EQUAL("Moscow Tour", company.getTours()[0]->getName());
    }
    
    TEST(AddNullTourThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addTour(nullptr), invalid_argument);
    }
    
    TEST(AddEquipmentToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        auto equipment = make_shared<Equipment>("Tent", "Good", 5);
        company.addEquipment(equipment);
        
        CHECK_EQUAL(1, company.getEquipment().size());
        CHECK_EQUAL("Tent", company.getEquipment()[0]->getName());
    }
    
    TEST(AddNullEquipmentThrowsException) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        CHECK_THROW(company.addEquipment(nullptr), invalid_argument);
    }
    
    TEST(AddComplaintToCompany) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        auto complaint = make_shared<Complaint>("Bad service", "Service was terrible");
        company.addComplaint(complaint);
        
        CHECK_EQUAL(1, company.getComplaints().size());
        CHECK_EQUAL("Bad service", company.getComplaints()[0]->getTitle());
    }
    
    TEST(ResolveComplaint) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        auto complaint1 = make_shared<Complaint>("Complaint 1", "Description 1");
        auto complaint2 = make_shared<Complaint>("Complaint 2", "Description 2");
        
        company.addComplaint(complaint1);
        company.addComplaint(complaint2);
        
        // Разрешаем первую жалобу
        company.resolveComplaint(0);
        
        CHECK(company.getComplaints()[0]->isResolved());
        CHECK(!company.getComplaints()[1]->isResolved());
        
        // Пытаемся разрешить несуществующую жалобу (не должно быть исключения)
    }
    
    TEST(FindEquipment) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        company.addEquipment(make_shared<Equipment>("Tent", "Good", 5));
        company.addEquipment(make_shared<Equipment>("Backpack", "Good", 10));
        company.addEquipment(make_shared<Equipment>("Sleeping Bag", "Worn", 3));
        
        // Находим существующее оборудование
        Equipment* found = company.findEquipment("Backpack");
        CHECK(found != nullptr);
        CHECK_EQUAL("Backpack", found->getName());
        CHECK_EQUAL(10, found->getQuantity());
        
        // Не находим несуществующее оборудование
        Equipment* notFound = company.findEquipment("Kayak");
        CHECK(notFound == nullptr);
        
        // Поиск с пустым именем
        Equipment* emptySearch = company.findEquipment("");
        CHECK(emptySearch == nullptr);
    }
    
    TEST(DisplayCompanyInfo) {
        Address address("Main St", "Moscow", "Russia", "101000");
        Company company("Test Company", 2020, address);
        
        // Добавляем некоторые данные
        ContactInfo clientContact("client@test.com", "+79161234567");
        auto client = make_shared<Client>(1, "Test", "Client", clientContact, 1001);
        company.addClient(client);
        
        ContactInfo empContact("emp@test.com", "+79161234568");
        vector<string> responsibilities = {"Test"};
        auto manager = make_shared<Manager>(
            2, "Test", "Manager", empContact, 2001, 
            "Manager", 40000.0, responsibilities, 2, 5000.0
        );
        company.addEmployee(manager);
        
        StdoutRedirect redirect;
        company.displayCompanyInfo();
        string output = redirect.getOutput();
        
        CHECK(output.find("Name: Test Company") != string::npos);
        CHECK(output.find("Foundation Year: 2020") != string::npos);
        CHECK(output.find("Clients: 1") != string::npos);
        CHECK(output.find("Employees: 1") != string::npos);
    }
}