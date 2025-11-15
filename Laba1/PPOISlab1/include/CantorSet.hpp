#pragma once

#include "MySet.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

/**
 * @class CantorSet
 * @brief Класс для работы с множествами в теории множеств Кантора
 * 
 * Класс реализует концепцию множеств Кантора, где множества могут содержать
 * как простые элементы (атомы), так и другие множества в качестве подмножеств.
 * Поддерживает рекурсивное построение полных канторовых множеств и операции над ними.
 */
class CantorSet {
private:
    MySet<std::string> elements;  ///< Простые элементы (атомы) множества
    MySet<std::unique_ptr<CantorSet>> subsets;  ///< Подмножества множества
    
    /**
     * @brief Рекурсивно строит полное канторово множество
     * @param all_elements Множество всех доступных элементов
     * @param all_subsets Множество всех доступных подмножеств
     */
    void buildCompleteCantorSet(const MySet<std::string>& all_elements,
                               const MySet<std::unique_ptr<CantorSet>>& all_subsets);
    
    /**
     * @brief Возвращает отсортированные элементы множества
     * @return Вектор строк с отсортированными элементами
     */
    std::vector<std::string> getSortedElements() const;
    
public:
    // Конструкторы
    
    /**
     * @brief Конструктор по умолчанию (создает пустое множество)
     */
    CantorSet();
    
    /**
     * @brief Конструктор из множества элементов и подмножеств
     * @param elements Множество строк-элементов
     * @param subsets Множество подмножеств (по умолчанию пустое)
     */
    CantorSet(const MySet<std::string>& elements, 
              const MySet<std::unique_ptr<CantorSet>>& subsets = {});
    
    /**
     * @brief Конструктор из вектора элементов
     * @param elements Вектор строк-элементов
     */
    CantorSet(const std::vector<std::string>& elements);
    
    /**
     * @brief Конструктор из C-строки (создает множество с одним элементом)
     * @param str C-строка для создания элемента
     */
    CantorSet(const char* str);
    
    /**
     * @brief Конструктор из std::string (создает множество с одним элементом)
     * @param str Строка для создания элемента
     */
    CantorSet(const std::string& str);
    
    /**
     * @brief Конструктор копирования
     * @param other Множество для копирования
     */
    CantorSet(const CantorSet& other);
    
    // Операторы присваивания
    
    /**
     * @brief Оператор присваивания
     * @param other Множество для копирования
     * @return Ссылка на текущее множество
     */
    CantorSet& operator=(const CantorSet& other);
    
    /**
     * @brief Сортирует элементы множества
     * @param instance Вектор элементов для сортировки
     * @return true если сортировка выполнена успешно
     */
    bool sorting(std::vector<std::string> instance);
    
    // Основные методы построения полного канторова множества
    
    /**
     * @brief Создает полное канторово множество из заданных элементов и подмножеств
     * @param elements Множество элементов
     * @param subsets Множество подмножеств (по умолчанию пустое)
     * @return Полное канторово множество
     */
    static CantorSet createCompleteCantorSet(const MySet<std::string>& elements,
                                           const MySet<std::unique_ptr<CantorSet>>& subsets = {});
    
    /**
     * @brief Создает полное канторово множество из существующего множества
     * @param set Исходное множество
     * @return Полное канторово множество
     */
    static CantorSet createCompleteCantorSet(const CantorSet& set);
    
    // Проверка принадлежности
    
    /**
     * @brief Проверяет принадлежность элемента множеству
     * @param element Элемент для проверки
     * @return true если элемент принадлежит множеству
     */
    bool contains(const std::string& element) const;
    
    /**
     * @brief Проверяет принадлежность подмножества множеству
     * @param subset Подмножество для проверки
     * @return true если подмножество принадлежит множеству
     */
    bool contains(const CantorSet& subset) const;
    
    /**
     * @brief Оператор проверки принадлежности элемента
     * @param element Элемент для проверки
     * @return true если элемент принадлежит множеству
     */
    bool operator[](const std::string& element) const ;
    
    /**
     * @brief Оператор проверки принадлежности подмножества
     * @param subset Подмножество для проверки
     * @return true если подмножество принадлежит множеству
     */
    bool operator[](const CantorSet& subset) const ;
    
    /**
     * @brief Добавляет элемент в множество
     * @param element Элемент для добавления
     */
    void addElement(const std::string& element);
    
    /**
     * @brief Добавляет подмножество в множество
     * @param subset Подмножество для добавления
     */
    void addSubset(std::unique_ptr<CantorSet> subset);
    
    // Характеристики множества
    
    /**
     * @brief Проверяет, является ли множество пустым
     * @return true если множество не содержит элементов и подмножеств
     */
    bool isEmpty() const;
    
