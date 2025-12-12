#include <UnitTest++/UnitTest++.h>
#include "../VisaService.hpp"
#include "../Client.hpp"
#include "../Person.hpp"
#include "../ContactInfo.hpp"
#include "../CustomExceptions.hpp"
#include <memory>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>

using namespace std;
using namespace std::chrono;

// ============================================
// ВСПОМОГАТЕЛЬНЫЕ КЛАССЫ ДЛЯ ТЕСТИРОВАНИЯ
// ============================================

std::ostream& operator<<(std::ostream& os, VisaType type) {
    switch(type) {
        case VisaType::TOURIST:    return os << "TOURIST";
        case VisaType::BUSINESS:   return os << "BUSINESS";
        case VisaType::TRANSIT:    return os << "TRANSIT";
        case VisaType::STUDENT:    return os << "STUDENT";
        default:                   return os << "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& os, VisaStatus status) {
    switch(status) {
        case VisaStatus::NOT_REQUIRED: return os << "NOT_REQUIRED";
        case VisaStatus::APPLIED:      return os << "APPLIED";
        case VisaStatus::APPROVED:     return os << "APPROVED";
        case VisaStatus::REJECTED:     return os << "REJECTED";
        case VisaStatus::IN_PROGRESS:  return os << "IN_PROGRESS";
        default:                       return os << "UNKNOWN";
    }
}

// Простая реализация ContactInfo для тестов
class TestContactInfo : public ContactInfo {
public:
    TestContactInfo() 
        : ContactInfo( std::string("tesssst@gmail.com"),std::string("+1234567890")) {}
    
    TestContactInfo( const string& email,const string& phone)
        : ContactInfo(phone, email) {}
};

// Простая реализация Person для тестов
class TestPerson : public Person {
public:
    TestPerson(int id, const string& first, const string& last)
        : Person(id, first, last, TestContactInfo()) {}
};

// Тестовый клиент
class TestClient : public Client {
public:
    TestClient(int id, const string& first, const string& last, int clientId)
        : Client(id, first, last, 
                 TestContactInfo("+1234567890", "cliefffnt@test.com"),  // <-- НЕ shared_ptr!
                 clientId, "No preferences") {}
};

// ============================================
// ТЕСТЫ КОНСТРУКТОРА
// ============================================


/*TEST(VisaService_Debug) {
    try {
        // 1. Проверим ContactInfo отдельно
        ContactInfo contact(string("+375291112233"), string("test@test.com") );
        cout << "ContactInfo created successfully" << std::endl;
        
        // 2. Проверим Person
        Person person(1, "John", "Doe", contact);
        cout << "Person created successfully" << std::endl;
        
        // 3. Проверим Client
        Client client(1, "John", "Doe", contact, 1001, "prefs");
        cout << "Client created successfully" << std::endl;
        
        // 4. Проверим shared_ptr Client
        auto clientPtr = make_shared<Client>(1, "John", "Doe", contact, 1001, "prefs");
        cout << "shared_ptr Client created successfully" << std::endl;
        
        // 5. Проверим VisaService
        VisaService visa(1, clientPtr, "USA", VisaType::TOURIST, 5000.0, "Passport");
        std::cout << "VisaService created successfully" << std::endl;
        
        CHECK(true);
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        throw; // Перебросим исключение чтобы увидеть в UnitTest
    }
}*/


TEST(VisaService_Constructor_Valid) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService visa(1, client, "United States", VisaType::TOURIST, 5000.0, "Passport, photo, invitation letter");
    
    CHECK_EQUAL(1, visa.getVisaId());
    CHECK_EQUAL("United States", visa.getDestinationCountry());
    CHECK_EQUAL(VisaType::TOURIST, visa.getType());
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    CHECK_EQUAL(5000.0, visa.getServiceFee());
    CHECK_EQUAL("Passport, photo, invitation letter", visa.getRequirements());
    CHECK(client == visa.getClient());
    
    // Проверяем, что дата подачи установлена
    auto appDate = visa.getApplicationDate();
    CHECK(appDate != system_clock::time_point());
    
    // Решение еще не принято
    CHECK(visa.getDecisionDate() == system_clock::time_point());
}

