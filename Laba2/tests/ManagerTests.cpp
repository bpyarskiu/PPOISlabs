#include "../Manager.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <string> 

using namespace std;

SUITE(ManagerTests) {

    TEST(Manager_Constructor) {
        ContactInfo contact("manager@example.com", "+375291112233");
        vector<string> responsibilities = {"Team Management", "Budget Planning"};
        
        Manager manager(1, "John", "Manager", contact, 4001, 
                       "Project Manager", 70000.0, responsibilities, 5, 10000.0);
        
        CHECK_EQUAL("John Manager", manager.getFullName());
        CHECK_EQUAL(5, manager.getTeamSize());
        CHECK_EQUAL(10000.0, manager.getPerformanceBonus());
        CHECK_EQUAL(2u, manager.getResponsibilities().size());
        CHECK_EQUAL("Project Manager", manager.getPosition());
    }

    TEST(Manager_InvalidConstructor_EmptyResponsibilities) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> emptyResponsibilities;
        
        CHECK_THROW(
            Manager(1, "Test", "Manager", contact, 4001, "Manager", 50000.0,
                   emptyResponsibilities, 3, 5000.0),
            invalid_argument
        );
    }

    TEST(Manager_AddResponsibility) {
        ContactInfo contact("manager@example.com", "+375291112233");
        vector<string> responsibilities = {"Team Management"};
        
        Manager manager(1, "Jane", "Manager", contact, 4002, 
                       "Manager", 60000.0, responsibilities, 4, 8000.0);
        
        // Добавляем новую ответственность
        manager.addResponsibility("Reporting");
        auto resps = manager.getResponsibilities();
        
        CHECK_EQUAL(2u, resps.size());
        CHECK(find(resps.begin(), resps.end(), "Reporting") != resps.end());
        
        // Пытаемся добавить дубликат
        manager.addResponsibility("Team Management");
        CHECK_EQUAL(2u, manager.getResponsibilities().size());
        
        // Пытаемся добавить пустую ответственность
        CHECK_THROW(manager.addResponsibility(""), invalid_argument);
    }

    TEST(Manager_CalculateTotalCompensation) {
        ContactInfo contact("manager@example.com", "+375291112233");
        vector<string> responsibilities = {"Management"};
        
        // Тест 1: с бонусом
        Manager manager1(1, "John", "Doe", contact, 4003, 
                        "Manager", 80000.0, responsibilities, 10, 20000.0);
        
        CHECK_EQUAL(100000.0, manager1.calculateTotalCompensation()); // 80000 + 20000
        
        // Тест 2: без бонуса (0 бонус)
        Manager manager2(2, "Jane", "Smith", contact, 4004, 
                        "Manager", 60000.0, responsibilities, 5, 0.0);
        
        CHECK_EQUAL(60000.0, manager2.calculateTotalCompensation());
        
        // Тест 3: отрицательный бонус (если разрешено)
        Manager manager3(3, "Bob", "Brown", contact, 4005, 
                        "Manager", 50000.0, responsibilities, 3, -5000.0);
        
        CHECK_EQUAL(45000.0, manager3.calculateTotalCompensation()); // 50000 - 5000
    }

    TEST(Manager_DisplayInfo) {
        ContactInfo contact("manager@example.com", "+375291112233");
        vector<string> responsibilities = {"Team Leadership", "Budget Control", "Strategy"};
        
        Manager manager(1, "Robert", "Johnson", contact, 4006, 
                       "Senior Manager", 90000.0, responsibilities, 8, 15000.0);
        
        StdoutRedirect redirect;
        manager.displayInfo();
        string output = redirect.getOutput();
        
        // Проверяем наличие ключевой информации
        CHECK(output.find("Robert Johnson") != string::npos);
        CHECK(output.find("Team Size: 8 employees") != string::npos);
        CHECK(output.find("Performance Bonus: 15000.0 RUB") != string::npos);
        CHECK(output.find("Total Compensation: 105000.0 RUB") != string::npos); // 90000 + 15000
        CHECK(output.find("Team Leadership") != string::npos);
        CHECK(output.find("Budget Control") != string::npos);
        CHECK(output.find("Strategy") != string::npos);
    }

    TEST(Manager_GetMethods) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> responsibilities = {"Hiring", "Training", "Evaluation"};
        
        Manager manager(1, "Sarah", "Wilson", contact, 4007, 
                       "HR Manager", 65000.0, responsibilities, 12, 12000.0);
        
        // Проверяем все геттеры
        CHECK_EQUAL(12, manager.getTeamSize());
        CHECK_EQUAL(12000.0, manager.getPerformanceBonus());
        
        auto resps = manager.getResponsibilities();
        CHECK_EQUAL(3u, resps.size());
        CHECK(find(resps.begin(), resps.end(), "Training") != resps.end());
    }

    TEST(Manager_EdgeCases) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> responsibilities = {"Minimal"};
        
        // Менеджер с минимальной командой
        Manager smallTeam(1, "Small", "Team", contact, 4008, 
                         "Manager", 40000.0, responsibilities, 1, 1000.0);
        
        CHECK_EQUAL(1, smallTeam.getTeamSize());
        CHECK_EQUAL(41000.0, smallTeam.calculateTotalCompensation());
        
        // Менеджер без команды (0 человек)
        Manager noTeam(2, "No", "Team", contact, 4009, 
                      "Manager", 35000.0, responsibilities, 0, 0.0);
        
        CHECK_EQUAL(0, noTeam.getTeamSize());
        CHECK_EQUAL(35000.0, noTeam.calculateTotalCompensation());
        
        // Менеджер с большим бонусом
        Manager bigBonus(3, "Big", "Bonus", contact, 4010, 
                        "Director", 120000.0, responsibilities, 20, 50000.0);
        
        CHECK_EQUAL(170000.0, bigBonus.calculateTotalCompensation());
    }

    TEST(Manager_Inheritance) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> responsibilities = {"Management"};
        
        Manager manager(1, "Inheritance", "Test", contact, 4011, 
                       "Test Manager", 55000.0, responsibilities, 6, 5000.0);
        
        // Проверяем методы, унаследованные от Employee
        CHECK_EQUAL(4011, manager.getEmployeeId());
        CHECK_EQUAL("Test Manager", manager.getPosition());
        CHECK_EQUAL(55000.0, manager.getSalary());
        
        // Проверяем методы, унаследованные от Person
        CHECK_EQUAL("Inheritance Test", manager.getFullName());
        CHECK_EQUAL("test@example.com", manager.getContactInfo().getEmail());
    }
}