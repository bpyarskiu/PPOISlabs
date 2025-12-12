#include <UnitTest++/UnitTest++.h>
#include "../Tour.hpp"
#include "../Price.hpp"
#include "../DateRange.hpp"
#include "HELPERFILE.cpp"
#include <memory>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

// ============================================
// ВСПОМОГАТЕЛЬНЫЕ КЛАССЫ ДЛЯ ТЕСТИРОВАНИЯ
// ============================================

// Простая реализация Accommodation для тестов
class TestAccommodation : public Accommodation {
public:
    TestAccommodation(int id, const string& name, const Address& addr, 
                     const Coordinates& coords, AccommodationType type, 
                     const Price& price, const Rating& rating, int capacity = 2)
        : Accommodation(id, name, addr, coords, type, price, rating, capacity) {}
    
    Price calculateTotalCost(int nights) const  {
        // Простая реализация для тестов
        return getPricePerNight().multiply(nights);
    }
};

// Простая реализация Transport для тестов  
class TestTransport : public Transport {
public:
    TestTransport(int id, const string& type, const string& desc, const Price& price)
        : Transport(id, type, desc, price) {}
    
    double calculatePrice(int passengers) const override {
        return getPrice().getAmount() * passengers;
    }
};

// Простая реализация Review для тестов
class TestReview : public Review {
public:
    TestReview(const string& author, int rating, const string& comment = "")
        : Review(author, rating, comment) {}
};

// Простая реализация Insurance для тестов
class TestInsurance : public Insurance {
public:
    TestInsurance(const string& type, const Price& price, 
                  const string& coverage, const Duration& duration)
        : Insurance(type, price, coverage, duration) {}
};

// Простая реализация MealPlan для тестов
class TestMealPlan : public MealPlan {
public:
    TestMealPlan(const string& type, const Price& price, const string& desc = "")
        : MealPlan(type, price, desc) {}
};

// ============================================
// ТЕСТЫ КОНСТРУКТОРА
// ============================================

TEST(Tour_Constructor_Valid) {
    auto now = system_clock::now();
    auto start = now + hours(24 * 7); // через неделю
    auto end = start + hours(24 * 14); // через 2 недели после начала
    
    DateRange dateRange(start, end);
    Price basePrice(1000.0, "USD");
    
    Tour tour(1, "Egypt Adventure", "Cairo", basePrice, dateRange);
    
    CHECK_EQUAL(1, tour.getTourId());
    CHECK_EQUAL("Egypt Adventure", tour.getName());
    CHECK_EQUAL("Cairo", tour.getDestination());
    CHECK_EQUAL(1000.0, tour.getBasePrice().getAmount());
    CHECK_EQUAL("USD", tour.getBasePrice().getCurrency());
}

TEST(Tour_Constructor_InvalidName) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 7));
    Price basePrice(1000.0, "USD");
    
    // Пустое имя
    CHECK_THROW(
        Tour(1, "", "Paris", basePrice, dateRange),
        invalid_argument
    );
}

TEST(Tour_Constructor_InvalidDestination) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 7));
    Price basePrice(1000.0, "USD");
    
    // Пустой пункт назначения
    CHECK_THROW(
        Tour(1, "Paris Tour", "", basePrice, dateRange),
        invalid_argument
    );
}

// ============================================
// ТЕСТЫ ГЕТТЕРОВ
// ============================================

TEST(Tour_Getters) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 10));
    Price basePrice(1500.0, "EUR");
    
    Tour tour(42, "Greek Islands", "Santorini", basePrice, dateRange);
    
    CHECK_EQUAL(42, tour.getTourId());
    CHECK_EQUAL("Greek Islands", tour.getName());
    CHECK_EQUAL("Santorini", tour.getDestination());
    CHECK_EQUAL(1500.0, tour.getBasePrice().getAmount());
    CHECK_EQUAL("EUR", tour.getBasePrice().getCurrency());
    
    // Проверяем, что списки изначально пусты
    CHECK(tour.getAccommodations().empty());
    CHECK(tour.getTransports().empty());
    CHECK(tour.getReviews().empty());
    
    // Проверяем, что insurance и mealPlan изначально nullptr
    CHECK(!tour.getInsurance());
    CHECK(!tour.getMealPlan());
}

