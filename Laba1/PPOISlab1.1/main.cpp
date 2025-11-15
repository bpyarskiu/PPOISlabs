#include "include/Matrix.hpp"
#include <iostream>

void demonstrateMatrixOperations() {
    std::cout << "=== Демонстрация работы с матрицами ===" << std::endl;
    
    // 1. Создание матриц
    std::cout << "1. Создание матрицы 3x3:" << std::endl;
    Matrix m1(3, 3);
    double counter = 1.0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m1.at(i, j) = counter++;
        }
    }
    m1.print();
    
    // 2. Инкремент/декремент
    std::cout << "\n2. Преинкремент матрицы:" << std::endl;
    ++m1;
    m1.print();
    
    std::cout << "Постинкремент матрицы (возвращает старую версию):" << std::endl;
    Matrix m1_old = m1++;
    std::cout << "Старая версия:" << std::endl;
    m1_old.print();
    std::cout << "Текущая версия:" << std::endl;
    m1.print();
    
    // 3. Изменение размера
    std::cout << "\n3. Изменение размера до 4x2:" << std::endl;
    m1.resize(4, 2);
    m1.print();
    
    // 4. Создание и проверка специальных матриц
    std::cout << "\n4. Создание единичной матрицы 3x3:" << std::endl;
    Matrix identity(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        identity.at(i, i) = 1.0;
    }
    identity.print();
    
    std::cout << "Проверки для единичной матрицы:" << std::endl;
    std::cout << "Квадратная: " << identity.isSquare() << std::endl;
    std::cout << "Единичная: " << identity.isIdentity() << std::endl;
    std::cout << "Диагональная: " << identity.isDiagonal() << std::endl;
    
    // 5. Транспонирование
    std::cout << "\n5. Создание матрицы 2x3 и её транспонирование:" << std::endl;
    Matrix m2(2, 3);
    m2.at(0, 0) = 1; m2.at(0, 1) = 2; m2.at(0, 2) = 3;
    m2.at(1, 0) = 4; m2.at(1, 1) = 5; m2.at(1, 2) = 6;
    
    std::cout << "Исходная матрица:" << std::endl;
    m2.print();
    
    Matrix m2_transposed = m2.transpose();
    std::cout << "Транспонированная матрица:" << std::endl;
    m2_transposed.print();
    
    // 6. Подматрица
    std::cout << "\n6. Извлечение подматрицы 2x2 из матрицы 3x3:" << std::endl;
    Matrix m3(3, 3);
    counter = 1.0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m3.at(i, j) = counter++;
        }
    }
    std::cout << "Исходная матрица:" << std::endl;
    m3.print();
    
    Matrix sub = m3.getSubmatrix(0, 1, 2, 2);
    std::cout << "Подматрица [0,1] размером 2x2:" << std::endl;
    sub.print();
    
    // 7. Симметрическая матрица
    std::cout << "\n7. Создание симметрической матрицы:" << std::endl;
    Matrix symmetric(3, 3);
    symmetric.at(0, 0) = 1; symmetric.at(0, 1) = 2; symmetric.at(0, 2) = 3;
    symmetric.at(1, 0) = 2; symmetric.at(1, 1) = 5; symmetric.at(1, 2) = 6;
    symmetric.at(2, 0) = 3; symmetric.at(2, 1) = 6; symmetric.at(2, 2) = 9;
    symmetric.print();
    
    std::cout << "Симметрическая: " << symmetric.isSymmetric() << std::endl;
    
    // 8. Загрузка из файла (пример)
    std::cout << "\n8. Пример загрузки из файла:" << std::endl;
    try {
        // Сначала создадим тестовый файл
        std::ofstream test_file("test_matrix.txt");
        test_file << "2 3\n1.5 2.5 3.5\n4.5 5.5 6.5";
        test_file.close();
        
        Matrix from_file;
        from_file.loadFromFile("test_matrix.txt");
        std::cout << "Матрица загруженная из файла:" << std::endl;
        from_file.print();
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    try {
        demonstrateMatrixOperations();
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}