#include "include/CantorSet.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void demonstrateBasicOperations() {
    std::cout << "=== БАЗОВЫЕ ОПЕРАЦИИ С МНОЖЕСТВАМИ ===" << std::endl;
    
    // Создание множеств
    CantorSet A("{1,2,3,4}");
    CantorSet B("{3,4,5,6}");
    
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "Мощность A: " << A.cardinality() << std::endl;
    std::cout << "Мощность B: " << B.cardinality() << std::endl;
    
    // Операции над множествами
    std::cout << "A + B (объединение) = " << (A + B) << std::endl;
    std::cout << "A * B (пересечение) = " << (A * B) << std::endl;
    std::cout << "A - B (разность) = " << (A - B) << std::endl;
    std::cout << "B - A (разность) = " << (B - A) << std::endl;
    
    // Проверка принадлежности
    std::cout << "1 ∈ A: " << (A[std::string("1")] ? "да" : "нет") << std::endl;
    std::cout << "5 ∈ A: " << (A[std::string("5")] ? "да" : "нет") << std::endl;
    std::cout << "A == B: " << (A == B ? "да" : "нет") << std::endl;
    
    std::cout << std::endl;
}

void demonstrateCantorSets() {
    std::cout << "=== КАНТОРОВЫ МНОЖЕСТВА ===" << std::endl;
    
    // Простое множество
    CantorSet simple("{1,2,3,4,5,6}");
    std::cout << "Исходное множество: " << simple << std::endl;
    
    CantorSet cantorSimple = CantorSet::createCompleteCantorSet(simple);
    std::cout << "Канторово множество: " << cantorSimple << std::endl;
    
    // Показ уровней
    std::cout << "Уровни канторова множества:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        CantorSet level = cantorSimple.getLevel(i);
        if (!level.isEmpty()) {
            std::cout << "  Уровень " << i << ": " << level << std::endl;
        }
    }
    
    std::cout << std::endl;
}

void demonstrateComplexSets() {
    std::cout << "=== СЛОЖНЫЕ МНОЖЕСТВА С ПОДМНОЖЕСТВАМИ ===" << std::endl;
    
    // Создание множества с подмножествами вручную
    CantorSet complex;
    complex.addElement("apple");
    complex.addElement("banana");
    
    // Создание подмножества
    auto subset1 = std::make_unique<CantorSet>();
    subset1->addElement("x");
    subset1->addElement("y");
    complex.addSubset(std::move(subset1));
    
    // Создание еще одного подмножества
    auto subset2 = std::make_unique<CantorSet>();
    subset2->addElement("hello");
    subset2->addElement("world");
    complex.addSubset(std::move(subset2));
    
    std::cout << "Сложное множество: " << complex << std::endl;
    std::cout << "Общее количество элементов: " << complex.totalElements() << std::endl;
    std::cout << "Максимальная глубина: " << complex.getMaxDepth() << std::endl;
    
    // Создание канторова множества из сложного
    CantorSet cantorComplex = CantorSet::createCompleteCantorSet(complex);
    std::cout << "Канторово множество: " << cantorComplex << std::endl;
    
    std::cout << std::endl;
}

void demonstrateSetOperations() {
    std::cout << "=== РАСШИРЕННЫЕ ОПЕРАЦИИ ===" << std::endl;
    
    CantorSet set1("{a,b,c,d,e}");
    CantorSet set2("{c,d,e,f,g}");
    
    std::cout << "set1 = " << set1 << std::endl;
    std::cout << "set2 = " << set2 << std::endl;
    
    // Составные операции
    set1 += set2;
    std::cout << "После set1 += set2: " << set1 << std::endl;
    
    set1 -= CantorSet("{a,f}");
    std::cout << "После set1 -= {a,f}: " << set1 << std::endl;
    
    set1 *= CantorSet("{b,c,d}");
    std::cout << "После set1 *= {b,c,d}: " << set1 << std::endl;
    
    // Удаление элементов
    set1.remove(std::string("b"));
    std::cout << "После удаления 'b': " << set1 << std::endl;
    
    std::cout << std::endl;
}

void demonstrateFromFile(const std::string& filename) {
    std::cout << "=== ЧТЕНИЕ ИЗ ФАЙЛА ===" << std::endl;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Файл " << filename << " не найден" << std::endl;
        return;
    }
    
    std::string line;
    int counter = 1;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::cout << "--- Множество " << counter << " ---" << std::endl;
        std::cout << "Из файла: " << line << std::endl;
        
        try {
            CantorSet original(line);
            CantorSet cantor = CantorSet::createCompleteCantorSet(original);
            
            std::cout << "Канторово множество: " << cantor << std::endl;
            std::cout << "Мощность: " << cantor.cardinality() << std::endl;
            std::cout << "Всего элементов: " << cantor.totalElements() << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
        counter++;
        std::cout << std::endl;
    }
    
    file.close();
}

void demonstrateEdgeCases() {
    std::cout << "=== ГРАНИЧНЫЕ СЛУЧАИ ===" << std::endl;
    
    // Пустое множество
    CantorSet empty("{}");
    std::cout << "Пустое множество: " << empty << std::endl;
    std::cout << "Пустое? " << (empty.isEmpty() ? "да" : "нет") << std::endl;
    
    // Множество с одним элементом
    CantorSet single("{единственный}");
    std::cout << "Один элемент: " << single << std::endl;
    CantorSet cantorSingle = CantorSet::createCompleteCantorSet(single);
    std::cout << "Канторово: " << cantorSingle << std::endl;
    
    // Большое множество
    CantorSet large("{1,2,3,4,5,6,7,8,9,10,11,12}");
    std::cout << "Большое множество: " << large << std::endl;
    CantorSet cantorLarge = CantorSet::createCompleteCantorSet(large);
    std::cout << "Канторово большое: " << cantorLarge << std::endl;
    
    std::cout << std::endl;
}

int main() {
    std::cout << "ДЕМОНСТРАЦИЯ РАБОТЫ СИСТЕМЫ МНОЖЕСТВ" << std::endl;
    std::cout << "=====================================" << std::endl << std::endl;
    
    demonstrateBasicOperations();
    demonstrateCantorSets();
    demonstrateComplexSets();
    demonstrateSetOperations();
    demonstrateEdgeCases();
    demonstrateFromFile("input.txt");

    CantorSet original(std::string("{1,2,3,4,5,6}"));
        CantorSet cantor = CantorSet::createCompleteCantorSet(original);
        CantorSet proverka = cantor.getLevel(2);
    std::cout<<proverka.toString()<<"\n";

     CantorSet origin(std::string("{1, 2,{a,b,c},5,6,{d,e}}"));
        CantorSet cantor2 = CantorSet::createCompleteCantorSet(origin);
        std::cout<<cantor2.toString()<<"\n";
    
    std::cout << "=====================================" << std::endl;
    std::cout << "ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА" << std::endl;
    
    return 0;
}