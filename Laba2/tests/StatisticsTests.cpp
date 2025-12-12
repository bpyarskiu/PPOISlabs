#include "../Statistics.hpp"
#include "../Company.hpp"
#include "../Tour.hpp"
#include "../Client.hpp"
#include "../Manager.hpp"  // Используем конкретный класс вместо Employee
#include "../Consultant.hpp"  // Или другой конкретный класс
#include "../Equipment.hpp"
#include "../Complaint.hpp"
#include "../Price.hpp"
#include "../DateRange.hpp"
#include "../ContactInfo.hpp"
#include "../Address.hpp"
#include "HELPERFILE.cpp"
#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <chrono>

using namespace std;

// Вспомогательная функция для создания DateRange для АКТИВНЫХ туров
DateRange createActiveDateRange() {
    auto start = chrono::system_clock::now() - chrono::hours(48); // Через 2 дня
    auto end = start + chrono::hours(168); // +7 дней
    return DateRange(start, end);
}

// Вспомогательная функция для создания DateRange для НЕАКТИВНЫХ туров
DateRange createInactiveDateRange() {
    // Начинался 30 дней назад, закончился 23 дня назад
    auto end = chrono::system_clock::now() - chrono::hours(24 * 23);
    auto start = end - chrono::hours(24 * 7); // Длился 7 дней
    return DateRange(start, end);
}

// Вспомогательная функция для создания Price
Price createPrice(double amount = 1000.0) {
    return Price(amount, "RUB");
}

// Вспомогательная функция для создания ContactInfo
ContactInfo createContactInfo() {
    return ContactInfo("test@example.com", "+375291112233");
}

// Вспомогательная функция для создания Address
Address createAddress() {
    return Address("Main St", "Minsk", "Belarus", "220000");
}

