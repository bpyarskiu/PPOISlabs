#include <UnitTest++/UnitTest++.h>
#include "../Discount.hpp"
#include "../License.hpp"
#include "../Passport.hpp"
#include <iostream>

class StdoutRedirect {
private:
    std::streambuf* oldCoutBuffer;
    std::stringstream newBuffer;

public:
    StdoutRedirect() {
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(newBuffer.rdbuf());
    }
    
    ~StdoutRedirect() {
        std::cout.rdbuf(oldCoutBuffer);
    }
    
    std::string getOutput() const {
        return newBuffer.str();
    }
};

TEST(DiscountTest_Validation) {
    // Тест валидного Discount
    Discount validDiscount(15.0, "Test discount");
    CHECK(validDiscount.isValid());
    
    // Тест невалидного Discount
    Discount invalidDiscount(0.0, "Zero discount");
    CHECK(!invalidDiscount.isValid());
    
    // Тест расчета цены
    CHECK_CLOSE(850.0, validDiscount.calculateDiscountedPrice(1000.0), 0.01);
    
    // Тест исключения при невалидной цене
    CHECK_THROW(validDiscount.calculateDiscountedPrice(-100.0), std::invalid_argument);
}

TEST(LicenseTest_Validation) {
    // Тест валидного License
    License validLicense("DL123456", "D", "2025-12-31");
    CHECK(validLicense.isValid());
    
    // Тест невалидного License
    License invalidLicense("DL123457", "D", "EXPIRED");
    CHECK(!invalidLicense.isValid());
    
    // Тест проверки категории
    CHECK(validLicense.canDriveCategory("D"));
    CHECK(!validLicense.canDriveCategory("A"));
}

TEST(PassportTest_Validation) {
    // Тест валидного Passport
    Passport validPassport("AB123456", "Belarus", "2025-12-31");
    CHECK(validPassport.isValid());
    
    // Тест невалидного Passport
    Passport invalidPassport("AB123457", "Belarus", "EXPIRED");
    CHECK(!invalidPassport.isValid());
}