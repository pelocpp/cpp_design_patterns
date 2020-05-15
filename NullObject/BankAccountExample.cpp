#include <iostream>
#include <string>
#include <memory>

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void info(const std::string& s) = 0;
    virtual void warn(const std::string& s) = 0;
};

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger() = default;

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
    NullLogger() = default;
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
      m_log{ logger },
      m_name{ name },
      m_balance{ balance }
    {}

    void deposit(int amount)
    {
        m_balance += amount;
        m_log->info("Deposited $" + std::to_string(amount)
            + " to " + m_name + ", balance is now $" + std::to_string(m_balance));
    }

    void withdraw(int amount)
    {
        if (m_balance >= amount)
        {
            m_balance -= amount;
            m_log->info("Withdrew $" + std::to_string(amount)
                + " from " + m_name + ", $" + std::to_string(m_balance) + " left");
        } 
        else
        {
            m_log->warn("Tried to withdraw $" + std::to_string(amount) +
                " from " + m_name + " but couldn't due to low balance");
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
    std::cout << "Done." << std::endl;
}