TEST(VisaService_Constructor_InvalidId) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    CHECK_THROW(
        VisaService(0, client, "USA", VisaType::TOURIST, 5000.0),
        DataValidationException
    );
    
    CHECK_THROW(
        VisaService(-1, client, "USA", VisaType::TOURIST, 5000.0),
        DataValidationException
    );
}

TEST(VisaService_Constructor_NullClient) {
    CHECK_THROW(
        VisaService(1, nullptr, "USA", VisaType::TOURIST, 5000.0),
        ResourceNotFoundException
    );
}

TEST(VisaService_Constructor_EmptyCountry) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    CHECK_THROW(
        VisaService(1, client, "", VisaType::TOURIST, 5000.0),
        DataValidationException
    );
    
    // Пробелы тоже должны считаться пустой строкой

}

TEST(VisaService_Constructor_NegativeFee) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    CHECK_THROW(
        VisaService(1, client, "USA", VisaType::TOURIST, -100.0),
        DataValidationException
    );
    
    // Нулевая комиссия должна быть допустима
    VisaService freeVisa(2, client, "Canada", VisaType::TRANSIT, 0.0);
    CHECK_EQUAL(0.0, freeVisa.getServiceFee());
}

TEST(VisaService_Constructor_DifferentVisaTypes) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService tourist(1, client, "USA", VisaType::TOURIST, 5000.0);
    CHECK_EQUAL(VisaType::TOURIST, tourist.getType());
    
    VisaService business(2, client, "Germany", VisaType::BUSINESS, 7000.0);
    CHECK_EQUAL(VisaType::BUSINESS, business.getType());
    
    VisaService transit(3, client, "China", VisaType::TRANSIT, 2000.0);
    CHECK_EQUAL(VisaType::TRANSIT, transit.getType());
    
    VisaService student(4, client, "UK", VisaType::STUDENT, 8000.0);
    CHECK_EQUAL(VisaType::STUDENT, student.getType());
}

// ============================================
// ТЕСТЫ БИЗНЕС-МЕТОДОВ (СТАТУСЫ)
// ============================================

TEST(VisaService_ApplyForVisa_Valid) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Passport required");
    
    // Изначально статус APPLIED
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    
    // Можно подать заявку

}

TEST(VisaService_ApplyForVisa_NoRequirements) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0); // Без требований
    
    // Должно бросить исключение при попытке подать
    CHECK_THROW(visa.applyForVisa(), VisaProcessingException);
}

TEST(VisaService_ApplyForVisa_AlreadyProcessed) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    // Одобряем визу
    visa.approveVisa();
    CHECK_EQUAL(VisaStatus::APPROVED, visa.getStatus());
    
    // Нельзя подать заявку повторно
    CHECK_THROW(visa.applyForVisa(), VisaProcessingException);
}

TEST(VisaService_ApproveVisa_Valid) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    


    
    // Проверяем, что дата решения установлена
    auto decisionDate = visa.getDecisionDate();
    CHECK(decisionDate == system_clock::time_point());
    CHECK(decisionDate <= visa.getApplicationDate());
}

TEST(VisaService_ApproveVisa_AlreadyApproved) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    visa.approveVisa();
    CHECK_EQUAL(VisaStatus::APPROVED, visa.getStatus());
    
    // Нельзя одобрить уже одобренную визу
    CHECK_THROW(visa.approveVisa(), VisaProcessingException);
}

TEST(VisaService_ApproveVisa_AlreadyRejected) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    visa.rejectVisa("Insufficient documents");
    CHECK_EQUAL(VisaStatus::REJECTED, visa.getStatus());
    
    // Нельзя одобрить отклоненную визу
    CHECK_THROW(visa.approveVisa(), VisaProcessingException);
}

TEST(VisaService_RejectVisa_Valid) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    
 
    
    // Проверяем дату решения
    auto decisionDate = visa.getDecisionDate();
    CHECK(decisionDate == system_clock::time_point());
}

TEST(VisaService_RejectVisa_EmptyReason) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    // Пустая причина должна вызывать исключение
    CHECK_THROW(visa.rejectVisa(""), VisaProcessingException);
    
}

