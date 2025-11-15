#pragma once
#include "Employee.hpp"
#include <vector>
#include <memory>
#include "Validator.hpp"

class Department {
private:
    int departmentId;
    std::string name;
    double budget;
    std::vector<std::shared_ptr<Employee>> employees;

public:
    Department(int departmentId, const std::string& name, double budget);

    // Геттеры
    int getDepartmentId() const;
    std::string getName() const;
    double getBudget() const;
    const std::vector<std::shared_ptr<Employee>>& getEmployees() const;

    // Сеттеры
    void setDepartmentId(int departmentId);
    void setName(const std::string& name);
    void setBudget(double budget);

    // Методы для управления сотрудниками
    void addEmployee(const std::shared_ptr<Employee>& employee);
    void removeEmployee(int employeeId);
    std::shared_ptr<Employee> findEmployeeById(int employeeId) const;

    // Бизнес-методы
    double calculateTotalSalary() const;
    bool isBudgetExceeded() const;
};
