#include <UnitTest++/UnitTest++.h>
#include "../Review.hpp"
#include "HELPERFILE.cpp"
#include <sstream>
#include <iostream>

using namespace std;
    
TEST(ReviewTest_Constructor) {
    Review review("John Doe", 5, "Excellent service!");
    
    CHECK_EQUAL("John Doe", review.getAuthor());
    CHECK_EQUAL(5, review.getRating());
    CHECK_EQUAL("Excellent service!", review.getComment());
    CHECK(review.getDate() <= chrono::system_clock::now());
    CHECK(review.isPositive());
}

TEST(ReviewTest_ConstructorMinimal) {
    Review review("Anonymous", 3, "");
    
    CHECK_EQUAL("Anonymous", review.getAuthor());
    CHECK_EQUAL(3, review.getRating());
    CHECK_EQUAL("", review.getComment());
    CHECK(!review.isPositive());  // 3 < 4
}

TEST(ReviewTest_InvalidConstructor) {
    // Пустой автор
    CHECK_THROW(
        Review("", 5, "Good"),
        std::invalid_argument
    );
    
    // Рейтинг меньше 1
    CHECK_THROW(
        Review("Author", 0, "Bad"),
        std::invalid_argument
    );
    
    // Рейтинг больше 5
    CHECK_THROW(
        Review("Author", 6, "Too high"),
        std::invalid_argument
    );
    
    // Отрицательный рейтинг
    CHECK_THROW(
        Review("Author", -1, "Very bad"),
        std::invalid_argument
    );
}

TEST(ReviewTest_IsPositive) {
    // Положительные отзывы (4-5)
    Review positive1("User1", 4, "Good");
    Review positive2("User2", 5, "Excellent");
    
    CHECK(positive1.isPositive());
    CHECK(positive2.isPositive());
    
    // Нейтральные/отрицательные отзывы (1-3)
    Review neutral("User3", 3, "Average");
    Review negative1("User4", 2, "Poor");
    Review negative2("User5", 1, "Terrible");
    
    CHECK(!neutral.isPositive());
    CHECK(!negative1.isPositive());
    CHECK(!negative2.isPositive());
}

TEST(ReviewTest_Display) {
    Review review("Test Author", 4, "Nice experience");
    
    StdoutRedirect redirect;
    review.display();
    string output = redirect.getOutput();
    
    CHECK(output.find("Author: Test Author") != string::npos);
    CHECK(output.find("Rating: 4/5") != string::npos);
    CHECK(output.find("Comment: Nice experience") != string::npos);
    CHECK(output.find("Type: Positive") != string::npos);
}

TEST(ReviewTest_DisplayWithoutComment) {
    Review review("Brief User", 3, "");
    
    StdoutRedirect redirect;
    review.display();
    string output = redirect.getOutput();
    
    CHECK(output.find("Author: Brief User") != string::npos);
    CHECK(output.find("Rating: 3/5") != string::npos);
    CHECK(output.find("Comment: ") == string::npos);  // Не должно быть Comment:
    CHECK(output.find("Type: Needs improvement") != string::npos);
}

TEST(ReviewTest_ValidateRating) {

    Review review("Test", 3, "");
    
    // Проверяем граничные значения
    CHECK(review.validateRating(1));  // Минимум
    CHECK(review.validateRating(5));  // Максимум
    CHECK(review.validateRating(3));  // Среднее
    
    // Проверяем невалидные значения
    CHECK(!review.validateRating(0));
    CHECK(!review.validateRating(6));
    CHECK(!review.validateRating(-1));
    CHECK(!review.validateRating(100));
}