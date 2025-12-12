#include <UnitTest++/UnitTest++.h>
#include "../TransportCompany.hpp"
#include "../Validator.hpp"
#include "../CustomExceptions.hpp"
#include "HELPERFILE.cpp"
#include <string>
#include <memory>

using namespace std;

TEST(TransportCompany_Constructor_Valid) {
    // Используем валидные данные согласно Validator
    TransportCompany company(1, "FastTrans Inc.", 
                            "+375291234567", "contact@fasttrans.com",
                            "123 Main St, Minsk", 8.5);
    
    CHECK_EQUAL(1, company.getCompanyId());
    CHECK_EQUAL("FastTrans Inc.", company.getName());
    CHECK_EQUAL("+375291234567", company.getContactPhone());
    CHECK_EQUAL("contact@fasttrans.com", company.getEmail());
    CHECK_EQUAL("123 Main St, Minsk", company.getAddress());
    CHECK_CLOSE(8.5, company.getReliabilityRating(), 0.001);
}

TEST(TransportCompany_Constructor_InvalidId) {
    // Неверный ID (должен быть > 0)
    CHECK_THROW(
        TransportCompany(0, "Test Company", "+1234567890", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    CHECK_THROW(
        TransportCompany(-1, "Test Company", "+1234567890", "test@test.com", "Address", 5.0),
        DataValidationException
    );
}

TEST(TransportCompany_Constructor_InvalidName) {
    // Пустое имя
    CHECK_THROW(
        TransportCompany(1, "", "+1234567890", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Имя из одного символа
    CHECK_THROW(
        TransportCompany(1, "A", "+1234567890", "test@test.com", "Address", 5.0),
        DataValidationException
    );
}

TEST(TransportCompany_Constructor_InvalidPhone) {
    // Пустой телефон
    CHECK_THROW(
        TransportCompany(1, "Test Company", "", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Телефон без +
    CHECK_THROW(
        TransportCompany(1, "Test Company", "1234567890", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Телефон начинается с + но слишком короткий (< 10 символов)
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+123", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Телефон с + но содержит нецифровые символы
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+123abc456", "test@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Валидные телефоны согласно Validator
    TransportCompany valid1(2, "Valid1", "+1234567890", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("+1234567890", valid1.getContactPhone());
    
    TransportCompany valid2(3, "Valid2", "+375291112233", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("+375291112233", valid2.getContactPhone());
}

TEST(TransportCompany_Constructor_InvalidEmail) {
    // Пустой email
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "", "Address", 5.0),
        DataValidationException
    );
    
    // Email без @
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "invalid-email", "Address", 5.0),
        DataValidationException
    );
    
    // Email с @ но без точки после
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@email", "Address", 5.0),
        DataValidationException
    );
    
    // Email с @ и точкой, но точка сразу после @
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@.com", "Address", 5.0),
        DataValidationException
    );
    
    // Email с @ в начале
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "@test.com", "Address", 5.0),
        DataValidationException
    );
    
    // Email с точкой в конце
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@com.", "Address", 5.0),
        DataValidationException
    );
    
    // Валидные emails согласно Validator
    TransportCompany valid1(2, "Valid1", "+1234567890", "test@gmail.com", "Addr", 5.0);
    CHECK_EQUAL("test@gmail.com", valid1.getEmail());
    
    TransportCompany valid2(3, "Valid2", "+1234567890", "user.name@domain.co.uk", "Addr", 5.0);
    CHECK_EQUAL("user.name@domain.co.uk", valid2.getEmail());
}

TEST(TransportCompany_Constructor_InvalidAddress) {
    // Пустой адрес
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@test.com", "", 5.0),
        DataValidationException
    );
}

TEST(TransportCompany_Constructor_InvalidRating) {
    // Рейтинг меньше 0
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@test.com", "Address", -0.5),
        DataValidationException
    );
    
    // Рейтинг больше 10
    CHECK_THROW(
        TransportCompany(1, "Test Company", "+1234567890", "test@test.com", "Address", 10.5),
        DataValidationException
    );
    
    // Граничные случаи - 0.0 и 10.0 должны быть допустимы
    TransportCompany minRating(2, "Test Company", "+1234567890", "test@test.com", "Address", 0.0);
    CHECK_CLOSE(0.0, minRating.getReliabilityRating(), 0.001);
    
    TransportCompany maxRating(3, "Test Company", "+1234567890", "test@test.com", "Address", 10.0);
    CHECK_CLOSE(10.0, maxRating.getReliabilityRating(), 0.001);
    
    TransportCompany midRating(4, "Test Company", "+1234567890", "test@test.com", "Address", 5.5);
    CHECK_CLOSE(5.5, midRating.getReliabilityRating(), 0.001);
}

