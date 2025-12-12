#pragma once
#include <string>

enum class Currency {
    RUB,
    USD,
    EUR,
    GBP,
    JPY,
    CNY
};
inline std::ostream& operator<<(std::ostream& os, Currency currency) {
    switch (currency) {
        case Currency::RUB: os << std::string("RUB"); break;
        case Currency::USD: os << std::string("USD"); break;
        case Currency::EUR: os << std::string("EUR"); break;
        case Currency::GBP: os << std::string("GBP"); break;
        case Currency::JPY: os << std::string("JPY"); break;
        case Currency::CNY: os << std::string("CNY"); break;
        default: os << std::string("UNKNOWN"); break;
    }
    return os;
}