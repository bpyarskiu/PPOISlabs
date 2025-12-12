#include "../Guide.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <string> 

using namespace std;

SUITE(GuideTests) {

    TEST(Guide_Constructor) {
        ContactInfo contact("guide@example.com", "+375291112233");
        vector<string> languages = {"English", "Russian"};
        vector<string> specializations = {"History", "Culture"};
        
        Guide guide(1, "John", "Guide", contact, 3001, 
                   "Tour Guide", 40000.0, languages, specializations, 5, 4.7);
        
        CHECK_EQUAL("John Guide", guide.getFullName());
        CHECK_EQUAL(5, guide.getExperienceYears());
        CHECK_EQUAL(4.7, guide.getRating());
        CHECK_EQUAL(2u, guide.getLanguages().size());
        CHECK_EQUAL(2u, guide.getSpecializations().size());
    }

    TEST(Guide_InvalidConstructor_EmptyLanguages) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> emptyLanguages;
        vector<string> specializations = {"History"};
        
        CHECK_THROW(
            Guide(1, "Test", "Guide", contact, 3001, "Guide", 30000.0,
                 emptyLanguages, specializations, 3, 4.0),
            invalid_argument
        );
    }

    TEST(Guide_AddLanguage) {
        ContactInfo contact("guide@example.com", "+375291112233");
        vector<string> languages = {"English"};
        vector<string> specializations = {"History"};
        
        Guide guide(1, "John", "Guide", contact, 3001, 
                   "Tour Guide", 40000.0, languages, specializations, 3, 4.5);
        
        // Добавляем новый язык
        guide.addLanguage("German");
        auto langs = guide.getLanguages();
        
        CHECK_EQUAL(2u, langs.size());
        CHECK(find(langs.begin(), langs.end(), std::string("German")) != langs.end());
        
        // Пытаемся добавить дубликат
        guide.addLanguage("English");
        CHECK_EQUAL(2u, guide.getLanguages().size()); // Размер не должен измениться
        
        // Пытаемся добавить пустой язык
        CHECK_THROW(guide.addLanguage(""), invalid_argument);
    }

    TEST(Guide_AddSpecialization) {
        ContactInfo contact("guide@example.com", "+375291112233");
        vector<string> languages = {"English"};
        vector<string> specializations = {"History"};
        
        Guide guide(1, "John", "Guide", contact, 3001, 
                   "Tour Guide", 40000.0, languages, specializations, 3, 4.5);
        
        // Добавляем новую специализацию
        guide.addSpecialization("Art");
        auto specs = guide.getSpecializations();
        
        CHECK_EQUAL(2u, specs.size());
        CHECK(find(specs.begin(), specs.end(), std::string("Art")) != specs.end());
        
        // Пытаемся добавить дубликат
        guide.addSpecialization("History");
        CHECK_EQUAL(2u, guide.getSpecializations().size());
        
        // Пытаемся добавить пустую специализацию
        CHECK_THROW(guide.addSpecialization(""), invalid_argument);
    }

    TEST(Guide_SpeaksLanguage) {
        ContactInfo contact("guide@example.com", "+375291112233");
        vector<string> languages = {"English", "Russian", "French"};
        vector<string> specializations = {"History"};
        
        Guide guide(1, "John", "Guide", contact, 3001, 
                   "Tour Guide", 40000.0, languages, specializations, 5, 4.8);
        
        // Проверяем известные языки
        CHECK(guide.speaksLanguage("English"));
        CHECK(guide.speaksLanguage("Russian"));
        CHECK(guide.speaksLanguage("French"));
        
        // Проверяем неизвестный язык
        CHECK(!guide.speaksLanguage("German"));
        CHECK(!guide.speaksLanguage(""));
        CHECK(!guide.speaksLanguage("Spanish"));
    }

    TEST(Guide_DisplayInfo) {
        ContactInfo contact("guide@example.com", "+375291112233");
        vector<string> languages = {"English", "Russian"};
        vector<string> specializations = {"History", "Architecture"};
        
        Guide guide(1, "Anna", "Smith", contact, 3002, 
                   "Senior Guide", 50000.0, languages, specializations, 8, 4.9);
        
        StdoutRedirect redirect;
        guide.displayInfo();
        string output = redirect.getOutput();
        
        // Проверяем наличие ключевой информации
        CHECK(output.find("Anna Smith") != string::npos);
        CHECK(output.find("Experience: 8 years") != string::npos);
        CHECK(output.find("Rating: 4.9/5") != string::npos);
        CHECK(output.find("English") != string::npos);
        CHECK(output.find("Russian") != string::npos);
        CHECK(output.find("History") != string::npos);
        CHECK(output.find("Architecture") != string::npos);
    }

    TEST(Guide_GetMethods) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> languages = {"English", "Spanish", "Italian"};
        vector<string> specializations = {"Art", "Food"};
        
        Guide guide(1, "Maria", "Rossi", contact, 3003, 
                   "Guide", 35000.0, languages, specializations, 4, 4.6);
        
        // Проверяем все геттеры
        CHECK_EQUAL(4, guide.getExperienceYears());
        CHECK_EQUAL(4.6, guide.getRating());
        
        auto langs = guide.getLanguages();
        CHECK_EQUAL(3u, langs.size());
        CHECK(find(langs.begin(), langs.end(), std::string("Italian")) != langs.end());
        
        auto specs = guide.getSpecializations();
        CHECK_EQUAL(2u, specs.size());
        CHECK(find(specs.begin(), specs.end(), std::string("Food")) != specs.end());
    }

    TEST(Guide_EdgeCases) {
        ContactInfo contact("test@example.com", "+375291112233");
        vector<string> languages = {"English"};
        vector<string> specializations;
        
        // Создаем гида без специализаций (должно быть разрешено)
        Guide guide(1, "Test", "Guide", contact, 3004, 
                   "Guide", 30000.0, languages, specializations, 1, 3.0);
        
        CHECK_EQUAL(0u, guide.getSpecializations().size());
        
        // Проверяем минимальный рейтинг
        Guide lowRated(2, "Low", "Rating", contact, 3005, 
                      "Guide", 25000.0, languages, specializations, 0, 1.0);
        
        CHECK_EQUAL(1.0, lowRated.getRating());
    }
}