TEST(TransportCompany_Setters_Valid) {
    TransportCompany company(1, "Initial Company", "+11111111111", "initial@test.com", 
                           "Initial Address", 5.0);
    
    // Изменяем все поля
    company.setCompanyId(2);
    CHECK_EQUAL(2, company.getCompanyId());
    
    company.setName("Updated Company Name");
    CHECK_EQUAL("Updated Company Name", company.getName());
    
    company.setContactPhone("+22222222222");
    CHECK_EQUAL("+22222222222", company.getContactPhone());
    
    company.setEmail("updated@test.com");
    CHECK_EQUAL("updated@test.com", company.getEmail());
    
    company.setAddress("Updated Address Street");
    CHECK_EQUAL("Updated Address Street", company.getAddress());
    
    company.setReliabilityRating(7.5);
    CHECK_CLOSE(7.5, company.getReliabilityRating(), 0.001);
}

TEST(TransportCompany_Setters_Invalid) {
    TransportCompany company(1, "Test Company", "+1234567890", "test@test.com", "Address", 5.0);
    
    // Неверный ID
    CHECK_THROW(company.setCompanyId(0), DataValidationException);
    CHECK_THROW(company.setCompanyId(-1), DataValidationException);
    
    // Пустое имя
    CHECK_THROW(company.setName(""), DataValidationException);
    
    // Слишком короткое имя
    CHECK_THROW(company.setName("A"), DataValidationException);
    
    // Неверный телефон
    CHECK_THROW(company.setContactPhone(""), DataValidationException);
    CHECK_THROW(company.setContactPhone("1234567890"), DataValidationException); // без +
    CHECK_THROW(company.setContactPhone("+123"), DataValidationException); // слишком короткий
    CHECK_THROW(company.setContactPhone("+123abc456"), DataValidationException); // не цифры
    
    // Неверный email
    CHECK_THROW(company.setEmail(""), DataValidationException);
    CHECK_THROW(company.setEmail("invalid"), DataValidationException);
    CHECK_THROW(company.setEmail("test@"), DataValidationException);
    CHECK_THROW(company.setEmail("@test.com"), DataValidationException);
    
    // Пустой адрес
    CHECK_THROW(company.setAddress(""), DataValidationException);
    
    // Неверный рейтинг
    CHECK_THROW(company.setReliabilityRating(-0.1), DataValidationException);
    CHECK_THROW(company.setReliabilityRating(10.1), DataValidationException);
}

TEST(TransportCompany_Setters_ValidPhoneFormats) {
    TransportCompany company(1, "Test Company", "+1234567890", "test@test.com", "Address", 5.0);
    
    // Разные валидные форматы телефонов
    company.setContactPhone("+375291112233");  // Беларусь
    CHECK_EQUAL("+375291112233", company.getContactPhone());
    
    company.setContactPhone("+74951234567");   // Россия
    CHECK_EQUAL("+74951234567", company.getContactPhone());
    
    company.setContactPhone("+4402071234567"); // Великобритания
    CHECK_EQUAL("+4402071234567", company.getContactPhone());
    
    company.setContactPhone("+12125551212");   // США
    CHECK_EQUAL("+12125551212", company.getContactPhone());
}

TEST(TransportCompany_Setters_ValidEmailFormats) {
    TransportCompany company(1, "Test Company", "+1234567890", "test@test.com", "Address", 5.0);
    
    // Разные валидные форматы email
    company.setEmail("simple@gmail.com");
    CHECK_EQUAL("simple@gmail.com", company.getEmail());
    
    company.setEmail("user.name@domain.com");
    CHECK_EQUAL("user.name@domain.com", company.getEmail());
    
    company.setEmail("user_name@sub.domain.co.uk");
    CHECK_EQUAL("user_name@sub.domain.co.uk", company.getEmail());
    
    company.setEmail("test+filter@example.org");
    CHECK_EQUAL("test+filter@example.org", company.getEmail());
}