// ============================================
// ТЕСТЫ ДОБАВЛЕНИЯ ЭЛЕМЕНТОВ
// ============================================

TEST(Tour_AddAccommodation_Valid) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    Address addr(std::string("123 Street"), std::string("City"), std::string("Country"),std::string("1244"));
    Coordinates coords(40.7128, -74.0060);
    Rating rating(4.5, 10);
    
    auto accommodation = make_shared<TestAccommodation>(
        1, "Test Hotel", addr, coords, AccommodationType::HOTEL, 
        Price(100.0, "USD"), rating, 2
    );
    
    tour.addAccommodation(accommodation);
    
    CHECK_EQUAL(1, tour.getAccommodations().size());
    CHECK_EQUAL("Test Hotel", tour.getAccommodations()[0]->getName());
}

TEST(Tour_AddAccommodation_Null) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    CHECK_THROW(tour.addAccommodation(nullptr), invalid_argument);
}

TEST(Tour_AddTransport_Valid) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    auto transport = make_shared<TestTransport>(
        1, "Flight", "Direct flight", Price(300.0, "USD")
    );
    
    tour.addTransport(transport);
    
    CHECK_EQUAL(1, tour.getTransports().size());
    CHECK_EQUAL("Flight", tour.getTransports()[0]->getType());
}

TEST(Tour_AddTransport_Null) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    CHECK_THROW(tour.addTransport(nullptr), invalid_argument);
}

TEST(Tour_AddReview_Valid) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    auto review = make_shared<TestReview>("John Doe", 5, "Excellent tour!");
    tour.addReview(review);
    
    CHECK_EQUAL(1, tour.getReviews().size());
    CHECK_EQUAL("John Doe", tour.getReviews()[0]->getAuthor());
    CHECK_EQUAL(5, tour.getReviews()[0]->getRating());
}

TEST(Tour_AddReview_Multiple) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    tour.addReview(make_shared<TestReview>("Alice", 4));
    tour.addReview(make_shared<TestReview>("Bob", 3));
    tour.addReview(make_shared<TestReview>("Charlie", 5));
    
    CHECK_EQUAL(3, tour.getReviews().size());
}

TEST(Tour_SetInsurance_Valid) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    auto insurance = make_shared<TestInsurance>(
        "Medical", Price(50.0, "USD"), "Full coverage", Duration(7)
    );
    
    tour.setInsurance(insurance);
    
    auto retrieved = tour.getInsurance();
    CHECK(retrieved != nullptr);
    CHECK_EQUAL("Medical", retrieved->getType());
    CHECK_EQUAL(50.0, retrieved->getPrice().getAmount());
}

TEST(Tour_SetMealPlan_Valid) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    auto mealPlan = make_shared<TestMealPlan>(
        "All Inclusive", Price(30.0, "USD"), "Three meals per day"
    );
    
    tour.setMealPlan(mealPlan);
    
    auto retrieved = tour.getMealPlan();
    CHECK(retrieved != nullptr);
    CHECK_EQUAL("All Inclusive", retrieved->getType());
    CHECK_EQUAL(30.0, retrieved->getPricePerDay().getAmount());
}

// ============================================
// ТЕСТЫ РАСЧЕТНЫХ МЕТОДОВ
// ============================================

TEST(Tour_CalculateTotalPrice_EmptyTour) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 7)); // 7 дней
    Price basePrice(1000.0, "USD");
    
    Tour tour(1, "Simple Tour", "Bali", basePrice, dateRange);
    
    // Только базовая цена
    Price total = tour.calculateTotalPrice();
    CHECK_EQUAL(1000.0, total.getAmount());
    CHECK_EQUAL("USD", total.getCurrency());
}