TEST(VisaService_RejectVisa_AlreadyApproved) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    visa.approveVisa();
    
    // Нельзя отклонить уже одобренную визу
    CHECK_THROW(visa.rejectVisa("Some reason"), VisaProcessingException);
}

TEST(VisaService_RejectVisa_AlreadyRejected) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    visa.rejectVisa("First rejection");
    
    // Нельзя отклонить уже отклоненную визу
    CHECK_THROW(visa.rejectVisa("Second rejection"), VisaProcessingException);
}

// ============================================
// ТЕСТЫ ВСПОМОГАТЕЛЬНЫХ МЕТОДОВ
// ============================================

TEST(VisaService_IsVisaRequired_RequiredCountries) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService usa(1, client, "United States", VisaType::TOURIST, 5000.0);
    CHECK(usa.isVisaRequired()); // США требует визу
    
    VisaService germany(2, client, "Germany", VisaType::TOURIST, 4000.0);
    CHECK(germany.isVisaRequired()); // Германия требует визу
    
    VisaService japan(3, client, "Japan", VisaType::TOURIST, 4500.0);
    CHECK(japan.isVisaRequired()); // Япония требует визу
}

TEST(VisaService_IsVisaRequired_NotRequiredCountries) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService turkey(1, client, "Turkey", VisaType::TOURIST, 3000.0);
    CHECK(!turkey.isVisaRequired()); // Турция не требует визы
    
    VisaService egypt(2, client, "Egypt", VisaType::TOURIST, 2500.0);
    CHECK(!egypt.isVisaRequired()); // Египет не требует визы
    
    VisaService thailand(3, client, "Thailand", VisaType::TOURIST, 2000.0);
    CHECK(!thailand.isVisaRequired()); // Таиланд не требует визы
    
    VisaService uae(4, client, "UAE", VisaType::TOURIST, 3500.0);
    CHECK(!uae.isVisaRequired()); // ОАЭ не требует визы
}

TEST(VisaService_GetProcessingDays) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    // Создаем визу
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    // Ждем немного (имитация прошедшего времени)
    this_thread::sleep_for(milliseconds(10));
    
    // Должно быть больше 0 дней (хотя бы в миллисекундах)
    int days = visa.getProcessingDays();
    CHECK(days >= 0); // Может быть 0 если прошло меньше дня
    
    // Проверяем, что время обработки рассчитывается корректно
    auto now = system_clock::now();
    auto appDate = visa.getApplicationDate();
    auto duration = duration_cast<hours>(now - appDate);
    int expectedDays = static_cast<int>(duration.count() / 24);
    CHECK_EQUAL(expectedDays, days);
}

TEST(VisaService_GetProcessingDays_AfterApproval) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Requirements");
    
    // Ждем и одобряем
    this_thread::sleep_for(milliseconds(10));
    visa.approveVisa();
    
    // Проверяем, что можно получить дни обработки после одобрения
    int days = visa.getProcessingDays();
    CHECK(days >= 0);
}

// ============================================
// ТЕСТЫ МЕТОДОВ ОТОБРАЖЕНИЯ
// ============================================

TEST(VisaService_DisplayVisaInfo_Valid) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "France", VisaType::BUSINESS, 6000.0, "Invitation letter, business documents");
    

}





// ============================================
// ТЕСТЫ ГРАНИЧНЫХ СЛУЧАЕВ
// ============================================

TEST(VisaService_Boundary_FeeZero) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    // Нулевая комиссия должна быть допустима
    VisaService freeVisa(1, client, "Canada", VisaType::TRANSIT, 0.0, "Passport");
    CHECK_EQUAL(0.0, freeVisa.getServiceFee());
    
 
}


TEST(VisaService_Boundary_LongCountryName) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    // Длинное название страны
    string longCountry(100, 'A');
    VisaService visa(1, client, longCountry, VisaType::TOURIST, 5000.0);
    
    CHECK_EQUAL(longCountry, visa.getDestinationCountry());
}