    /**
     * @brief Возвращает мощность множества (количество элементов и подмножеств)
     * @return Мощность множества
     */
    size_t cardinality() const;
    
    /**
     * @brief Возвращает общее количество элементов (включая вложенные)
     * @return Общее количество элементов
     */
    size_t totalElements() const;
    
    /**
     * @brief Возвращает максимальную глубину вложенности множества
     * @return Максимальная глубина вложенности
     */
    size_t getMaxDepth() const;
    
    /**
     * @brief Получает множество элементов определенного уровня вложенности
     * @param level Уровень вложенности
     * @return Множество элементов заданного уровня
     */
    CantorSet getLevel(int level) const;
    
    // Преобразование в строку
    
    /**
     * @brief Преобразует множество в строковое представление
     * @return Строковое представление множества
     */
    std::string toString() const;
    
    /**
     * @brief Преобразует множество в подробное строковое представление
     * @return Подробное строковое представление множества
     */
    std::string toDetailedString() const;
    
    /**
     * @brief Преобразует множество в строку в формате Кантора
     * @return Строковое представление в формате Кантора
     */
    std::string toCantorString() const;
    
    // Ввод/вывод
    
    /**
     * @brief Оператор вывода множества в поток
     * @param os Выходной поток
     * @param set Множество для вывода
     * @return Ссылка на выходной поток
     */
    friend std::ostream& operator<<(std::ostream& os, const CantorSet& set);
    
    /**
     * @brief Оператор ввода множества из потока
     * @param is Входной поток
     * @param set Множество для заполнения
     * @return Ссылка на входной поток
     */
    friend std::istream& operator>>(std::istream& is, CantorSet& set);
    
    // Операторы сравнения
    
    /**
     * @brief Оператор проверки на равенство множеств
     * @param other Множество для сравнения
     * @return true если множества равны
     */
    bool operator==(const CantorSet& other) const;
    
    /**
     * @brief Оператор проверки "меньше"
     * @param other Множество для сравнения
     * @return true если текущее множество "меньше"
     */
    bool operator<(const CantorSet& other) const;
    
    /**
     * @brief Оператор проверки "больше"
     * @param other Множество для сравнения
     * @return true если текущее множество "больше"
     */
    bool operator>(const CantorSet& other) const;
    
    // Операции над множествами
    
    /**
     * @brief Объединение множеств
     * @param other Множество для объединения
     * @return Новое множество - результат объединения
     */
    CantorSet operator+(const CantorSet& other) const;
    
    /**
     * @brief Оператор объединения с присваиванием
     * @param other Множество для объединения
     * @return Ссылка на текущее множество
     */
    CantorSet& operator+=(const CantorSet& other);
    
    /**
     * @brief Пересечение множеств
     * @param other Множество для пересечения
     * @return Новое множество - результат пересечения
     */
    CantorSet operator*(const CantorSet& other) const;
    
    /**
     * @brief Оператор пересечения с присваиванием
     * @param other Множество для пересечения
     * @return Ссылка на текущее множество
     */
    CantorSet& operator*=(const CantorSet& other);
    
    /**
     * @brief Разность множеств
     * @param other Множество для вычитания
     * @return Новое множество - результат разности
     */
    CantorSet operator-(const CantorSet& other) const;
    
    /**
     * @brief Оператор разности с присваиванием
     * @param other Множество для вычитания
     * @return Ссылка на текущее множество
     */
    CantorSet& operator-=(const CantorSet& other);
    
    /**
     * @brief Удаляет элемент из множества
     * @param element Элемент для удаления
     * @return true если элемент был удален
     */
    bool remove(const std::string& element);
    
    /**
     * @brief Удаляет подмножество из множества
     * @param subset Подмножество для удаления
     * @return true если подмножество было удалено
     */
    bool remove(const CantorSet& subset);
    
    // Итерация по элементам
    
    /**
     * @brief Выполняет callback-функцию для каждого элемента множества
     * @param callback Функция обратного вызова
     */
    void forEachElement(std::function<void(const std::string&)> callback) const;
    
    /**
     * @brief Выполняет callback-функцию для каждого подмножества
     * @param callback Функция обратного вызова
     */
    void forEachSubset(std::function<void(const CantorSet&)> callback) const;
    
    // Методы доступа
    
    /**
     * @brief Возвращает множество элементов
     * @return Константная ссылка на множество элементов
     */
    const MySet<std::string>& getElements() const { return elements; }
    
    /**
     * @brief Возвращает множество подмножеств
     * @return Константная ссылка на множество подмножеств
     */
    const MySet<std::unique_ptr<CantorSet>>& getSubsets() const { return subsets; }
};