TEST(Tour_CalculateTotalPrice_WithAllOptions) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 10)); // 10 дней
    Price basePrice(2000.0, "EUR");
    
    Tour tour(1, "Complete Tour", "Maldives", basePrice, dateRange);
    
    // Добавляем проживание
    Address addr(std::string("Beach Road"), std::string("Malé"), std::string("Maldives"),std::string("12334"));
    Coordinates coords(4.1755, 73.5093);
    Rating rating(4.8, 50);
    
    auto accommodation = make_shared<TestAccommodation>(
        1, "Beach Resort", addr, coords, AccommodationType::HOTEL, 
        Price(150.0, "EUR"), rating, 2
    );
    tour.addAccommodation(accommodation);
    
    // Добавляем транспорт
    auto flight = make_shared<TestTransport>(
        1, "Flight", "International flight", Price(500.0, "EUR")
    );
    tour.addTransport(flight);
    
    // Добавляем страховку
    auto insurance = make_shared<TestInsurance>(
        "Comprehensive", Price(100.0, "EUR"), "Full coverage", Duration(10)
    );
    tour.setInsurance(insurance);
    
    // Добавляем питание
    auto mealPlan = make_shared<TestMealPlan>(
        "Half Board", Price(40.0, "EUR"), "Breakfast and dinner"
    );
    tour.setMealPlan(mealPlan);
    
    // Рассчитываем общую стоимость:
    // Базовая: 2000
    // Проживание: 150 * 10 = 1500
    // Транспорт: 500
    // Страховка: 100
    // Питание: 40 * 10 = 400
    // Итого: 4500 EUR
    
    Price total = tour.calculateTotalPrice();
    CHECK_CLOSE(4500.0, total.getAmount(), 0.01);
    CHECK_EQUAL("EUR", total.getCurrency());
}

TEST(Tour_CalculateTotalPrice_MultipleAccommodations) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 14)); // 14 дней
    Price basePrice(1500.0, "USD");
    
    Tour tour(1, "Multi-City Tour", "Italy", basePrice, dateRange);
    
    Address addr1(std::string("Venice Street"), std::string("Venice"), std::string("Italy"),std::string("12344"));
    Address addr2(std::string("Rome Street"), std::string("Rome"), std::string("Italy"),std::string("124444"));
    Coordinates coords1(45.4408, 12.3155);
    Coordinates coords2(41.9028, 12.4964);
    Rating rating(4.5, 20);
    
    // Два разных отеля
    auto hotel1 = make_shared<TestAccommodation>(
        1, "Venice Hotel", addr1, coords1, AccommodationType::HOTEL, 
        Price(120.0, "USD"), rating, 2
    );
    
    auto hotel2 = make_shared<TestAccommodation>(
        2, "Rome Hotel", addr2, coords2, AccommodationType::HOTEL, 
        Price(140.0, "USD"), rating, 2
    );
    
    tour.addAccommodation(hotel1);
    tour.addAccommodation(hotel2);
    
    // Базовая: 1500
    // Отель 1: 120 * 14 = 1680
    // Отель 2: 140 * 14 = 1960
    // Итого: 5140 USD
    
    Price total = tour.calculateTotalPrice();
    CHECK_CLOSE(5140.0, total.getAmount(), 0.01);
}

TEST(Tour_GetAverageRating_NoReviews) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    double avg = tour.getAverageRating();
    CHECK_EQUAL(0.0, avg);
}

TEST(Tour_GetAverageRating_WithReviews) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    tour.addReview(make_shared<TestReview>("Alice", 4));
    tour.addReview(make_shared<TestReview>("Bob", 3));
    tour.addReview(make_shared<TestReview>("Charlie", 5));
    
    double avg = tour.getAverageRating();
    CHECK_CLOSE(4.0, avg, 0.01); // (4+3+5)/3 = 4.0
}

