#include <UnitTest++/UnitTest++.h>
#include "../HumanResources.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

TEST(HRTest_Constructor) {
    ContactInfo contact("hr@test.com", "+375291111111");
    vector<string> specializations = {"Recruitment", "Training"};
    
    HumanResources hr(1, "Alice", "Smith", contact, 7001, 
                      "HR Manager", 80000.0,
                      specializations, 15, 5000.0);
    
    CHECK_EQUAL("Alice Smith", hr.getFullName());
    CHECK_EQUAL(15, hr.getRecruitedEmployees());
    CHECK_EQUAL(5000.0, hr.getRecruitmentBonus());
}

TEST(HRTest_InvalidConstructor) {
    ContactInfo contact("hr@test.com", "+375291111111");
    vector<string> emptySpecializations;
    vector<string> validSpecializations = {"Recruitment"};
    
    // Пустые специализации
    CHECK_THROW(
        HumanResources(1, "Alice", "Smith", contact, 7001,
                       "HR", 50000.0, emptySpecializations, 10, 3000.0),
        invalid_argument
    );
    
    // Отрицательные нанятые сотрудники
    CHECK_THROW(
        HumanResources(1, "Alice", "Smith", contact, 7001,
                       "HR", 50000.0, validSpecializations, -5, 3000.0),
        invalid_argument
    );
}

TEST(HRTest_AddHrSpecialization) {
    ContactInfo contact("hr@test.com", "+375291111111");
    vector<string> specializations = {"Recruitment"};
    
    HumanResources hr(1, "Alice", "Smith", contact, 7001,
                      "HR", 50000.0, specializations, 10, 3000.0);
    
    // Добавляем новую специализацию
    hr.addHrSpecialization("Training");
    auto specials = hr.getHrSpecializations();
    
    CHECK_EQUAL(2u, specials.size());
    CHECK(find(specials.begin(), specials.end(), "Training") != specials.end());
    
    // Пытаемся добавить дубликат
    hr.addHrSpecialization("Recruitment");
    CHECK_EQUAL(2u, hr.getHrSpecializations().size());
    
    // Тест на пустую строку
    CHECK_THROW(hr.addHrSpecialization(""), invalid_argument);
}

TEST(HRTest_CalculateTotalBonus) {
    ContactInfo contact("hr@test.com", "+375291111111");
    vector<string> specializations = {"Recruitment"};
    
    HumanResources hr(1, "Alice", "Smith", contact, 7001,
                      "HR", 50000.0, specializations, 12, 4000.0);
    
    // Бонус = 12 * 4000 = 48000
    CHECK_EQUAL(48000.0, hr.calculateTotalBonus());
}

TEST(HRTest_DisplayInfo) {
    ContactInfo contact("hr@test.com", "+375291111111");
    vector<string> specializations = {"Recruitment", "Training"};
    
    HumanResources hr(1, "Alice", "Smith", contact, 7001,
                      "HR Manager", 80000.0, specializations, 15, 5000.0);
    
    StdoutRedirect redirect;
    hr.displayInfo();
    string output = redirect.getOutput();
        
        // Проверяем наличие ключевой информации
        CHECK(output.find("hr@test.com") != string::npos);
        CHECK(output.find("+375291111111") != string::npos);
        CHECK(output.find("Recruitment") != string::npos);
        CHECK(output.find("Training") != string::npos); // 90000 + 15000
        CHECK(output.find("Alice Smith") != string::npos);
        CHECK(output.find("HR Manage") != string::npos);
        CHECK(output.find("80000.0") != string::npos);
}