#include <UnitTest++/UnitTest++.h>
#include "../Client.hpp"
#include "../Discount.hpp"
#include "../Passport.hpp"
#include "../ContactInfo.hpp"
#include <iostream>
#include "HELPERFILE.cpp"

// Добавьте в ClientTests.cpp
TEST(ClientTest_Constructor) {
    ContactInfo contact("test@test.com", "+375291234567");
    
    // Тест с полными данными
    auto discount = std::make_shared<Discount>(10.0, "Test");
    auto passport = std::make_shared<Passport>("AB123456", "BY", "2025-12-31");
    Client client(1, "John", "Doe", contact, 1001, "Preferences", discount, passport);
    
    CHECK_EQUAL(1001, client.getClientId());
    CHECK_EQUAL("Preferences", client.getPreferences());
    CHECK(client.getDiscount() != nullptr);
    
    // Тест с минимальными данными
    Client minimalClient(2, "Jane", "Smith", contact, 1002);
    CHECK_EQUAL(1002, minimalClient.getClientId());
    CHECK(minimalClient.getPreferences().empty());
    CHECK(minimalClient.getDiscount() == nullptr);
}

TEST(ClientTest_DisplayClientInfoEdgeCases) {
    ContactInfo contact("client@test.com", "+375291234567");
    
    // Тест без скидки и паспорта
    Client clientNoExtras(1, "John", "Doe", contact, 1001, "");
    
    StdoutRedirect redirect;
    clientNoExtras.displayClientInfo();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Client ID: 1001") != std::string::npos);
    CHECK(output.find("Preferences:") == std::string::npos); // Нет preferences
}

TEST(ClientTest_ApplyDiscountEdgeCases) {
    ContactInfo contact("client@test.com", "+375291234567");
    
    // Тест с нулевой скидкой
    auto zeroDiscount = std::make_shared<Discount>(0.0, "Zero discount");
    Client clientZero(1, "John", "Doe", contact, 1001, "", zeroDiscount);
    
    double price = 1000.0;
    CHECK_CLOSE(1000.0, clientZero.applyDiscountToPrice(price), 0.01);
    
    // Тест с 100% скидкой
    auto fullDiscount = std::make_shared<Discount>(100.0, "Full discount");
    Client clientFull(2, "Jane", "Smith", contact, 1002, "", fullDiscount);
    
    CHECK_CLOSE(0.0, clientFull.applyDiscountToPrice(price), 0.01);
}

TEST(ClientTest_DiscountApplication) {
    ContactInfo contact("client@test.com", "+375291234567");
    auto discount = std::make_shared<Discount>(10.0, "Welcome discount");
    Client client(1, "John", "Doe", contact, 1001, "Beach vacations", discount);
    
    // Тест applyDiscountToPrice с действующей скидкой
    double originalPrice = 1000.0;
    double discountedPrice = client.applyDiscountToPrice(originalPrice);
    CHECK_CLOSE(900.0, discountedPrice, 0.01); // 10% скидка
    
    // Тест applyDiscountToPrice без скидки
    Client clientNoDiscount(2, "Jane", "Smith", contact, 1002, "");
    double samePrice = clientNoDiscount.applyDiscountToPrice(originalPrice);
    CHECK_CLOSE(1000.0, samePrice, 0.01);
}

TEST(ClientTest_PassportValidation) {
    ContactInfo contact("client@test.com", "+375291234567");
    auto passport = std::make_shared<Passport>("AB123456", "Belarus", "2025-12-31");
    Client client(1, "John", "Doe", contact, 1001, "", nullptr, passport);
    
    // Тест hasValidPassport с валидным паспортом
    CHECK(client.hasValidPassport());
    
    // Тест hasValidPassport с невалидным паспортом
    auto expiredPassport = std::make_shared<Passport>("AB123457", "Belarus", "EXPIRED");
    Client clientExpired(2, "Jane", "Smith", contact, 1002, "", nullptr, expiredPassport);
    CHECK(!clientExpired.hasValidPassport());
}

TEST(ClientTest_SetDiscount) {
    ContactInfo contact("client@test.com", "+375291234567");
    Client client(1, "John", "Doe", contact, 1001, "");
    
    // Изначально скидки нет
    CHECK(client.getDiscount() == nullptr);
    
    // Устанавливаем скидку
    auto discount = std::make_shared<Discount>(15.0, "Summer promotion");
    client.setDiscount(discount);
    
    // Проверяем что скидка установилась
    CHECK(client.getDiscount() != nullptr);
    CHECK_EQUAL("Summer promotion", client.getDiscount()->getDescription());
}

TEST(ClientTest_SetPassport) {
    ContactInfo contact("client@test.com", "+375291234567");
    Client client(1, "John", "Doe", contact, 1001, "");
    
    // Изначально паспорта нет
    CHECK(!client.hasValidPassport());
    
    // Устанавливаем паспорт
    auto passport = std::make_shared<Passport>("CD789012", "Belarus", "2026-06-30");
    client.setPassport(passport);
    
    // Проверяем что паспорт установился
    CHECK(client.hasValidPassport());
}

TEST(ClientTest_DisplayClientInfo) {
    ContactInfo contact("client@test.com", "+375291234567");
    auto discount = std::make_shared<Discount>(10.0, "Test discount");
    auto passport = std::make_shared<Passport>("EF345678", "Belarus", "2025-12-31");
    Client client(1, "John", "Doe", contact, 1001, "Luxury hotels", discount, passport);
    
    StdoutRedirect redirect;
    client.displayClientInfo();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Client ID: 1001") != std::string::npos);
    CHECK(output.find("Preferences: Luxury hotels") != std::string::npos);
    CHECK(output.find("Discount:") != std::string::npos);
    CHECK(output.find("Passport: Valid") != std::string::npos);
}