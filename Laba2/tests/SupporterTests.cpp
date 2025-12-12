// tests/SupporterTests.cpp
#include <UnitTest++/UnitTest++.h>
#include "../Supporter.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <algorithm> 

using namespace std;

TEST(SupporterTest_Constructor) {
    ContactInfo contact("supporter@test.com", "+375295556677");
    vector<string> languages = {"English", "Russian"};
    
    // Тест успешного создания
    Supporter supporter(1, "Anna", "Support", contact, 5001, 
                       "Customer Support", 40000.0, SupportLevel::STANDARD,
                       languages, 100, 4.5);
    
    CHECK_EQUAL(SupportLevel::STANDARD, supporter.getSupportLevel());
    CHECK_EQUAL(100, supporter.getResolvedTickets());
    CHECK_CLOSE(4.5, supporter.getSatisfactionRating(), 0.01);
    
    // Тест с пустым списком языков
    vector<string> emptyLanguages;
    CHECK_THROW(
        Supporter invalidSupporter(2, "Bob", "Support", contact, 5002,
                                  "Support", 35000.0, SupportLevel::BASIC,
                                  emptyLanguages, 50, 4.0),
        std::invalid_argument
    );
}

TEST(SupporterTest_AddSupportedLanguage) {
    ContactInfo contact("supporter@test.com", "+375295556677");
    vector<string> languages = {"English"};
    Supporter supporter(1, "Anna", "Support", contact, 5001, 
                       "Support", 40000.0, SupportLevel::STANDARD,
                       languages, 100, 4.5);
    
    // Добавляем новый язык
    supporter.addSupportedLanguage("German");
    const auto& supported = supporter.getSupportedLanguages();
    
    CHECK_EQUAL(2, supported.size());
    CHECK(std::find(supported.begin(), supported.end(), std::string("German")) != supported.end());
    
    // Пытаемся добавить пустой язык
    CHECK_THROW(supporter.addSupportedLanguage(""), std::invalid_argument);
    
    // Пытаемся добавить дубликат
    supporter.addSupportedLanguage("English");
    CHECK_EQUAL(2, supported.size()); // Размер не должен увеличиться
}

TEST(SupporterTest_ResolveTicket) {
    ContactInfo contact("supporter@test.com", "+375295556677");
    vector<string> languages = {"English"};
    Supporter supporter(1, "Anna", "Support", contact, 5001, 
                       "Support", 40000.0, SupportLevel::STANDARD,
                       languages, 100, 4.5);
    
    // Решаем несколько тикетов
    int initialTickets = supporter.getResolvedTickets();
    double initialRating = supporter.getSatisfactionRating();
    
    supporter.resolveTicket();
    supporter.resolveTicket();
    supporter.resolveTicket();
    
    CHECK_EQUAL(initialTickets + 3, supporter.getResolvedTickets());
    CHECK(supporter.getSatisfactionRating() > initialRating);
    CHECK(supporter.getSatisfactionRating() <= 5.0);
}

TEST(SupporterTest_GetSupportLevelString) {
    ContactInfo contact("supporter@test.com", "+375295556677");
    vector<string> languages = {"English"};
    
    Supporter basic(1, "дщч", "срьщ", contact, 5001, "Support", 30000.0, 
                   SupportLevel::BASIC, languages, 50, 3.5);
    Supporter premium(2, "ыглф", "иднфе", contact, 5002, "Support", 50000.0,
                     SupportLevel::PREMIUM, languages, 200, 4.8);
    
    CHECK_EQUAL("Basic", basic.getSupportLevelString());
    CHECK_EQUAL("Premium", premium.getSupportLevelString());
}

TEST(SupporterTest_DisplayInfo) {
    ContactInfo contact("supporter@test.com", "+375295556677");
    vector<string> languages = {"English", "Russian", "German"};
    Supporter supporter(1, "Anna", "Support", contact, 5001, 
                       "Senior Support", 45000.0, SupportLevel::PREMIUM,
                       languages, 150, 4.7);
    
    StdoutRedirect redirect;
    supporter.displayInfo();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Support Level: Premium") != std::string::npos);
    CHECK(output.find("Resolved Tickets: 150") != std::string::npos);
    CHECK(output.find("Satisfaction Rating: 4.70/5") != std::string::npos);
    CHECK(output.find("English") != std::string::npos);
    CHECK(output.find("Russian") != std::string::npos);
    CHECK(output.find("German") != std::string::npos);
}

TEST(SupporterTest_InvalidConstructor_EmptyLanguages) {
    ContactInfo contact("test@test.com", "+375291111111");
    
    // Пустой список языков должен вызывать исключение
    CHECK_THROW(
        Supporter(1, "John", "Doe", contact, 5001, "Support", 30000.0,
                 SupportLevel::BASIC, vector<string>(), 0, 0.0),
        std::invalid_argument
    );
}

TEST(SupportLevel_OperatorOutput) {
    // Тестируем все возможные значения SupportLevel
    
    std::stringstream ss;
    
    // Test BASIC
    ss.str("");
    ss << SupportLevel::BASIC;
    CHECK_EQUAL("Basic", ss.str());
    
    // Test PREMIUM
    ss.str("");
    ss << SupportLevel::PREMIUM;
    CHECK_EQUAL("Premium", ss.str());
    
    ss.str("");
    ss << SupportLevel::STANDARD;
    CHECK_EQUAL("Standard", ss.str());  // Так написано в вашем коде
    
    // Test URGENT
    ss.str("");
    ss << SupportLevel::URGENT;
    CHECK_EQUAL("Urgent", ss.str());
    
    // Test default case (неизвестное значение)
    ss.str("");
    ss << static_cast<SupportLevel>(999);  // Несуществующее значение
    std::string result = ss.str();
    // Проверяем, что содержит "SupportLevel::Unknown"
    CHECK(result.find("SupportLevel::Unknown") != std::string::npos);
    CHECK(result.find("999") != std::string::npos);
}