SUITE(StatisticsTests) {

    TEST(Statistics_Constructor) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        Statistics stats(company);
        
        CHECK(true); // Простая проверка создания
    }

    TEST(Statistics_TotalClients) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем и добавляем клиентов с ВАЛИДНЫМИ ID (> 0)
        for (int i = 1; i <= 3; i++) { // Начинаем с 1
            auto client = make_shared<Client>(
                i, "Client" + to_string(i), "Lastname", 
                createContactInfo(), 1000 + i
            );
            company->addClient(client);
        }
        
        Statistics stats(company);
        CHECK_EQUAL(3, stats.getTotalClients());
        
        // Без клиентов
        auto emptyCompany = make_shared<Company>("Empty", 2020, createAddress());
        Statistics stats2(emptyCompany);
        CHECK_EQUAL(0, stats2.getTotalClients());
    }

    TEST(Statistics_TotalEmployees) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем и добавляем сотрудников с ВАЛИДНЫМИ ID (> 0)
        // Используем Manager вместо Employee
        for (int i = 1; i <= 2; i++) {
            vector<string> responsibilities = {"Management"};
            auto manager = make_shared<Manager>(
                i, "Emp" + to_string(i), "Lastname", 
                createContactInfo(), 2000 + i, 
                "Manager", 50000.0,
                responsibilities, 3, 5000.0
            );
            company->addEmployee(manager);
        }
        
        Statistics stats(company);
        CHECK_EQUAL(2, stats.getTotalEmployees());
    }

    TEST(Statistics_EquipmentCount) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Добавляем оборудование
        company->addEquipment(make_shared<Equipment>("Tent", "Good", 5));
        company->addEquipment(make_shared<Equipment>("Backpack", "Good", 10));
        company->addEquipment(make_shared<Equipment>("Sleeping Bag", "Worn", 8));
        
        Statistics stats(company);
        CHECK_EQUAL(3, stats.getEquipmentCount());
    }

    TEST(Statistics_ActiveTours) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем АКТИВНЫЕ туры (даты в будущем)
        auto tour1 = make_shared<Tour>(
            1, "Paris Tour", "Paris", 
            createPrice(1000), createActiveDateRange()  // Активный
        );
        
        auto tour2 = make_shared<Tour>(
            2, "London Tour", "London", 
            createPrice(1200), createActiveDateRange()  // Активный
        );
        
        // Неактивный тур (дата в прошлом)
        auto tour3 = make_shared<Tour>(
            3, "Old Tour", "Rome", 
            createPrice(800), createInactiveDateRange()  // Неактивный
        );
        
        // Активный тур
        auto tour4 = make_shared<Tour>(
            4, "Berlin Tour", "Berlin", 
            createPrice(900), createActiveDateRange()  // Активный
        );
        
        company->addTour(tour1);
        company->addTour(tour2);
        company->addTour(tour3);
        company->addTour(tour4);
        
        Statistics stats(company);
        CHECK_EQUAL(3, stats.getActiveTours()); // tour1, tour2, tour4 активны
        
        // Тест без туров
        auto emptyCompany = make_shared<Company>("Empty", 2020, createAddress());
        Statistics stats2(emptyCompany);
        CHECK_EQUAL(0, stats2.getActiveTours());
    }

    TEST(Statistics_AverageTourRating) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем туры
        auto tour1 = make_shared<Tour>(
            1, "Tour 1", "Paris", 
            createPrice(1000), createActiveDateRange()
        );
        
        auto tour2 = make_shared<Tour>(
            2, "Tour 2", "London", 
            createPrice(1200), createActiveDateRange()
        );
        
        company->addTour(tour1);
        company->addTour(tour2);
        
        Statistics stats(company);
        // Без отзывов средний рейтинг должен быть 0 (или другое значение по умолчанию)
        // Если getAverageRating() возвращает 0 для туров без отзывов:
        CHECK_EQUAL(0.0, stats.getAverageTourRating());
        
        // Тест без туров
        auto emptyCompany = make_shared<Company>("Empty", 2020, createAddress());
        Statistics stats2(emptyCompany);
        CHECK_EQUAL(0.0, stats2.getAverageTourRating());
    }

    TEST(Statistics_ToursByDestination) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем туры с разными направлениями
        company->addTour(make_shared<Tour>(
            1, "Paris Adventure", "Paris", 
            createPrice(1000), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            2, "London Sightseeing", "London", 
            createPrice(1200), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            3, "Paris Romance", "Paris", // Дубликат направления
            createPrice(1500), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            4, "Rome History", "Rome", 
            createPrice(900), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            5, "Paris Luxury", "Paris", // Еще один Париж
            createPrice(2000), createActiveDateRange()
        ));
        
        Statistics stats(company);
        auto destinations = stats.getToursByDestination();
        
        CHECK_EQUAL(3u, destinations.size()); // Paris, London, Rome
        CHECK_EQUAL(3, destinations["Paris"]);
        CHECK_EQUAL(1, destinations["London"]);
        CHECK_EQUAL(1, destinations["Rome"]);
        
        // Проверка несуществующего направления
        CHECK(destinations.find("Tokyo") == destinations.end());
        
        // Тест с пустым списком
        auto emptyCompany = make_shared<Company>("Empty", 2020, createAddress());
        Statistics stats2(emptyCompany);
        auto emptyDestinations = stats2.getToursByDestination();
        CHECK(emptyDestinations.empty());
    }

    TEST(Statistics_ResolvedComplaints) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Добавляем жалобы
        auto complaint1 = make_shared<Complaint>("Bad service", "Service was terrible");
        complaint1->resolve(); // Решаем первую
        
        auto complaint2 = make_shared<Complaint>("Late delivery", "Package arrived late");
        // Оставляем нерешенной
        
        auto complaint3 = make_shared<Complaint>("Wrong item", "Received wrong product");
        complaint3->resolve(); // Решаем третью
        
        auto complaint4 = make_shared<Complaint>("Damaged goods", "Product was damaged");
        // Оставляем нерешенной
        
        auto complaint5 = make_shared<Complaint>("Rude staff", "Staff was rude");
        complaint5->resolve(); // Решаем пятую
        
        company->addComplaint(complaint1);
        company->addComplaint(complaint2);
        company->addComplaint(complaint3);
        company->addComplaint(complaint4);
        company->addComplaint(complaint5);
        
        Statistics stats(company);
        CHECK_EQUAL(3, stats.getResolvedComplaintsCount());
        
        // Все нерешенные
        auto allPendingCompany = make_shared<Company>("Pending", 2020, createAddress());
        for (int i = 1; i <= 5; i++) {
            auto complaint = make_shared<Complaint>("Issue " + to_string(i), "Description");
            allPendingCompany->addComplaint(complaint);
        }
        Statistics stats2(allPendingCompany);
        CHECK_EQUAL(0, stats2.getResolvedComplaintsCount());
        
        // Все решенные
        auto allResolvedCompany = make_shared<Company>("Resolved", 2020, createAddress());
        for (int i = 1; i <= 4; i++) {
            auto complaint = make_shared<Complaint>("Issue " + to_string(i), "Description");
            complaint->resolve();
            allResolvedCompany->addComplaint(complaint);
        }
        Statistics stats3(allResolvedCompany);
        CHECK_EQUAL(4, stats3.getResolvedComplaintsCount());
    }

    TEST(Statistics_DisplaySummary) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Настраиваем тестовые данные с ВАЛИДНЫМИ ID (> 0)
        for (int i = 1; i <= 2; i++) {
            auto client = make_shared<Client>(
                i, "Client" + to_string(i), "Lastname", 
                createContactInfo(), 1000 + i
            );
            company->addClient(client);
        }
        
        for (int i = 1; i <= 1; i++) {
            vector<string> responsibilities = {"Management"};
            auto manager = make_shared<Manager>(
                i, "Emp" + to_string(i), "Lastname", 
                createContactInfo(), 2000 + i, 
                "Manager", 50000.0,
                responsibilities, 2, 3000.0
            );
            company->addEmployee(manager);
        }
        
        company->addTour(make_shared<Tour>(
            1, "Test Tour", "Paris", 
            createPrice(1000), createActiveDateRange()
        ));
        
        company->addEquipment(make_shared<Equipment>("Tent", "Good", 5));
        company->addEquipment(make_shared<Equipment>("Backpack", "Good", 3));
        company->addEquipment(make_shared<Equipment>("Sleeping Bag", "Worn", 2));
        
        // Жалобы
        auto complaint1 = make_shared<Complaint>("Issue 1", "Description 1");
        complaint1->resolve();
        company->addComplaint(complaint1);
        
        auto complaint2 = make_shared<Complaint>("Issue 2", "Description 2");
        company->addComplaint(complaint2);
        
        Statistics stats(company);
        
        StdoutRedirect redirect;
        stats.displaySummary();
        string output = redirect.getOutput();
        
        // Проверяем наличие ключевых строк (не строгое сравнение)
        CHECK(output.find("Total Clients:") != string::npos);
        CHECK(output.find("Total Employees:") != string::npos);
        CHECK(output.find("Active Tours:") != string::npos);
        CHECK(output.find("Total Equipment:") != string::npos);
        CHECK(output.find("Resolved Complaints:") != string::npos);
        CHECK(output.find("=== COMPANY STATISTICS ===") != string::npos);
    }

    TEST(Statistics_DisplayTourStatistics) {
        auto company = make_shared<Company>("Test Company", 2000, createAddress());
        
        // Создаем туры
        company->addTour(make_shared<Tour>(
            1, "Paris Adventure", "Paris", 
            createPrice(1000), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            2, "London Sightseeing", "London", 
            createPrice(1200), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            3, "Paris Romance", "Paris", 
            createPrice(1500), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            4, "Rome History", "Rome", 
            createPrice(900), createActiveDateRange()
        ));
        
        Statistics stats(company);
        
        StdoutRedirect redirect;
        stats.displayTourStatistics();
        string output = redirect.getOutput();
        
        // Более гибкие проверки
        CHECK(output.find("Paris:") != string::npos);
        CHECK(output.find("London:") != string::npos);
        CHECK(output.find("Rome:") != string::npos);
        CHECK(output.find("TOUR DESTINATION STATISTICS") != string::npos);
    }

    TEST(Statistics_DisplayTourStatistics_Empty) {
        auto emptyCompany = make_shared<Company>("Empty", 2020, createAddress());
        Statistics stats(emptyCompany);
        
        StdoutRedirect redirect;
        stats.displayTourStatistics();
        string output = redirect.getOutput();
        
        CHECK(output.find("TOUR DESTINATION STATISTICS") != string::npos);
    }

    TEST(Statistics_IntegrationTest) {
        auto company = make_shared<Company>("Global Tours", 1995, createAddress());
        
        // Клиенты с ВАЛИДНЫМИ ID (> 0)
        for (int i = 1; i <= 5; i++) {
            auto client = make_shared<Client>(
                i, "Client" + to_string(i), "Lastname", 
                createContactInfo(), 1000 + i
            );
            company->addClient(client);
        }
        
        // Сотрудники с ВАЛИДНЫМИ ID (> 0) - используем разные типы
        for (int i = 1; i <= 8; i++) {
            if (i % 2 == 0) {
                // Manager
                vector<string> responsibilities = {"Team Management"};
                auto manager = make_shared<Manager>(
                    i, "Manager" + to_string(i), "Lastname", 
                    createContactInfo(), 2000 + i, 
                    "Manager", 50000.0 + i * 5000,
                    responsibilities, 3 + i, 5000.0
                );
                company->addEmployee(manager);
            } else {
                // Consultant
                vector<string> specializations = {"Travel Planning"};
                auto consultant = make_shared<Consultant>(
                    i, "Consultant" + to_string(i), "Lastname", 
                    createContactInfo(), 3000 + i,
                    "Consultant", 45000.0 + i * 4000,
                    specializations, i * 2, 0.1
                );
                company->addEmployee(consultant);
            }
        }
        
        // Оборудование
        company->addEquipment(make_shared<Equipment>("Tent", "Good", 10));
        company->addEquipment(make_shared<Equipment>("Backpack", "Good", 20));
        company->addEquipment(make_shared<Equipment>("Sleeping Bag", "Worn", 15));
        company->addEquipment(make_shared<Equipment>("Cooking Set", "Good", 8));
        
        // Туры (все активные)
        company->addTour(make_shared<Tour>(
            1, "Paris Deluxe", "Paris", 
            createPrice(1500), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            2, "London Basic", "London", 
            createPrice(1200), createActiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            3, "Paris Express", "Paris", 
            createPrice(1000), createActiveDateRange()
        ));
        
        // Один неактивный тур
        company->addTour(make_shared<Tour>(
            4, "Old Rome Tour", "Rome", 
            createPrice(900), createInactiveDateRange()
        ));
        
        company->addTour(make_shared<Tour>(
            5, "Berlin Adventure", "Berlin", 
            createPrice(1100), createActiveDateRange()
        ));
        
        // Жалобы
        for (int i = 1; i <= 3; i++) {
            auto complaint = make_shared<Complaint>("Issue " + to_string(i), "Description " + to_string(i));
            complaint->resolve();
            company->addComplaint(complaint);
        }
        
        for (int i = 4; i <= 5; i++) {
            auto complaint = make_shared<Complaint>("Issue " + to_string(i), "Description " + to_string(i));
            company->addComplaint(complaint);
        }
        
        Statistics stats(company);
        
        // Проверяем все методы
        CHECK_EQUAL(5, stats.getTotalClients());
        CHECK_EQUAL(8, stats.getTotalEmployees());
        CHECK_EQUAL(4, stats.getEquipmentCount());
        CHECK_EQUAL(4, stats.getActiveTours()); // Все кроме прошедшего
        
        CHECK_EQUAL(3, stats.getResolvedComplaintsCount());
        
        auto destinations = stats.getToursByDestination();
        CHECK_EQUAL(4u, destinations.size()); // Paris, London, Rome, Berlin
        CHECK_EQUAL(2, destinations["Paris"]);
        CHECK_EQUAL(1, destinations["London"]);
        CHECK_EQUAL(1, destinations["Rome"]);
        CHECK_EQUAL(1, destinations["Berlin"]);
    }
}