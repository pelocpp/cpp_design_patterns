// ===========================================================================
// BankAccount.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class BankAccount
{
private:
    int m_balance;

public:
    BankAccount() : BankAccount{ 0 } {}
    BankAccount(int balance) : m_balance{ balance } {}

    void deposit(int amount) { m_balance += amount; }
    void withdraw(int amount) { m_balance -= amount; }
    int getBalance() const { return m_balance; }
};

class Command
{
protected:
    BankAccount& m_account;

public:
    Command(BankAccount& account) : m_account{ account } {}

    virtual void execute() const = 0;
};

class BankAccountDepositCommand : public Command
{
private:
    int m_amount;

public:
    BankAccountDepositCommand(BankAccount& account, int amount)
        : Command{ account }, m_amount{ amount } {}

    virtual void execute() const override
    {
        m_account.deposit(m_amount);
    }
};

class BankAccountWithdrawCommand : public Command
{
private:
    int m_amount;

public:
    BankAccountWithdrawCommand(BankAccount& account, int amount)
        : Command{ account }, m_amount{ amount } {}

    virtual void execute() const override
    {
        m_account.withdraw(m_amount);
    }
};

class Transactions
{
private:
    std::vector<std::shared_ptr<Command>> m_transactions;

public:
    Transactions(std::initializer_list<std::shared_ptr<Command>> transactions)
        : m_transactions{ transactions } {}

    void execute()
    {
        for (const auto& transaction : m_transactions) {
            transaction->execute();
        }
    }
};

void testBankAccounts_01()
{
    BankAccount ba1{ 1000 };
    BankAccount ba2{ 1000 };

    Transactions transactions
    {
        std::make_shared<BankAccountWithdrawCommand>(ba1, 300),
        std::make_shared<BankAccountDepositCommand>(ba2, 300)
    };

    transactions.execute();

    std::cout << ba1.getBalance() << std::endl;
    std::cout << ba2.getBalance() << std::endl;
}

// or without class 'Transactions' a.k.a. 'Invoker'

void testBankAccounts_02()
{
    BankAccount ba1{ 1000 };
    BankAccount ba2{ 1000 };

    std::vector<std::shared_ptr<Command>> transactions
    {
        std::make_shared<BankAccountWithdrawCommand>(ba1, 300),
        std::make_shared<BankAccountDepositCommand>(ba2, 300),
    };

    for (const auto& transaction : transactions) {
        transaction->execute();
    }

    std::cout << ba1.getBalance() << std::endl;
    std::cout << ba2.getBalance() << std::endl;
}

void testBankAccounts()
{
    testBankAccounts_01();
    testBankAccounts_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
