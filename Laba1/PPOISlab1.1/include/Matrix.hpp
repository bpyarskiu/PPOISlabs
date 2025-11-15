#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>

/**
 * @class Matrix
 * @brief Класс для работы с двумерными матрицами чисел с плавающей точкой
 * 
 * Класс предоставляет функциональность для создания, модификации и анализа матриц,
 * включая операции линейной алгебры и ввод/вывод данных.
 */
class Matrix {
private:
    size_t rows_;       ///< Количество строк в матрице
    size_t cols_;       ///< Количество столбцов в матрице
    double** data_;     ///< Двумерный массив, содержащий данные матрицы

    /**
     * @brief Освобождает память, занятую матрицей
     */
    void clear();
    
    /**
     * @brief Выделяет память для матрицы заданного размера
     * @param rows Количество строк
     * @param cols Количество столбцов
     */
    void allocateMemory(size_t rows, size_t cols);

public:
    // Конструкторы и деструктор
    
    /**
     * @brief Конструктор матрицы
     * @param rows Количество строк (по умолчанию 0)
     * @param cols Количество столбцов (по умолчанию 0)
     */
    Matrix(size_t rows = 0, size_t cols = 0);
    
    /**
     * @brief Конструктор копирования
     * @param other Матрица для копирования
     */
    Matrix(const Matrix& other);
    
    /**
     * @brief Деструктор матрицы
     */
    ~Matrix();

    // Оператор присваивания
    
    /**
     * @brief Оператор присваивания
     * @param other Матрица для копирования
     * @return Ссылка на текущую матрицу
     */
    Matrix& operator=(const Matrix& other);

    // Операторы инкремента/декремента
    
    /**
     * @brief Преинкремент (увеличивает все элементы на 1)
     * @return Ссылка на измененную матрицу
     */
    Matrix& operator++();
    
    /**
     * @brief Постинкремент (увеличивает все элементы на 1)
     * @return Копия матрицы до изменения
     */
    Matrix operator++(int);
    
    /**
     * @brief Предекремент (уменьшает все элементы на 1)
     * @return Ссылка на измененную матрицу
     */
    Matrix& operator--();
    
    /**
     * @brief Постдекремент (уменьшает все элементы на 1)
     * @return Копия матрицы до изменения
     */
    Matrix operator--(int);

    // Основные методы из задания
    
    /**
     * @brief Изменяет размер матрицы
     * @param new_rows Новое количество строк
     * @param new_cols Новое количество столбцов
     */
    void resize(size_t new_rows, size_t new_cols);
    
    /**
     * @brief Загружает матрицу из файла
     * @param filename Имя файла для загрузки
     * @throws std::runtime_error Если файл не может быть открыт
     */
    void loadFromFile(const std::string& filename);
    
    /**
     * @brief Получает подматрицу из текущей матрицы
     * @param start_row Начальная строка
     * @param start_col Начальный столбец
     * @param sub_rows Количество строк в подматрице
     * @param sub_cols Количество столбцов в подматрице
     * @return Новая матрица, содержащая подматрицу
     * @throws std::out_of_range Если индексы выходят за границы
     */
    Matrix getSubmatrix(size_t start_row, size_t start_col, size_t sub_rows, size_t sub_cols) const;
    
    /**
     * @brief Транспонирует матрицу
     * @return Новая транспонированная матрица
     */
    Matrix transpose() const;

    // Проверки типа матрицы
    
    /**
     * @brief Проверяет, является ли матрица квадратной
     * @return true если матрица квадратная, false в противном случае
     */
    bool isSquare() const;
    
    /**
     * @brief Проверяет, является ли матрица нулевой
     * @return true если все элементы равны 0, false в противном случае
     */
    bool isZero() const;
    
    /**
     * @brief Проверяет, является ли матрица единичной
     * @return true если матрица единичная, false в противном случае
     */
    bool isIdentity() const;
    
    /**
     * @brief Проверяет, является ли матрица диагональной
     * @return true если матрица диагональная, false в противном случае
     */
    bool isDiagonal() const;
    
    /**
     * @brief Проверяет, является ли матрица симметричной
     * @return true если матрица симметричная, false в противном случае
     */
    bool isSymmetric() const;
    
    /**
     * @brief Проверяет, является ли матрица верхней треугольной
     * @return true если матрица верхняя треугольная, false в противном случае
     */
    bool isUpperTriangular() const;
    
    /**
     * @brief Проверяет, является ли матрица нижней треугольной
     * @return true если матрица нижняя треугольная, false в противном случае
     */
    bool isLowerTriangular() const;

    // Методы доступа
    
    /**
     * @brief Возвращает количество строк
     * @return Количество строк в матрице
     */
    size_t getRows() const { return rows_; }
    
    /**
     * @brief Возвращает количество столбцов
     * @return Количество столбцов в матрице
     */
    size_t getCols() const { return cols_; }
    
    /**
     * @brief Доступ к элементу матрицы с проверкой границ
     * @param i Индекс строки
     * @param j Индекс столбца
     * @return Ссылка на элемент матрицы
     * @throws std::out_of_range Если индексы выходят за границы
     */
    double& at(size_t i, size_t j);
    
    /**
     * @brief Константный доступ к элементу матрицы с проверкой границ
     * @param i Индекс строки
     * @param j Индекс столбца
     * @return Константная ссылка на элемент матрицы
     * @throws std::out_of_range Если индексы выходят за границы
     */
    const double& at(size_t i, size_t j) const;

    // Вспомогательные методы
    
    /**
     * @brief Заполняет матрицу указанным значением
     * @param value Значение для заполнения
     */
    void fill(double value);
    
    /**
     * @brief Выводит матрицу в стандартный поток вывода
     */
    void print() const;

    // Дружественная функция для вывода
    
    /**
     * @brief Оператор вывода матрицы в поток
     * @param os Выходной поток
     * @param m Матрица для вывода
     * @return Ссылка на выходной поток
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};