#include <UnitTest++/UnitTest++.h>
#include "../Price.hpp"
#include "../Address.hpp"
#include "../ContactInfo.hpp"

SUITE(PriceTests) {
    TEST(DefaultConstructor) {
        Price price;
        CHECK_EQUAL(0.0, price.getAmount());
        CHECK_EQUAL("RUB", price.getCurrency());
    }
    
    TEST(ParameterizedConstructor) {
        Price price(100.5, "USD");
        CHECK_EQUAL(100.5, price.getAmount());
        CHECK_EQUAL("USD", price.getCurrency());
    }
    
    TEST(InvalidAmountThrowsException) {
        CHECK_THROW(Price(-10.0), std::invalid_argument);
    }
    
    TEST(AddPricesSameCurrency) {
        Price price1(100.0, "RUB");
        Price price2(50.0, "RUB");
        Price result = price1.add(price2);
        
        CHECK_EQUAL(150.0, result.getAmount());
        CHECK_EQUAL("RUB", result.getCurrency());
    }
    
    TEST(AddPricesDifferentCurrencyThrowsException) {
        Price price1(100.0, "RUB");
        Price price2(50.0, "USD");
        
        CHECK_THROW(price1.add(price2), std::invalid_argument);
    }
    
    TEST(MultiplyPrice) {
        Price price(100.0, "RUB");
        Price result = price.multiply(2.5);
        
        CHECK_EQUAL(250.0, result.getAmount());
        CHECK_EQUAL("RUB", result.getCurrency());
    }
    
    TEST(MultiplyWithNegativeFactorThrowsException) {
        Price price(100.0, "RUB");
        
        CHECK_THROW(price.multiply(-1.0), std::invalid_argument);
    }
}

SUITE(AddressTests) {
    TEST(ValidAddressCreation) {
        Address address("Main St", "Moscow", "Russia", "101000");
        
        CHECK_EQUAL("Main St", address.getStreet());
        CHECK_EQUAL("Moscow", address.getCity());
        CHECK_EQUAL("Russia", address.getCountry());
        CHECK_EQUAL("101000", address.getPostalCode());
    }
    
    TEST(EmptyStreetThrowsException) {
        CHECK_THROW(Address("", "Moscow", "Russia", "101000"), std::invalid_argument);
    }
    
    TEST(EmptyCityThrowsException) {
        CHECK_THROW(Address("Main St", "", "Russia", "101000"), std::invalid_argument);
    }
    
    TEST(EmptyCountryThrowsException) {
        CHECK_THROW(Address("Main St", "Moscow", "", "101000"), std::invalid_argument);
    }
    
    TEST(GetFullAddress) {
        Address address("Main St", "Moscow", "Russia", "101000");
        std::string expected = "Main St, Moscow, Russia 101000";
        
        CHECK_EQUAL(expected, address.getFullAddress());
    }
}

SUITE(ContactInfoTests) {
    TEST(ValidContactInfoCreation) {
        ContactInfo contact("test@email.com", "+79161234567");
        
        CHECK_EQUAL("test@email.com", contact.getEmail());
        CHECK_EQUAL("+79161234567", contact.getPhone());
    }
    
    TEST(InvalidEmailThrowsException) {
        CHECK_THROW(ContactInfo("", "+79161234567"), std::invalid_argument);
    }
    
    TEST(InvalidPhoneThrowsException) {
        CHECK_THROW(ContactInfo("test@email.com", "123"), std::invalid_argument);
    }
    
    TEST(ValidEmailCheck) {
        ContactInfo contact("valid@email.com", "+79161234567");
        CHECK(contact.isValidEmail());
    }
    
    TEST(ValidPhoneCheck) {
        ContactInfo contact("test@email.com", "+79161234567");
        CHECK(contact.isValidPhone());
    }
}