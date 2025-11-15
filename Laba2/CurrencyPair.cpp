#include "CurrencyPair.hpp"

using namespace std;

CurrencyPair::CurrencyPair(Currency from, Currency to) : from(from), to(to) {}

Currency CurrencyPair::getFrom() const { return from; }

Currency CurrencyPair::getTo() const { return to; }

bool CurrencyPair::operator==(const CurrencyPair& other) const {
    return from == other.from && to == other.to;
}

string CurrencyPair::toString() const {
    return to_string(static_cast<int>(from)) + "_" + to_string(static_cast<int>(to));
}

CurrencyPair CurrencyPair::getReversePair() const {
    return CurrencyPair(to, from);
}

size_t CurrencyPair::Hash::operator()(const CurrencyPair& pair) const {
    return hash<int>{}(static_cast<int>(pair.from)) ^ 
           (hash<int>{}(static_cast<int>(pair.to)) << 1);
}