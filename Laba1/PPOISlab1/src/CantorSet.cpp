#include "../include/CantorSet.hpp"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>

// ============ КОНСТРУКТОРЫ ============

CantorSet::CantorSet() {}

CantorSet::CantorSet(const MySet<std::string>& elements,
                     const MySet<std::unique_ptr<CantorSet>>& subsets)
    : elements(elements), subsets(subsets) {}

CantorSet::CantorSet(const std::vector<std::string>& elements_vec) {
    for (const auto& elem : elements_vec) {
        this->elements.insert(elem);
    }
}

CantorSet::CantorSet(const char* str) : CantorSet(std::string(str)) {}

CantorSet::CantorSet(const std::string& str) {
    // Простой парсинг строки вида "{element1, element2, ...}"
    if (str == "{}" || str.empty()) return;
    
    std::string content = str.substr(1, str.length() - 2); // Убираем {}
    std::stringstream ss(content);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        // Убираем пробелы
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        
        if (!token.empty()) {
            elements.insert(token);
        }
    }
}

CantorSet::CantorSet(const CantorSet& other) {
    elements = other.elements;
    
    other.subsets.forEach([this](const std::unique_ptr<CantorSet>& subset) {
        subsets.insert(std::make_unique<CantorSet>(*subset));
    });
}

// ============ ОПЕРАТОРЫ ПРИСВАИВАНИЯ ============

CantorSet& CantorSet::operator=(const CantorSet& other) {
    if (this != &other) {
        elements = other.elements;
        subsets.clear();
        
        other.subsets.forEach([this](const std::unique_ptr<CantorSet>& subset) {
            subsets.insert(std::make_unique<CantorSet>(*subset));
        });
    }
    return *this;
}

// ============ ПОСТРОЕНИЕ КАНТОРОВА МНОЖЕСТВА ============

CantorSet CantorSet::createCompleteCantorSet(const MySet<std::string>& elements,
                                           const MySet<std::unique_ptr<CantorSet>>& subsets) {
    CantorSet result;
    result.buildCompleteCantorSet(elements, subsets);
    return result;
}

CantorSet CantorSet::createCompleteCantorSet(const CantorSet& set) {
    return createCompleteCantorSet(set.elements, set.subsets);
}

void CantorSet::buildCompleteCantorSet(const MySet<std::string>& all_elements,
                                      const MySet<std::unique_ptr<CantorSet>>& all_subsets) {
    // Собираем все элементы в один отсортированный список
    std::vector<std::string> sorted_elements;
    all_elements.forEach([&](const std::string& elem) {
        sorted_elements.push_back(elem);
    });
    std::sort(sorted_elements.begin(), sorted_elements.end());
    
    // Базовый случай: если 1 элемент или меньше
    if (sorted_elements.size() <= 1) {
        elements = all_elements;
        subsets = all_subsets;
        return;
    }
    
    // Вычисляем границы третей
    size_t n = sorted_elements.size();
    size_t first_end = n / 3;
    size_t third_start = 2 * n / 3;
    
    // Добавляем первую треть на текущий уровень
    for (size_t i = 0; i < first_end; ++i) {
        elements.insert(sorted_elements[i]);
    }
    
    // Добавляем третью треть на текущий уровень
    for (size_t i = third_start; i < n; ++i) {
        elements.insert(sorted_elements[i]);
    }
    
    // Собираем элементы для следующего уровня
    std::vector<std::string> next_level_elements;
    for (size_t i = 0; i < first_end; ++i) {
        next_level_elements.push_back(sorted_elements[i]);
    }

    for (size_t i = third_start; i < n; ++i) {
        next_level_elements.push_back(sorted_elements[i]);
    }
    
    // Рекурсивно строим следующий уровень, если есть что строить
    if (next_level_elements.size() > 1) {
        MySet<std::string> next_elements;
        for (const auto& elem : next_level_elements) {
            next_elements.insert(elem);
        }
        
        CantorSet next_level = createCompleteCantorSet(next_elements);
        if (!next_level.isEmpty()) {
            subsets.insert(std::make_unique<CantorSet>(next_level));
        }
    } else if (next_level_elements.size() == 1) {
        // Если остался один элемент, просто добавляем его
        elements.insert(next_level_elements[0]);
    }
    
    // Обрабатываем подмножества (если они есть)
    all_subsets.forEach([this](const std::unique_ptr<CantorSet>& subset) {
        CantorSet cantor_subset = createCompleteCantorSet(*subset);
        if (!cantor_subset.isEmpty()) {
            subsets.insert(std::make_unique<CantorSet>(cantor_subset));
        }});
}
// ============ ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ============

