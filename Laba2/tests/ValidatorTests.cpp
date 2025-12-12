#include <UnitTest++/UnitTest++.h>
#include "../Validator.hpp"

TEST(ValidatorTest_EmailValidation) {
    CHECK(Validator::isValidEmail("test@example.com"));
    CHECK(Validator::isValidEmail("user.name@domain.co.uk"));
    CHECK(!Validator::isValidEmail("invalid-email"));
    CHECK(!Validator::isValidEmail("no@dot"));
    CHECK(!Validator::isValidEmail("@nodomain.com"));
    CHECK(!Validator::isValidEmail(""));
}

TEST(ValidatorTest_PhoneValidation) {
    CHECK(Validator::isValidPhone("+79161234567"));
    CHECK(Validator::isValidPhone("+375291234567"));
    CHECK(!Validator::isValidPhone("123"));
    CHECK(!Validator::isValidPhone("79161234567")); // нет +
    CHECK(!Validator::isValidPhone("+7916abc4567")); // буквы
    CHECK(!Validator::isValidPhone(""));
}