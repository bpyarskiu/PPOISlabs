#include "CurrencyConverter.hpp"
#include "CustomExceptions.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

CurrencyConverter::CurrencyConverter(Currency baseCurrency) : baseCurrency(baseCurrency) {
    initializeDefaultRates();
}

void CurrencyConverter::setExchangeRate(Currency from, Currency to, double rate) {
    setExchangeRate(CurrencyPair(from, to), rate);
}

void CurrencyConverter::setExchangeRate(const CurrencyPair& pair, double rate) {
    if (rate <= 0) {
        throw CurrencyConversionException("Exchange rate must be positive");
    }
    
    validateCurrency(pair.getFrom());
    validateCurrency(pair.getTo());
    
    exchangeRates[pair] = rate;
    
    // Автоматически устанавливаем обратный курс
    if (pair.getFrom() != pair.getTo()) {
        CurrencyPair reversePair = pair.getReversePair();
        exchangeRates[reversePair] = 1.0 / rate;
    }
}

double CurrencyConverter::getExchangeRate(Currency from, Currency to) const {
    return getExchangeRate(CurrencyPair(from, to));
}

double CurrencyConverter::getExchangeRate(const CurrencyPair& pair) const {
    if (pair.getFrom() == pair.getTo()) return 1.0;
    
    auto it = exchangeRates.find(pair);
    
    if (it == exchangeRates.end()) {
        // Пробуем найти через базовую валюту
        try {
            double toBase = getExchangeRate(CurrencyPair(pair.getFrom(), baseCurrency));
            double fromBase = getExchangeRate(CurrencyPair(baseCurrency, pair.getTo()));
            return toBase * fromBase;
        } catch (const CurrencyConversionException&) {
            throw CurrencyConversionException("Exchange rate not found for currency pair: " + 
                                            getCurrencyName(pair.getFrom()) + " to " + 
                                            getCurrencyName(pair.getTo()));
        }
    }
    
    return it->second;
}

double CurrencyConverter::convert(double amount, Currency from, Currency to) const {
    if (amount < 0) {
        throw CurrencyConversionException("Amount cannot be negative");
    }
    
    validateCurrency(from);
    validateCurrency(to);
    
    if (from == to) return amount;
    
    double rate = getExchangeRate(from, to);
    return amount * rate;
}

double CurrencyConverter::convertToBase(double amount, Currency from) const {
    return convert(amount, from, baseCurrency);
}

double CurrencyConverter::convertFromBase(double amount, Currency to) const {
    return convert(amount, baseCurrency, to);
}

void CurrencyConverter::updateRatesFromAPI() {
    // Имитация обновления курсов из API
    cout << "Updating exchange rates from API..." << endl;
    
    // "Обновляем" курсы случайными значениями в разумных пределах
    setExchangeRate(Currency::RUB, Currency::USD, 0.011 + (rand() % 10) / 1000.0);
    setExchangeRate(Currency::RUB, Currency::EUR, 0.010 + (rand() % 10) / 1000.0);
    setExchangeRate(Currency::RUB, Currency::GBP, 0.0087 + (rand() % 5) / 1000.0);
    setExchangeRate(Currency::RUB, Currency::JPY, 1.63 + (rand() % 20) / 100.0);
    setExchangeRate(Currency::RUB, Currency::CNY, 0.079 + (rand() % 5) / 1000.0);
    
    cout << "Exchange rates updated successfully" << endl;
}

string CurrencyConverter::getCurrencySymbol(Currency currency) const {
    switch (currency) {
        case Currency::RUB: return "₽";
        case Currency::USD: return "$";
        case Currency::EUR: return "€";
        case Currency::GBP: return "£";
        case Currency::JPY: return "¥";
        case Currency::CNY: return "¥";
        default: return "?";
    }
}

string CurrencyConverter::getCurrencyName(Currency currency) const {
    switch (currency) {
        case Currency::RUB: return "RUB";
        case Currency::USD: return "USD";
        case Currency::EUR: return "EUR";
        case Currency::GBP: return "GBP";
        case Currency::JPY: return "JPY";
        case Currency::CNY: return "CNY";
        default: return "UNKNOWN";
    }
}

void CurrencyConverter::displayAllRates() const {
    cout << "=== EXCHANGE RATES ===" << endl
         << "Base Currency: " << getCurrencySymbol(baseCurrency) << " (" << getCurrencyName(baseCurrency) << ")" << endl << endl;
    
    vector<Currency> currencies = {Currency::USD, Currency::EUR, Currency::GBP, Currency::JPY, Currency::CNY};
    
    // Прямые курсы (из базовой валюты)
    cout << "Direct Rates:" << endl;
    for (const auto& currency : currencies) {
        if (currency != baseCurrency) {
            try {
                double rate = getExchangeRate(baseCurrency, currency);
                cout << "1 " << getCurrencySymbol(baseCurrency) << " = " 
                     << fixed << setprecision(4) << rate << " " 
                     << getCurrencySymbol(currency) << " (" << getCurrencyName(currency) << ")" << endl;
            } catch (const CurrencyConversionException& e) {
                cout << "Rate not available for " << getCurrencyName(currency) << endl;
            }
        }
    }
    
    cout << endl << "Reverse Rates:" << endl;
    // Обратные курсы (в базовую валюту)
    for (const auto& currency : currencies) {
        if (currency != baseCurrency) {
            try {
                double rate = getExchangeRate(currency, baseCurrency);
                cout << "1 " << getCurrencySymbol(currency) << " = " 
                     << fixed << setprecision(4) << rate << " " 
                     << getCurrencySymbol(baseCurrency) << " (" << getCurrencyName(currency) << ")" << endl;
            } catch (const CurrencyConversionException& e) {
                cout << "Rate not available for " << getCurrencyName(currency) << endl;
            }
        }
    }
    cout << "=====================" << endl;
}

bool CurrencyConverter::hasExchangeRate(const CurrencyPair& pair) const {
    return exchangeRates.find(pair) != exchangeRates.end();
}

void CurrencyConverter::removeExchangeRate(const CurrencyPair& pair) {
    auto it = exchangeRates.find(pair);
    if (it != exchangeRates.end()) {
        exchangeRates.erase(it);
        
        // Также удаляем обратную пару
        CurrencyPair reversePair = pair.getReversePair();
        auto reverseIt = exchangeRates.find(reversePair);
        if (reverseIt != exchangeRates.end()) {
            exchangeRates.erase(reverseIt);
        }
    }
}

void CurrencyConverter::clearAllRates() {
    exchangeRates.clear();
    initializeDefaultRates(); // Восстанавливаем базовые курсы
}

void CurrencyConverter::initializeDefaultRates() {
    // Устанавливаем реалистичные курсы валют
    setExchangeRate(Currency::RUB, Currency::USD, 0.011);
    setExchangeRate(Currency::RUB, Currency::EUR, 0.010);
    setExchangeRate(Currency::RUB, Currency::GBP, 0.0087);
    setExchangeRate(Currency::RUB, Currency::JPY, 1.63);
    setExchangeRate(Currency::RUB, Currency::CNY, 0.079);
}

void CurrencyConverter::validateCurrency(Currency currency) const {
    if (currency < Currency::RUB || currency > Currency::CNY) {
        throw CurrencyConversionException("Invalid currency specified: " + to_string(static_cast<int>(currency)));
    }
}