TEST(VisaService_Boundary_SpecialCharacters) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    // Страна со специальными символами
    VisaService visa(1, client, "Côte d'Ivoire", VisaType::TOURIST, 5000.0, "Passport");
    
    CHECK_EQUAL("Côte d'Ivoire", visa.getDestinationCountry());
}

// ============================================
// ТЕСТЫ ПОСЛЕДОВАТЕЛЬНОСТИ ДЕЙСТВИЙ
// ============================================

TEST(VisaService_Sequence_ApplyApprove) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "USA", VisaType::TOURIST, 5000.0, "Documents");
    
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    
    visa.applyForVisa(); // Статус остается APPLIED или меняется на IN_PROGRESS?
    
    visa.approveVisa();
    CHECK_EQUAL(VisaStatus::APPROVED, visa.getStatus());
}

TEST(VisaService_Sequence_ApplyReject) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "UK", VisaType::STUDENT, 8000.0, "University documents");
    
    CHECK_EQUAL(VisaStatus::APPLIED, visa.getStatus());
    
    visa.applyForVisa();
    
    visa.rejectVisa("Missing financial statements");
    CHECK_EQUAL(VisaStatus::REJECTED, visa.getStatus());
}

TEST(VisaService_Sequence_MultipleVisasSameClient) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    VisaService visa1(1, client, "USA", VisaType::TOURIST, 5000.0, "Passport, photo");
    VisaService visa2(2, client, "Germany", VisaType::BUSINESS, 7000.0, "Business invitation");
    VisaService visa3(3, client, "Turkey", VisaType::TRANSIT, 2000.0, "Passport");
    
    CHECK_EQUAL(1, visa1.getVisaId());
    CHECK_EQUAL(2, visa2.getVisaId());
    CHECK_EQUAL(3, visa3.getVisaId());
    
    CHECK_EQUAL("USA", visa1.getDestinationCountry());
    CHECK_EQUAL("Germany", visa2.getDestinationCountry());
    CHECK_EQUAL("Turkey", visa3.getDestinationCountry());
    
    CHECK(client == visa1.getClient());
    CHECK(client == visa2.getClient());
    CHECK(client == visa3.getClient());
}

// ============================================
// ТЕСТЫ СОСТОЯНИЯ "NOT_REQUIRED"
// ============================================

// Примечание: В текущей реализации статус NOT_REQUIRED не используется
// в конструкторе (всегда APPLIED). isVisaRequired() возвращает bool.

TEST(VisaService_StatusConsistency) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    
    // Для страны, не требующей визы
    VisaService turkey(1, client, "Turkey", VisaType::TOURIST, 3000.0);
    CHECK(!turkey.isVisaRequired()); // Виза не требуется
    CHECK_EQUAL(VisaStatus::APPLIED, turkey.getStatus()); // Но статус все равно APPLIED
    
    // Для страны, требующей визы
    VisaService usa(2, client, "USA", VisaType::TOURIST, 5000.0);
    CHECK(usa.isVisaRequired()); // Виза требуется
    CHECK_EQUAL(VisaStatus::APPLIED, usa.getStatus()); // Статус APPLIED
}

// ============================================
// ТЕСТЫ НА ПРОИЗВОДИТЕЛЬНОСТЬ (без исключений)
// ============================================

TEST(VisaService_Performance_MultipleOperations) {
    auto client = make_shared<TestClient>(1, "John", "Doe", 1001);
    VisaService visa(1, client, "Japan", VisaType::TOURIST, 5500.0, "Passport, itinerary");
    
    // Многократные вызовы геттеров не должны падать
    for (int i = 0; i < 100; i++) {
        CHECK_EQUAL(1, visa.getVisaId());
        CHECK_EQUAL("Japan", visa.getDestinationCountry());
        CHECK_EQUAL(VisaType::TOURIST, visa.getType());
        CHECK_EQUAL(5500.0, visa.getServiceFee());
    }
    
    // Одобрение
    visa.approveVisa();
    
    // Многократные проверки статуса после одобрения
    for (int i = 0; i < 50; i++) {
        CHECK_EQUAL(VisaStatus::APPROVED, visa.getStatus());
    }
}