std::vector<std::string> CantorSet::getSortedElements() const {
    std::vector<std::string> result;
    elements.forEach([&](const std::string& elem) {
        result.push_back(elem);
    });
    std::sort(result.begin(), result.end());
    return result;}


bool CantorSet::sorting(std::vector<std::string> instance){
    return instance ==this->getSortedElements();
}

// ============ ПРОВЕРКА ПРИНАДЛЕЖНОСТИ ============

bool CantorSet::contains(const std::string& element) const {
    return elements.contains(element);
}

bool CantorSet::contains(const CantorSet& subset) const {
    return subsets.contains(subset);
}

bool CantorSet::operator[](const std::string& element) const { return contains(element); }

bool CantorSet::operator[](const CantorSet& subset) const { return contains(subset); }
// ============ ХАРАКТЕРИСТИКИ ============

bool CantorSet::isEmpty() const {
    return elements.empty() && subsets.empty();
}

size_t CantorSet::cardinality() const {
    return elements.size() + subsets.size();
}

size_t CantorSet::totalElements() const {
    size_t count = elements.size();
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        count += subset->totalElements();
    });
    return count;
}

size_t CantorSet::getMaxDepth() const {
    if (subsets.empty()) {
        return 1;
    }
    
    size_t max_depth = 0;
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        size_t depth = subset->getMaxDepth();
        if (depth > max_depth) {
            max_depth = depth;
        }
    });
    
    return max_depth+1;
}


// ============ ПОЛУЧЕНИЕ УРОВНЯ ============

CantorSet CantorSet::getLevel(int level) const {
    if (level == 0) {
        return *this;
    }
    
    CantorSet result;
    
    // Ищем подмножества на нужной глубине
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        if (level == 1) {
            // Если это следующий уровень, просто добавляем его элементы
            subset->elements.forEach([&](const std::string& elem) {
                result.elements.insert(elem);
            });
        } else {
            // Рекурсивно ищем глубже
            CantorSet deeper = subset->getLevel(level - 1);
            deeper.elements.forEach([&](const std::string& elem) {
                result.elements.insert(elem);
            });
        }
    });
    
    return result;
}

// ============ ПУБЛИЧНЫЕ МЕТОДЫ ДЛЯ ДОБАВЛЕНИЯ ЭЛЕМЕНТОВ ============

void CantorSet::addElement(const std::string& element) {
    elements.insert(element);
}

void CantorSet::addSubset(std::unique_ptr<CantorSet> subset) {
    subsets.insert(std::move(subset));
}


// ============ ПРЕОБРАЗОВАНИЕ В СТРОКУ ============

std::string CantorSet::toString() const {
    if (isEmpty()) return "{}";
    
    std::stringstream ss;
    ss << "{";
    
    bool first = true;
    
    elements.forEach([&](const std::string& elem) {
        if (!first) ss << ", ";
        ss << elem;
        first = false;
    });
    
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        if (!first) ss << ", ";
        ss << subset->toString();
        first = false;
    });
    
    ss << "}";
    return ss.str();
}

std::string CantorSet::toDetailedString() const {
    std::stringstream ss;
    ss << "CantorSet: " << toString() << "\n";
    ss << "Cardinality: " << cardinality() << "\n";
    ss << "Total elements: " << totalElements() << "\n";
    
    if (!subsets.empty()) {
        ss << "Subsets:\n";
        subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
            ss << "  - " << subset->toString() << "\n";
        });
    }
    return ss.str();
}