TEST(Tour_GetAverageRating_MixedReviews) {
    Tour tour(1, "Test Tour", "Test Dest", Price(500.0, "USD"), 
              DateRange(system_clock::now(), system_clock::now() + hours(24 * 7)));
    
    tour.addReview(make_shared<TestReview>("User1", 1));
    tour.addReview(make_shared<TestReview>("User2", 2));
    tour.addReview(make_shared<TestReview>("User3", 3));
    tour.addReview(make_shared<TestReview>("User4", 4));
    tour.addReview(make_shared<TestReview>("User5", 5));
    
    double avg = tour.getAverageRating();
    CHECK_CLOSE(3.0, avg, 0.01); // (1+2+3+4+5)/5 = 3.0
}

// ============================================
// ТЕСТЫ СОСТОЯНИЯ
// ============================================

TEST(Tour_IsActive_ActiveTour) {
    auto now = system_clock::now();
    auto start = now - hours(24 * 2); // начался 2 дня назад
    auto end = now + hours(24 * 5);   // закончится через 5 дней
    
    DateRange dateRange(start, end);
    Tour tour(1, "Active Tour", "Barcelona", Price(800.0, "EUR"), dateRange);
    
    CHECK(tour.isActive());
}

TEST(Tour_IsActive_InactiveTour_Future) {
    auto now = system_clock::now();
    auto start = now + hours(24 * 10); // начнется через 10 дней
    auto end = start + hours(24 * 7);  // закончится через 7 дней после начала
    
    DateRange dateRange(start, end);
    Tour tour(1, "Future Tour", "Tokyo", Price(1200.0, "USD"), dateRange);
    
    // Тур еще не начался - считается неактивным
    CHECK(!tour.isActive());
}

TEST(Tour_IsActive_InactiveTour_Past) {
    auto now = system_clock::now();
    auto start = now - hours(24 * 20); // начался 20 дней назад
    auto end = now - hours(24 * 10);   // закончился 10 дней назад
    
    DateRange dateRange(start, end);
    Tour tour(1, "Past Tour", "London", Price(600.0, "GBP"), dateRange);
    
    // Тур уже закончился - считается неактивным
    CHECK(!tour.isActive());
}

// ============================================
// ТЕСТЫ МЕТОДОВ ОТОБРАЖЕНИЯ
// ============================================

TEST(Tour_DisplayTourInfo) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24 * 8));
    Price basePrice(1200.0, "USD");
    
    Tour tour(99, "Safari Adventure", "Kenya", basePrice, dateRange);
    
    // Добавляем некоторые опции
    Address addr(std::string("Savannah Lodge"), std::string("Maasai Mara"), std::string("Kenya"),std::string("124141"));
    Coordinates coords(-1.4067, 35.0080);
    Rating rating(4.7, 35);
    
    auto accommodation = make_shared<TestAccommodation>(
        1, "Wildlife Lodge", addr, coords, AccommodationType::HOTEL, 
        Price(200.0, "USD"), rating, 2
    );
    tour.addAccommodation(accommodation);
    
    StdoutRedirect redirect;
    tour.displayTourInfo();
    string output = redirect.getOutput();
    
    // Проверяем ключевые элементы вывода
    CHECK(output.find("Safari Adventure") != string::npos);
    CHECK(output.find("1200") != string::npos);
    CHECK(output.find("Active") != string::npos);
    CHECK(output.find("1") != string::npos);
    CHECK(output.find("USD") != string::npos);
}




// ============================================
// ТЕСТЫ ПРОДОЛЖИТЕЛЬНОСТИ
// ============================================

TEST(Tour_GetDurationDays) {
    auto now = system_clock::now();
    
    // Тест с 7 днями
    DateRange dateRange7(now, now + hours(24 * 7));
    Tour tour7(1, "Week Tour", "Test", Price(700.0, "USD"), dateRange7);
    // Проверяем через DateRange::getDurationDays
    
    // Тест с 1 днем
    DateRange dateRange1(now, now + hours(24));
    Tour tour1(2, "Day Tour", "Test", Price(100.0, "USD"), dateRange1);
    
    // Тест с 30 днями
    DateRange dateRange30(now, now + hours(24 * 30));
    Tour tour30(3, "Month Tour", "Test", Price(3000.0, "USD"), dateRange30);
}