TEST(TransportCompany_DisplayCompanyInfo) {
    TransportCompany company(100, "Express Delivery Ltd.", 
                            "+375291112233", "info@express.by",
                            "Pobediteley Ave 17, Minsk, Belarus", 9.2);
    
    StdoutRedirect redirect;
    company.displayCompanyInfo();
    string output = redirect.getOutput();
    
    // Проверяем ключевые элементы вывода
    CHECK(output.find("Transport Company: Express Delivery Ltd.") != string::npos);
    CHECK(output.find("ID: 100") != string::npos);
    CHECK(output.find("Contact: +375291112233") != string::npos);
    CHECK(output.find("Email: info@express.by") != string::npos);
    CHECK(output.find("Address: Pobediteley Ave 17, Minsk, Belarus") != string::npos);
    CHECK(output.find("Reliability Rating: 9.2/10") != string::npos);
}

TEST(TransportCompany_Getters) {
    TransportCompany company(42, "Global Transport Solutions", 
                            "+449876543210", "contact@globaltransport.uk",
                            "25 Baker Street, London, UK", 8.8);
    
    CHECK_EQUAL(42, company.getCompanyId());
    CHECK_EQUAL("Global Transport Solutions", company.getName());
    CHECK_EQUAL("+449876543210", company.getContactPhone());
    CHECK_EQUAL("contact@globaltransport.uk", company.getEmail());
    CHECK_EQUAL("25 Baker Street, London, UK", company.getAddress());
    CHECK_CLOSE(8.8, company.getReliabilityRating(), 0.001);
}

TEST(TransportCompany_BoundaryValues) {
    // Проверяем граничные значения рейтинга
    TransportCompany min(1, "Min Rating Co", "+11111111111", "min@test.com", "Address", 0.0);
    CHECK_CLOSE(0.0, min.getReliabilityRating(), 0.001);
    
    TransportCompany max(2, "Max Rating Co", "+22222222222", "max@test.com", "Address", 10.0);
    CHECK_CLOSE(10.0, max.getReliabilityRating(), 0.001);
    
    TransportCompany exactMid(3, "Mid Rating Co", "+33333333333", "mid@test.com", "Address", 5.0);
    CHECK_CLOSE(5.0, exactMid.getReliabilityRating(), 0.001);
    
    TransportCompany decimal(4, "Decimal Co", "+44444444444", "decimal@test.com", "Address", 3.14159);
    CHECK_CLOSE(3.14159, decimal.getReliabilityRating(), 0.001);
}


TEST(TransportCompany_MultipleInstances) {
    // Создаем несколько экземпляров с разными данными
    TransportCompany company1(1, "Company One", "+11111111111", "one@company.com", "Address 1", 6.5);
    TransportCompany company2(2, "Company Two", "+22222222222", "two@company.com", "Address 2", 7.8);
    TransportCompany company3(3, "Company Three", "+33333333333", "three@company.com", "Address 3", 9.1);
    
    CHECK_EQUAL("Company One", company1.getName());
    CHECK_EQUAL("Company Two", company2.getName());
    CHECK_EQUAL("Company Three", company3.getName());
    
    CHECK_EQUAL("+11111111111", company1.getContactPhone());
    CHECK_EQUAL("+22222222222", company2.getContactPhone());
    CHECK_EQUAL("+33333333333", company3.getContactPhone());
}

TEST(TransportCompany_NameValidation) {
    // Проверяем различные форматы имен
    // Валидные имена (согласно Validator::isValidName)
    TransportCompany valid1(1, "Company Name", "+1234567890", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("Company Name", valid1.getName());
    
    TransportCompany valid2(2, "Company-Name", "+1234567890", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("Company-Name", valid2.getName());
    
    TransportCompany valid3(3, "Company O'Name", "+1234567890", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("Company O'Name", valid3.getName());
    
    TransportCompany valid4(4, "Company Ltd.", "+1234567890", "test@test.com", "Addr", 5.0);
    CHECK_EQUAL("Company Ltd.", valid4.getName());

}