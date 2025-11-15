#include <UnitTest++/UnitTest++.h>
#include "../Booking.hpp"
TEST(BookingTest, BookingCreation) {
    Client client(1, "John", "Doe", "john@email.com");
    Tour tour(1, "Beach Tour", "Relaxing beach vacation", 1000.0);
    
    Booking booking(1, client, tour, std::chrono::system_clock::now());
    EXPECT_EQ(booking.getClient().getEmail(), "john@email.com");
    EXPECT_EQ(booking.getTour().getName(), "Beach Tour");
    EXPECT_EQ(booking.getStatus(), BookingStatus::PENDING);
}