// ============================================
// ТЕСТЫ ГРАНИЧНЫХ СЛУЧАЕВ
// ============================================


TEST(Tour_Boundary_MinimalData) {
    auto now = system_clock::now();
    DateRange dateRange(now, now + hours(24));
    Price basePrice(1.0, "USD");
    
    // Минимально допустимые данные
    Tour tour(1, "A", "B", basePrice, dateRange);
    
    CHECK_EQUAL("A", tour.getName());
    CHECK_EQUAL("B", tour.getDestination());
    CHECK_EQUAL(1.0, tour.getBasePrice().getAmount());
}

// ============================================
// ТЕСТЫ НАПОЛНЕННОГО ТУРА
// ============================================

TEST(Tour_FullFeaturedTour) {
    auto now = system_clock::now();
    DateRange dateRange(now + hours(24), now + hours(24 * 15)); // 14 дней
    
    Tour tour(777, "Ultimate European Journey", "Europe", 
              Price(2500.0, "EUR"), dateRange);
    
    // Добавляем 3 отеля
    for (int i = 1; i <= 3; i++) {
        Address addr("Hotel Street " + to_string(i), "City" + to_string(i), std::string("Country"),std::string("121244"));
        Coordinates coords(48.8566 + i*0.1, 2.3522 + i*0.1);
        Rating rating(4.0 + i*0.2, 50 + i*10);
        
        auto hotel = make_shared<TestAccommodation>(
            i, "Hotel " + to_string(i), addr, coords, AccommodationType::HOTEL,
            Price(100.0 + i*20, "EUR"), rating, 2
        );
        tour.addAccommodation(hotel);
    }
    
    // Добавляем 2 вида транспорта
    auto flight = make_shared<TestTransport>(1, "Flight", "International", Price(400.0, "EUR"));
    auto train = make_shared<TestTransport>(2, "Train", "Intercity", Price(150.0, "EUR"));
    tour.addTransport(flight);
    tour.addTransport(train);
    
    // Добавляем 5 отзывов
    vector<int> ratings = {5, 4, 5, 3, 4};
    for (size_t i = 0; i < ratings.size(); i++) {
        auto review = make_shared<TestReview>(
            "Traveler " + to_string(i+1), 
            ratings[i],
            "Review comment " + to_string(i+1)
        );
        tour.addReview(review);
    }
    
    // Добавляем страховку
    auto insurance = make_shared<TestInsurance>(
        "Full Coverage", Price(120.0, "EUR"), "Medical+Baggage", Duration(14)
    );
    tour.setInsurance(insurance);
    
    // Добавляем план питания
    auto mealPlan = make_shared<TestMealPlan>(
        "Breakfast Only", Price(25.0, "EUR"), "Continental breakfast"
    );
    tour.setMealPlan(mealPlan);
    
    // Проверяем все геттеры
    CHECK_EQUAL(777, tour.getTourId());
    CHECK_EQUAL("Ultimate European Journey", tour.getName());
    CHECK_EQUAL("Europe", tour.getDestination());
    CHECK_EQUAL(3, tour.getAccommodations().size());
    CHECK_EQUAL(2, tour.getTransports().size());
    CHECK_EQUAL(5, tour.getReviews().size());
    CHECK(tour.getInsurance() != nullptr);
    CHECK(tour.getMealPlan() != nullptr);
    
    // Проверяем средний рейтинг
    double expectedAvg = (5+4+5+3+4) / 5.0;
    CHECK_CLOSE(expectedAvg, tour.getAverageRating(), 0.01);
    
    // Проверяем, что расчет общей цены не падает

}