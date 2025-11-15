#include <UnitTest++/UnitTest++.h>
#icnlude "../CurrencyConverter.hpp"
TEST(CurrencyPairTest, BasicOperations) {
    CurrencyPair pair(Currency::USD, Currency::EUR);
    EXPECT_EQ(pair.getFrom(), Currency::USD);
    EXPECT_EQ(pair.getTo(), Currency::EUR);
    
    CurrencyPair reverse = pair.getReversePair();
    EXPECT_EQ(reverse.getFrom(), Currency::EUR);
    EXPECT_EQ(reverse.getTo(), Currency::USD);
}

TEST(CurrencyConverterTest, Conversion) {
    CurrencyConverter converter;
    converter.setExchangeRate(Currency::USD, Currency::EUR, 0.85);
    
    double result = converter.convert(100, Currency::USD, Currency::EUR);
    EXPECT_DOUBLE_EQ(result, 85.0);

    EXPECT_THROW(converter.convert(-100, Currency::USD, Currency::EUR), CurrencyConversionException);
}