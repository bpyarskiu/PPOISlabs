#include <UnitTest++/UnitTest++.h>
#include "../CurrencyConverter.hpp"
#include "../CurrencyPair.hpp"
#include "../CustomExceptions.hpp"

TEST(CurrencyPairTest_BasicOperations) {
    CurrencyPair pair(Currency::USD, Currency::EUR);
    CHECK_EQUAL(pair.getFrom(), Currency::USD);
    CHECK_EQUAL(pair.getTo(), Currency::EUR);
    
    CurrencyPair reverse = pair.getReversePair();
    CHECK_EQUAL(reverse.getFrom(), Currency::EUR);
    CHECK_EQUAL(reverse.getTo(), Currency::USD);
}

TEST(CurrencyConverterTest_Conversion) {
    CurrencyConverter converter;
    converter.setExchangeRate(Currency::USD, Currency::EUR, 0.85);
    
    double result = converter.convert(100, Currency::USD, Currency::EUR);
    CHECK_EQUAL(result, 85.0);

    CHECK_THROW(converter.convert(-100, Currency::USD, Currency::EUR), CurrencyConversionException);
}