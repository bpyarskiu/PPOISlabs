#include <UntiTest++/UnitTest++.h>
#include "../BusRide.hpp"
#include "../Flight.hpp"
TEST(PaymentSystemTest, ProcessPayment) {
    PaymentSystem paymentSystem;
    PaymentResult result = paymentSystem.processPayment(
        PaymentDetails(1000.0, Currency::RUB, "4111111111111111", "12/25")
    );
    
    EXPECT_TRUE(result.isSuccess());
    EXPECT_FALSE(result.getTransactionId().empty());
}