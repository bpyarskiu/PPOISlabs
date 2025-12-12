#include <UnitTest++/UnitTest++.h>
#include "../Logger.hpp"
#include <sstream>
#include <fstream>
#include <cstdio>
#include "HELPERFILE.cpp"

SUITE(LoggerTests) {
    TEST(LoggerTest_LogMessages) {
        // Создаем логгер с временным файлом
        Logger logger("test_log.txt", true);
        
        // Тестируем разные уровни логирования
        logger.log(LogLevel::INFO, "Test info message");
        logger.log(LogLevel::WARNING, "Test warning message"); 
        logger.log(LogLevel::ERROR, "Test error message");
        
        // Проверяем что файл создался и не пустой
        std::ifstream file("test_log.txt");
        CHECK(file.is_open());
        
        std::string line;
        bool hasContent = false;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                hasContent = true;
                // Проверяем что сообщения содержат нужный текст
                CHECK(line.find("Test") != std::string::npos);
            }
        }
        CHECK(hasContent);
        
        file.close();
        
        // Удаляем временный файл
        std::remove("test_log.txt");
    }
    
    TEST(LoggerTest_ConvenienceMethods) {
        Logger logger("test_log2.txt", false); // Без вывода в консоль
        
        // Тестируем удобные методы
        logger.info("Information message");
        logger.warning("Warning message");
        logger.error("Error message");
        
        // Проверяем запись в файл
        std::ifstream file("test_log2.txt");
        CHECK(file.is_open());
        
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        
        CHECK(content.find("Information message") != std::string::npos);
        CHECK(content.find("Warning message") != std::string::npos); 
        CHECK(content.find("Error message") != std::string::npos);
        CHECK(content.find("INFO") != std::string::npos);
        CHECK(content.find("WARNING") != std::string::npos);
        CHECK(content.find("ERROR") != std::string::npos);
        
        file.close();
        std::remove("test_log2.txt");
    }
    
    TEST(LoggerTest_ConsoleOutput) {
        Logger logger("test_log3.txt", true); // С выводом в консоль
        
        // Не можем легко перехватить cout в UnitTest++, 
        // но можем проверить что не падает
        logger.info("Console output test");
        
        // Проверяем что файл тоже создался
        std::ifstream file("test_log3.txt");
        CHECK(file.is_open());
        file.close();
        
        std::remove("test_log3.txt");
    }
}