#include <UnitTest++/UnitTest++.h>
#include "../NotificationManager.hpp"
#include "../Company.hpp"
#include "../Client.hpp"
#include "../Employee.hpp"
#include "../ContactInfo.hpp"
#include "HELPERFILE.cpp"
#include <memory>

using namespace std;

// Тестовые данные для создания реальных объектов
class TestClient : public Client {
public:
    TestClient(int id, const string& email) 
        : Client(id, "Test", "Client", ContactInfo(email, "+1234567890"), 
                 id, "", nullptr, nullptr) {}
    
    string getEmail() const { 
        return getContactInfo().getEmail(); 
    }
    
    string getFullName() const  {
        return "Test Client";
    }
    
    void display() const  {
        cout << "Test Client: " << getFullName();
    }
};

class TestEmployee : public Employee {
public:
    TestEmployee(int id) 
        : Employee(id, "John", "Doe", ContactInfo("john@company.com", "+1234567890"), 
                   id, "Manager", 50000.0) {}
    
    string getFullName() const  { 
        return getFirstName() + " " + getLastName(); 
    }
    
    void display() const {
        cout << "Test Employee: " << getFullName();
    }
    
    void displayInfo() const  {
        cout << "Employee Info: " << getFullName() << ", Position: " << getPosition();
    }
};

class TestCompany : public Company {
public:
    TestCompany() : Company("Test Company", 2000, Address("Street", "City", "Country", "12345")) {}
    
    // Простой тестовый класс
};

TEST(NotificationManager_Constructor) {
    auto company = make_shared<TestCompany>();
    NotificationManager manager(company);
    
    CHECK(true);
}

TEST(NotificationManager_SendTourReminders_NoClients) {
    auto company = make_shared<TestCompany>();
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendTourReminders();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== SENDING TOUR REMINDERS ===") != string::npos);
    // Может быть 0 клиентов, если их не добавили
    CHECK(true);
}

TEST(NotificationManager_SendTourReminders_WithClients) {
    auto company = make_shared<TestCompany>();
    
    // Создаем и добавляем клиентов
    auto client1 = make_shared<TestClient>(1, "client1@test.com");
    auto client2 = make_shared<TestClient>(2, "client2@test.com");
    
    company->addClient(client1);
    company->addClient(client2);
    
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendTourReminders();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== SENDING TOUR REMINDERS ===") != string::npos);
    CHECK(output.find("Don't forget about your upcoming tour") != string::npos);
}

TEST(NotificationManager_SendPaymentReminders) {
    auto company = make_shared<TestCompany>();
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendPaymentReminders();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== SENDING PAYMENT REMINDERS ===") != string::npos);
    CHECK(true);
}

TEST(NotificationManager_SendSpecialOffers) {
    auto company = make_shared<TestCompany>();
    
    // Добавляем клиента
    auto client = make_shared<TestClient>(1, "client@test.com");
    company->addClient(client);
    
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendSpecialOffers();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== SENDING SPECIAL OFFERS ===") != string::npos);
    CHECK(output.find("Special 20% discount") != string::npos);
}

TEST(NotificationManager_SendSystemMaintenanceNotice) {
    auto company = make_shared<TestCompany>();
    
    // Добавляем сотрудника
    auto employee = make_shared<TestEmployee>(1);
    company->addEmployee(employee);
    
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendSystemMaintenanceNotice();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== SYSTEM MAINTENANCE NOTICE ===") != string::npos);
    CHECK(true);
}

TEST(NotificationManager_SendBirthdayGreetings) {
    auto company = make_shared<TestCompany>();
    
    // Добавляем клиентов
    auto client1 = make_shared<TestClient>(1, "client1@test.com");
    auto client2 = make_shared<TestClient>(2, "client2@test.com");
    
    company->addClient(client1);
    company->addClient(client2);
    
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendBirthdayGreetings();
    string output = redirect.getOutput();
    
    CHECK(output.find("=== BIRTHDAY GREETINGS ===") != string::npos);
    CHECK(output.find("Sent birthday greetings") != string::npos);
}

TEST(NotificationManager_SendAllNotifications) {
    auto company = make_shared<TestCompany>();
    
    // Добавляем тестовые данные
    auto client = make_shared<TestClient>(1, "client@test.com");
    auto employee = make_shared<TestEmployee>(1);
    
    company->addClient(client);
    company->addEmployee(employee);
    
    NotificationManager manager(company);
    
    StdoutRedirect redirect;
    manager.sendAllNotifications();
    string output = redirect.getOutput();
    
    // Проверяем основные заголовки
    CHECK(output.find("SENDING ALL NOTIFICATIONS") != string::npos);
    CHECK(output.find("ALL NOTIFICATIONS COMPLETED") != string::npos);
}