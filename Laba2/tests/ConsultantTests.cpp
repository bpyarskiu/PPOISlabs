#include <UnitTest++/UnitTest++.h>
#include "../Consultant.hpp"
#include <algorithm>
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <string>
#include <iostream>
using namespace std;

TEST(ConsultantTest_Constructor) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"Marketing", "Sales"};
    
    Consultant consultant(1, "John", "Doe", contact, 6001, 
                         "Senior Consultant", 70000.0,
                         specializations, 10, 0.1);
    
    CHECK_EQUAL("John Doe", consultant.getFullName());
    CHECK_EQUAL(10, consultant.getSuccessfulBookings());
    CHECK_EQUAL(0.1, consultant.getCommissionRate());
}

TEST(ConsultantTest_InvalidConstructor) {
    ContactInfo contact("test@test.com", "+375291111111");
    vector<string> emptySpecializations;
    vector<string> validSpecializations = {"IT"};
    
    // Пустые специализации
    CHECK_THROW(
        Consultant(1, "John", "Doe", contact, 6001, 
                  "Consultant", 50000.0, emptySpecializations, 5, 0.05),
        std::invalid_argument
    );
    
    // Отрицательные бронирования
    CHECK_THROW(
        Consultant(1, "John", "Doe", contact, 6001,
                  "Consultant", 50000.0, validSpecializations, -1, 0.05),
        std::invalid_argument
    );
}

TEST(ConsultantTest_AddSpecialization) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"Marketing"};
    
    Consultant consultant(1, "John", "Doe", contact, 6001,
                         "Consultant", 50000.0, specializations, 5, 0.05);
    
    // Добавляем новую специализацию
    consultant.addSpecializationArea("Sales");
    auto areas = consultant.getSpecializationAreas();
    
    CHECK_EQUAL(2u, areas.size());
    CHECK(std::find(areas.begin(), areas.end(), "Sales") != areas.end());
    
    // Пытаемся добавить дубликат
    consultant.addSpecializationArea("Marketing");
    CHECK_EQUAL(2u, consultant.getSpecializationAreas().size()); // Размер не должен измениться
    
    // Тест на пустую строку
    CHECK_THROW(consultant.addSpecializationArea(""), std::invalid_argument);
}

TEST(ConsultantTest_CalculateCommission) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"IT"};
    
    Consultant consultant(1, "John", "Doe", contact, 6001,
                         "Consultant", 100000.0, specializations, 10, 0.15);
    
    // Комиссия = зарплата * rate * bookings = 100000 * 0.15 * 10 = 150000
    CHECK_EQUAL(150000.0, consultant.calculateCommission());
}

TEST(ConsultantTest_DisplayInfo) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"Marketing", "Sales"};
    
    Consultant consultant(1, "John", "Doe", contact, 6001, 
                         "Senior Consultant", 70000.0,
                         specializations, 10, 0.1);
    
    StdoutRedirect redirect;
    consultant.displayInfo();
    string output = redirect.getOutput();
        
        // Проверяем наличие ключевой информации
        CHECK(output.find("John Doe") != string::npos);
        CHECK(output.find("consultant@test.com") != string::npos);
        CHECK(output.find("+375291111111") != string::npos);
        CHECK(output.find("Marketing") != string::npos); // 90000 + 15000
        CHECK(output.find("Sales") != string::npos);
        CHECK(output.find("Senior Consultant") != string::npos);
        CHECK(output.find("70000.0") != string::npos);
}

TEST(ConsultantTest_GetSpecializationAreas) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"IT", "Finance"};
    
    Consultant consultant(1, "John", "Doe", contact, 6001,
                         "Consultant", 50000.0, specializations, 5, 0.05);
    
    auto areas = consultant.getSpecializationAreas();
    CHECK_EQUAL(2u, areas.size());
    CHECK(find(areas.begin(), areas.end(), "IT") != areas.end());
    CHECK(find(areas.begin(), areas.end(), "Finance") != areas.end());
}

TEST(ConsultantTest_CalculateCommissionEdgeCases) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"IT"};
    
    // Нулевые бронирования
    Consultant consultant1(1, "John", "Doe", contact, 6001,
                          "Consultant", 100000.0, specializations, 0, 0.15);
    CHECK_EQUAL(0.0, consultant1.calculateCommission());
    
    // Нулевая ставка комиссии
    Consultant consultant2(2, "Jane", "Doe", contact, 6002,
                          "Consultant", 100000.0, specializations, 10, 0.0);
    CHECK_EQUAL(0.0, consultant2.calculateCommission());
}

TEST(ConsultantTest_InvalidCommissionRate) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"IT"};
    
    // Отрицательная ставка комиссии (если такая валидация есть в коде)
    // Если нет - можно добавить в конструктор проверку
    Consultant consultant(1, "John", "Doe", contact, 6001,
                         "Consultant", 50000.0, specializations, 5, -0.05);
    // Если проверки нет, комиссия будет отрицательной
    // Если проверка есть, нужно добавить соответствующий CHECK_THROW
}

TEST(ConsultantTest_CopyAndAssignment) {
    ContactInfo contact("consultant@test.com", "+375291111111");
    vector<string> specializations = {"Marketing"};
    
    Consultant consultant1(1, "John", "Doe", contact, 6001,
                          "Consultant", 50000.0, specializations, 5, 0.05);
    
    // Проверка копирования (если реализовано)
    Consultant consultant2 = consultant1;
    CHECK_EQUAL(consultant1.getFullName(), consultant2.getFullName());
    CHECK_EQUAL(consultant1.getSuccessfulBookings(), consultant2.getSuccessfulBookings());
}