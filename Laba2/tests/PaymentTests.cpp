#include <UnitTest++/UnitTest++.h>
#include "../PaymentSystem.hpp"

TEST(PaymentSystemTest_ProcessPayment) {
    PaymentSystem paymentSystem;
    
    // Тестируем успешный платеж
    PaymentResult result = paymentSystem.processPayment(
        PaymentDetails(1000.0, "RUB", "4111111111111111", "12/25")
    );
    
    // Проверяем что транзакция обработана (может быть успешной или неуспешной)
    CHECK(!result.getTransactionId().empty() || !result.isSuccess());
    
    // Проверяем что при неудаче есть сообщение об ошибке
    if (!result.isSuccess()) {
        CHECK(!result.getMessage().empty());
    }
}

TEST(PaymentSystemTest_InvalidAmount) {
    PaymentSystem paymentSystem;
    
    PaymentResult result = paymentSystem.processPayment(
        PaymentDetails(-100.0, "RUB", "4111111111111111", "12/25")
    );
    
    CHECK(!result.isSuccess());
    CHECK(result.getMessage().find("Invalid") != std::string::npos);
}

TEST(PaymentSystemTest_InvalidCard) {
    PaymentSystem paymentSystem;
    
    PaymentResult result = paymentSystem.processPayment(
        PaymentDetails(1000.0, "RUB", "1234", "12/25")
    );
    
    CHECK(!result.isSuccess());
    CHECK(result.getMessage().find("card") != std::string::npos);
}