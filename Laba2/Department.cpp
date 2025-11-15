#include "Department.hpp"
#include <algorithm>

using namespace std;

Department::Department(int departmentId, const string& name, double budget) {
    setDepartmentId(departmentId);
    setName(name);
    setBudget(budget);
}

int Department::getDepartmentId() const { return departmentId; }

string Department::getName() const { return name; }

double Department::getBudget() const { return budget; }

const vector<shared_ptr<Employee>>& Department::getEmployees() const { return employees; }

void Department::setDepartmentId(int departmentId) {
    Validator::validateId(departmentId);
    this->departmentId = departmentId;
}

void Department::setName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Department name cannot be empty");
    }
    this->name = name;
}

void Department::setBudget(double budget) {
    Validator::validatePrice(budget);
    this->budget = budget;
}

void Department::addEmployee(const shared_ptr<Employee>& employee) {
    if (!employee) {
        throw invalid_argument("Cannot add null employee");
    }
    
    // Проверяем, нет ли уже сотрудника с таким ID
    auto existing = findEmployeeById(employee->getEmployeeId());
    if (existing) {
        throw invalid_argument("Employee with ID " + to_string(employee->getEmployeeId()) + " already exists in department");
    }
    
    employees.push_back(employee);
}

void Department::removeEmployee(int employeeId) {
    employees.erase(
        remove_if(employees.begin(), employees.end(),
            [employeeId](const shared_ptr<Employee>& emp) {
                return emp->getEmployeeId() == employeeId;
            }),
        employees.end()
    );
}

shared_ptr<Employee> Department::findEmployeeById(int employeeId) const {
    auto it = find_if(employees.begin(), employees.end(),
        [employeeId](const shared_ptr<Employee>& emp) {
            return emp->getEmployeeId() == employeeId;
        });
    return (it != employees.end()) ? *it : nullptr;
}

double Department::calculateTotalSalary() const {
    double total = 0.0;
    for (const auto& employee : employees) {
        if (employee) {
            total += employee->getSalary();
        }
    }
    return total;
}

bool Department::isBudgetExceeded() const {
    return calculateTotalSalary() > budget;
}