#include <UnitTest++/UnitTest++.h>
#include "../Discount.hpp"
#include "../Rating.hpp"
#include "../Duration.hpp"

SUITE(DiscountTests) {
    TEST(ValidDiscountCreation) {
        Discount discount(15.0, "Test discount");
        
        CHECK_EQUAL(15.0, discount.getPercentage());
        CHECK_EQUAL("Test discount", discount.getDescription());
    }
    
    TEST(InvalidPercentageThrowsException) {
        CHECK_THROW(Discount(-5.0), std::invalid_argument);
        CHECK_THROW(Discount(150.0), std::invalid_argument);
    }
    
    TEST(ApplyDiscount) {
        Discount discount(25.0);
        double originalPrice = 1000.0;
        double discountedPrice = discount.calculateDiscountedPrice(originalPrice);
        
        CHECK_EQUAL(750.0, discountedPrice);
    }
    
    TEST(ApplyZeroDiscount) {
        Discount discount(0.0);
        double originalPrice = 1000.0;
        double discountedPrice = discount.calculateDiscountedPrice(originalPrice);
        
        CHECK_EQUAL(1000.0, discountedPrice);
    }
    
    TEST(ApplyDiscountToNegativePriceThrowsException) {
        Discount discount(10.0);
        CHECK_THROW(discount.calculateDiscountedPrice(-100.0), std::invalid_argument);
    }
    
    TEST(IsValidDiscount) {
        Discount validDiscount(10.0);
        Discount zeroDiscount(0.0);
        
        CHECK(validDiscount.isValid());
        CHECK(!zeroDiscount.isValid());
    }
}

SUITE(RatingTests) {
    TEST(DefaultRating) {
        Rating rating;
        
        CHECK_EQUAL(0.0, rating.getValue());
        CHECK_EQUAL(0, rating.getVotesCount());
        CHECK(!rating.isValid());
    }
    
    TEST(InitialRating) {
        Rating rating(4.5, 10);
        
        CHECK_EQUAL(4.5, rating.getValue());
        CHECK_EQUAL(10, rating.getVotesCount());
        CHECK(rating.isValid());
    }
    
    TEST(AddVote) {
        Rating rating(4.0, 1); // 4.0 from 1 vote
        rating.addVote(5.0);   // Add 5.0
        
        CHECK_EQUAL(2, rating.getVotesCount());
        CHECK_CLOSE(4.5, rating.getValue(), 0.001); // (4.0 + 5.0) / 2 = 4.5
    }
    
    TEST(AddInvalidVoteThrowsException) {
        Rating rating;
        CHECK_THROW(rating.addVote(6.0), std::invalid_argument);
        CHECK_THROW(rating.addVote(-1.0), std::invalid_argument);
    }
    
    TEST(InvalidInitialRatingThrowsException) {
        CHECK_THROW(Rating(6.0, 1), std::invalid_argument);
        CHECK_THROW(Rating(-1.0, 1), std::invalid_argument);
        CHECK_THROW(Rating(4.0, -1), std::invalid_argument);
    }
}

SUITE(DurationTests) {
    TEST(DefaultDuration) {
        Duration duration;
        
        CHECK_EQUAL(0, duration.getHours());
        CHECK_EQUAL(0, duration.getDays());
    }
    
    TEST(DurationInHours) {
        Duration duration(48); // 48 hours
        
        CHECK_EQUAL(48, duration.getHours());
        CHECK_EQUAL(2, duration.getDays());
    }
    
    TEST(AddHours) {
        Duration duration(24);
        duration.addHours(12);
        
        CHECK_EQUAL(36, duration.getHours());
        CHECK_EQUAL(1, duration.getDays());
    }
    
    TEST(AddNegativeHoursThrowsException) {
        Duration duration;
        CHECK_THROW(duration.addHours(-5), std::invalid_argument);
    }
    
    TEST(InvalidDurationThrowsException) {
        CHECK_THROW(Duration(-10), std::invalid_argument);
    }
    
    TEST(GetFormattedDuration) {
        Duration duration1(5);
        Duration duration2(25);
        Duration duration3(48);
        
        CHECK_EQUAL("5 hours", duration1.getFormatted());
        CHECK_EQUAL("1d 1h", duration2.getFormatted());
        CHECK_EQUAL("2 days", duration3.getFormatted());
    }
}