// ============ СПЕЦИАЛЬНЫЙ ВЫВОД ДЛЯ КАНТОРОВА МНОЖЕСТВА ============

std::string CantorSet::toCantorString() const {
    if (isEmpty()) return "{}";
    std::stringstream ss;
    ss << "{";
    bool first = true;
    // Выводим элементы текущего уровня
    elements.forEach([&](const std::string& elem) {
        if (!first) ss << ",";
        ss << elem;
        first = false;
    });
    // Выводим подмножества (следующие уровни)
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        if (!first) ss << ",";
        ss << subset->toCantorString();
        first = false;
    });
    ss << "}";
    return ss.str();
}

// ============ ВВОД/ВЫВОД ============

std::ostream& operator<<(std::ostream& os, const CantorSet& set) {
    os << set.toString();
    return os;
}

std::istream& operator>>(std::istream& is, CantorSet& set) {
    std::string input;
    std::getline(is, input);
    set = CantorSet(input);
    return is;
}

// ============ ОПЕРАТОРЫ СРАВНЕНИЯ ============

bool CantorSet::operator==(const CantorSet& other) const {
    if (cardinality() != other.cardinality()) return false;
    
    // Сравниваем элементы
    bool equal = true;
    elements.forEach([&](const std::string& elem) {
        if (!other.elements.contains(elem)) {
            equal = false;
        }
    });
    
    if (!equal) return false;
    // Сравниваем подмножества
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        if (!other.subsets.contains(*subset)) {
            equal = false;
        }});
    
    return equal;
}

bool CantorSet::operator<(const CantorSet& other) const {
    return toString() < other.toString();
}
bool CantorSet::operator>(const CantorSet& other) const {
    return toString() > other.toString();
}

// ============ ОПЕРАТОРЫ МНОЖЕСТВ ============

CantorSet CantorSet::operator+(const CantorSet& other) const { // Объединение
        CantorSet result;
        
        // Объединяем элементы
        result.elements = elements + other.elements;
        
        // Объединяем подмножества
        result.subsets = subsets;
        other.subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
            if (!result.subsets.contains(*subset)) {
                result.subsets.insert(std::make_unique<CantorSet>(*subset));
            }});
        
        return result;
}
CantorSet& CantorSet::operator+=(const CantorSet& other) {
        *this = *this + other;
        return *this;
}
CantorSet CantorSet::operator*(const CantorSet& other) const { // Пересечение
        CantorSet result;
        
        // Пересекаем элементы
        result.elements = elements * other.elements;
        
        // Пересекаем подмножества
        subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
            if (other.subsets.contains(*subset)) {
                result.subsets.insert(std::make_unique<CantorSet>(*subset));
            }});
        
        return result;
    }
CantorSet& CantorSet::operator*=(const CantorSet& other) {
        *this = *this * other;
        return *this;
    }
CantorSet CantorSet::operator-(const CantorSet& other) const { // Разность
        CantorSet result;
        
        // Разность элементов
        result.elements = elements - other.elements;
        
        // Разность подмножеств
        subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
            if (!other.subsets.contains(*subset)) {
                result.subsets.insert(std::make_unique<CantorSet>(*subset));
            }
        });
        
        return result;
    }

CantorSet& CantorSet::operator-=(const CantorSet& other) {
        *this = *this - other;
        return *this;
    }

    // Удаление элемента
    bool CantorSet::remove(const std::string& element) {
        return elements.remove(element);
    }

    bool CantorSet::remove(const CantorSet& subset) {
        return subsets.remove(subset);
    }


// ============ ИТЕРАЦИЯ ============

void CantorSet::forEachElement(std::function<void(const std::string&)> callback) const {
    elements.forEach(callback);
}

void CantorSet::forEachSubset(std::function<void(const CantorSet&)> callback) const {
    subsets.forEach([&](const std::unique_ptr<CantorSet>& subset) {
        callback(*subset);
    });
}