#include <UnitTest++/UnitTest++.h>
#include "../ReportGenerator.hpp"
#include "../Company.hpp"
#include "../Address.hpp"
#include <sstream>
#include <iostream>

// Вспомогательный класс для перехвата stdout
class StdoutRedirect {
private:
    std::streambuf* oldCoutBuffer;
    std::stringstream newBuffer;

public:
    StdoutRedirect() {
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(newBuffer.rdbuf());
    }
    
    ~StdoutRedirect() {
        std::cout.rdbuf(oldCoutBuffer);
    }
    
    std::string getOutput() const {
        return newBuffer.str();
    }
};

TEST(ReportGeneratorTest_FinancialReport) {
    Address base("ppp", "hhh", "zzz", "xxx");
    auto company = std::make_shared<Company>("Test Company", 2006, base);
    auto now = std::chrono::system_clock::now();
    auto weekAgo = now - std::chrono::hours(24*7);
    
    ReportGenerator reporter(company, ReportType::FINANCIAL, weekAgo, now);
    
    // Перехватываем вывод
    StdoutRedirect redirect;
    reporter.generateFinancialReport();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("FINANCIAL REPORT") != std::string::npos);
    CHECK(output.find("Total Revenue") != std::string::npos);
}

TEST(ReportGeneratorTest_AllReports) {
    Address base("Test City", "Test Street", "123", "456789");
    auto company = std::make_shared<Company>("Test Tourism", 2010, base);
    auto now = std::chrono::system_clock::now();
    auto monthAgo = now - std::chrono::hours(24*30);
    
    ReportGenerator reporter(company, ReportType::FINANCIAL, monthAgo, now);
    
    // Тестируем генерацию всех отчетов
    StdoutRedirect redirect;
    reporter.generateAllReports();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("FINANCIAL REPORT") != std::string::npos);
    CHECK(output.find("BOOKING STATISTICS") != std::string::npos);
    CHECK(output.find("CLIENT ACTIVITY") != std::string::npos);
}

TEST(ReportGeneratorTest_ReportSummary) {
    Address base("Moscow", "Tverskaya", "1", "125009");
    auto company = std::make_shared<Company>("Moscow Tours", 2015, base);
    auto now = std::chrono::system_clock::now();
    auto yearAgo = now - std::chrono::hours(24*365);
    
    ReportGenerator reporter(company, ReportType::BOOKING_STATISTICS, yearAgo, now);
    
    StdoutRedirect redirect;
    reporter.displayReportSummary();
    std::string output = redirect.getOutput();
    
    CHECK(output.find("Report Summary") != std::string::npos);
    CHECK(output.find("Company") != std::string::npos);
}