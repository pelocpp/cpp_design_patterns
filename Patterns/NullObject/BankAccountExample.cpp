#include <iostream>
#include <string>
#include <sstream>
#include <memory>

class Logger
{
public:
    virtual ~Logger() {}

    virtual void info(const std::string& s) = 0;
    virtual void warn(const std::string& s) = 0;
};

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger() {};

    void info(const std::string& s) override {
        std::cout << "INFO: " << s << std::endl;
    }

    void warn(const std::string& s) override {
        std::cout << "WARNING!!! " << s << std::endl;
    }
};

class NullLogger : public Logger
{
public:
    NullLogger() {};
    void info(const std::string& s) override {}
    void warn(const std::string& s) override {}
};

class BankAccount
{
private:
    std::shared_ptr<Logger> m_log;
    std::string m_name;
    int m_balance = 0;

    static std::shared_ptr<Logger> nullLogger;

public:
  BankAccount(
      const std::string& name, 
      int balance, 
      const std::shared_ptr<Logger>& logger = nullLogger)
    :
      m_log{ logger }, m_name{ name }, m_balance{ balance }
    {}

    void deposit(int amount)
    {
        m_balance += amount;

        std::ostringstream oss;
        oss << "Deposited ";
        oss << std::to_string(amount);
        oss << "€ to ";
        oss << m_name;
        oss << ", balance is now ";
        oss << std::to_string(m_balance);
        oss << "€";

        m_log->info(oss.str());
    }

    void withdraw(int amount)
    {
        std::ostringstream oss;

        if (m_balance >= amount)
        {
            m_balance -= amount;

            oss << "Withdrew ";
            oss << std::to_string(amount);
            oss << "€ from ";
            oss << m_name;
            oss << ", ";
            oss << std::to_string(m_balance);
            oss << "€ left";

            m_log->info(oss.str());
        } 
        else
        {
            oss << "Tried to withdraw ";
            oss << std::to_string(amount);
            oss << "€ from ";
            oss << m_name;
            oss << " but couldn't due to low balance";

            m_log->warn(oss.str());
        }
    }
};

std::shared_ptr<Logger> BankAccount::nullLogger = std::make_shared<NullLogger>();

void test_bank_account()
{
    std::shared_ptr<Logger> logger = std::make_shared<ConsoleLogger>();

    BankAccount account{ "primary account", 1000, logger };
    account.deposit(2000);
    account.withdraw(2500);
    account.withdraw(1000);
    std::cout << "First account done." << std::endl;

    // note: default value of third parameter yields NullLogger object
    BankAccount account2{ "second account", 1000 };
    account2.deposit(2000);
    account2.withdraw(2500);
    account2.withdraw(1000);
    std::cout << "Done." << std::endl;
}