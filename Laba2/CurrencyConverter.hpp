#pragma once
#include <string>
#include <unordered_map>
#include "CurrencyPair.hpp"
#include "Currency.hpp"
#include <vector>

class CurrencyConverter {
private:
    std::unordered_map<CurrencyPair, double, CurrencyPair::Hash> exchangeRates;  // Добавляем Hash
    Currency baseCurrency;

public:
    CurrencyConverter(Currency baseCurrency = Currency::RUB);

    // Методы управления курсами
    void setExchangeRate(Currency from, Currency to, double rate);
    void setExchangeRate(const CurrencyPair& pair, double rate);
    double getExchangeRate(Currency from, Currency to) const;
    double getExchangeRate(const CurrencyPair& pair) const;
    void updateRatesFromAPI(); // Заглушка для имитации API

    // Основные методы конвертации
    double convert(double amount, Currency from, Currency to) const;
    double convertToBase(double amount, Currency from) const;
    double convertFromBase(double amount, Currency to) const;

    // Вспомогательные методы
    std::string getCurrencySymbol(Currency currency) const;
    std::string getCurrencyName(Currency currency) const;
    void displayAllRates() const;
    
    // Методы для работы с курсами
    bool hasExchangeRate(const CurrencyPair& pair) const;
    void removeExchangeRate(const CurrencyPair& pair);
    void clearAllRates();

private:
    void initializeDefaultRates();
    void validateCurrency(Currency currency) const;
};