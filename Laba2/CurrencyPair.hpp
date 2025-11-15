#pragma once
#include <string>
#include "Currency.hpp"

class CurrencyPair {
private:
    Currency from;
    Currency to;

public:
    CurrencyPair(Currency from, Currency to);
    
    // Геттеры
    Currency getFrom() const;
    Currency getTo() const;
    
    // Операторы сравнения для использования в std::unordered_map
    bool operator==(const CurrencyPair& other) const;
    
    // Метод для преобразования в строку (ключ для map)
    std::string toString() const;
    
    // Метод для получения обратной пары
    CurrencyPair getReversePair() const;

    struct Hash {
        std::size_t operator()(const CurrencyPair& pair) const;
    };
};

// Специализация std::hash для CurrencyPair
namespace std {
    template<>
    struct hash<CurrencyPair> {
        size_t operator()(const CurrencyPair& pair) const {
            return hash<string>()(pair.toString());
        }
    };
}