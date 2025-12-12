#include <UnitTest++/UnitTest++.h>
#include "../Person.hpp"
#include "../Employee.hpp"
#include "../Client.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <iostream>
#include <sstream>


SUITE(PersonTests) {
    TEST(ValidPersonCreation) {
        ContactInfo contact("john@email.com", "+79161234567");
        Person person(1, "John", "Doe", contact);
        
        CHECK_EQUAL(1, person.getId());
        CHECK_EQUAL("John", person.getFirstName());
        CHECK_EQUAL("Doe", person.getLastName());
        CHECK_EQUAL("John Doe", person.getFullName());
    }
    
    TEST(InvalidPersonIdThrowsException) {
        ContactInfo contact("john@email.com", "+79161234567");
        CHECK_THROW(Person(0, "John", "Doe", contact), std::invalid_argument);
    }
    
    TEST(EmptyFirstNameThrowsException) {
        ContactInfo contact("john@email.com", "+79161234567");
        CHECK_THROW(Person(1, "", "Doe", contact), std::invalid_argument);
    }
    
    TEST(EmptyLastNameThrowsException) {
        ContactInfo contact("john@email.com", "+79161234567");
        CHECK_THROW(Person(1, "John", "", contact), std::invalid_argument);
    }
}



SUITE(ClientTests) {
    TEST(ValidClientCreation) {
        ContactInfo contact("client@email.com", "+79161234567");
        Client client(1, "Bob", "Johnson", contact, 2001, "Beach tours");
        
        CHECK_EQUAL(2001, client.getClientId());
        CHECK_EQUAL("Beach tours", client.getPreferences());
    }
    
    TEST(ClientWithoutPreferences) {
        ContactInfo contact("client@email.com", "+79161234567");
        Client client(1, "Bob", "Johnson", contact, 2001);
        
        CHECK_EQUAL(2001, client.getClientId());
        CHECK_EQUAL("", client.getPreferences());
    }
    
    TEST(ClientWithDiscount) {
        ContactInfo contact("client@email.com", "+79161234567");
        auto discount = std::make_shared<Discount>(10.0, "Test discount");
        Client client(1, "Bob", "Johnson", contact, 2001, "", discount);
        
        CHECK(client.getDiscount() != nullptr);
        CHECK_EQUAL(10.0, client.getDiscount()->getPercentage());
    }
    
    TEST(ApplyDiscountToPrice) {
        ContactInfo contact("client@email.com", "+79161234567");
        auto discount = std::make_shared<Discount>(20.0);
        Client client(1, "Bob", "Johnson", contact, 2001, "", discount);
        
        double originalPrice = 1000.0;
        double discountedPrice = client.applyDiscountToPrice(originalPrice);
        
        CHECK_EQUAL(800.0, discountedPrice);
    }
    
    TEST(ApplyDiscountWithoutDiscount) {
        ContactInfo contact("client@email.com", "+79161234567");
        Client client(1, "Bob", "Johnson", contact, 2001);
        
        double originalPrice = 1000.0;
        double discountedPrice = client.applyDiscountToPrice(originalPrice);
        
        CHECK_EQUAL(1000.0, discountedPrice);
    }
    TEST(PersonTest_Display) {
    ContactInfo contact("test@email.com", "+375291234567");
    Person person(1, "John", "Doe", contact);
    
    // Перехватываем вывод
    StdoutRedirect redirect;
    person.display();
    std::string output = redirect.getOutput();
    
    // Проверяем что все ключевые элементы есть в выводе
    CHECK(output.find("ID: 1") != std::string::npos);
    CHECK(output.find("Name: John Doe") != std::string::npos);
    CHECK(output.find("test@email.com") != std::string::npos);
    CHECK(output.find("+375291234567") != std::string::npos);
}
}