#include <UntiTest++/UnitTest++.h>
#include "../Validator.hpp"
TEST(ValidatorTest, EmailValidation) {
    EXPECT_TRUE(Validator::isValidEmail("test@example.com"));
    EXPECT_FALSE(Validator::isValidEmail("invalid-email"));
    EXPECT_FALSE(Validator::isValidEmail(""));
}

TEST(ValidatorTest, PhoneValidation) {
    EXPECT_TRUE(Validator::isValidPhone("+79161234567"));
    EXPECT_FALSE(Validator::isValidPhone("123"));
}