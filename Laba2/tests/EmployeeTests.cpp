#include <UnitTest++/UnitTest++.h>
#include "../Employee.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <iostream>
#include <memory>

// Тестовый класс, реализующий абстрактный метод
class TestEmployee : public Employee {
public:
    TestEmployee(int id, const std::string& firstName, const std::string& lastName,
                 const ContactInfo& contact, int employeeId,
                 const std::string& position, double salary)
        : Employee(id, firstName, lastName, contact, employeeId, position, salary) {}
    
    // Реализация чисто виртуального метода
    void displayInfo() const override {
        std::cout << "Test Employee - " << getFullName() << std::endl;
    }
    
    // Для совместимости со старыми тестами
    void displayEmployeeInfo() const {
        display();  // Метод из Person
        std::cout << "Employee ID: " << getEmployeeId() << std::endl;
        std::cout << "Position: " << getPosition() << std::endl;
        std::cout << "Salary: " << getSalary() << " RUB" << std::endl;
    }
};

TEST(EmployeeTest_GetEmployeeId) {
    ContactInfo contact("employee@test.com", "+375293334455");
    TestEmployee employee(1, "John", "Doe", contact, 3001, "Manager", 50000.0);
    
    CHECK_EQUAL(3001, employee.getEmployeeId());
}

TEST(EmployeeTest_Display) {
    ContactInfo contact("employee@test.com", "+375293334455");
    TestEmployee employee(1, "John", "Doe", contact, 3001, "Manager", 50000.0);
    
    StdoutRedirect redirect;
    employee.display();  // Метод из Person
    std::string output = redirect.getOutput();
    
    CHECK(output.find("ID: 1") != std::string::npos);
    CHECK(output.find("Name: John Doe") != std::string::npos);
    CHECK(output.find("employee@test.com") != std::string::npos);
}

TEST(EmployeeTest_ConstructorValidation) {
    ContactInfo contact("employee@test.com", "+375293334455");
    
    // Тест валидации в конструкторе - пустая должность
    CHECK_THROW(TestEmployee invalidEmployee(1, "John", "Doe", contact, 3001, "", 50000.0),
               std::invalid_argument);
    
    // Тест валидации в конструкторе - отрицательная зарплата
    CHECK_THROW(TestEmployee invalidEmployee(2, "Jane", "Smith", contact, 3002, "Manager", -1000.0),
               std::invalid_argument);
    
    // Тест успешного создания
    TestEmployee validEmployee(3, "Bob", "Brown", contact, 3003, "Developer", 60000.0);
    CHECK_EQUAL("Developer", validEmployee.getPosition());
    CHECK_EQUAL(60000.0, validEmployee.getSalary());
}

TEST(EmployeeTest_DisplayInfo) {
    ContactInfo contact("manager@test.com", "+375294445566");
    TestEmployee employee(1, "Alice", "Johnson", contact, 4001, "Senior Manager", 80000.0);
    
    // Тест нового виртуального метода displayInfo()
    StdoutRedirect redirect;
    employee.displayInfo();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Test Employee - Alice Johnson") != std::string::npos);
}

TEST(EmployeeTest_Inheritance) {
    ContactInfo contact("test@test.com", "+375291112233");
    TestEmployee employee(1, "Inheritance", "Test", contact, 5001, "Tester", 40000.0);
    
    // Проверяем методы из Person
    CHECK_EQUAL("Inheritance Test", employee.getFullName());
    CHECK_EQUAL("test@test.com", employee.getContactInfo().getEmail());
    
    // Проверяем методы из Employee
    CHECK_EQUAL(5001, employee.getEmployeeId());
    CHECK_EQUAL("Tester", employee.getPosition());
    CHECK_EQUAL(40000.0, employee.getSalary());
}