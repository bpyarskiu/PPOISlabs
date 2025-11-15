#include <UnitTest++/UnitTest++.h>
#icnlude "../Logger.hpp"

TEST(LoggerTest, LogMessages) {
    Logger& logger = Logger::getInstance();
    
    testing::internal::CaptureStdout();
    logger.log("Test message", LogLevel::INFO);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Test message") != std::string::npos);
    EXPECT_TRUE(output.find("INFO") != std::string::npos);
}