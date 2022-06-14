// ===========================================================================
// BankAccount.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <vector>

class BankAccount
{
private:
    int m_balance;

public:
    BankAccount(int balance) : m_balance{ balance } {}

    int getBalance() const { return m_balance; }

    void deposit(int amount) { m_balance += amount; }
    void withdraw(int amount) { m_balance -= amount; }
};

struct Command
{
    virtual void execute() = 0;
};

struct BankAccountCommand : public Command
{
public:
    enum class Action : bool { deposit, withdraw };

private:
    BankAccount& m_account;
    Action m_action;
    int m_amount;

public:
    BankAccountCommand(BankAccount& account, Action action, int amount)
        : m_account{ account }, m_action{ action }, m_amount{ amount } {}

    virtual void execute() override {
        (m_action == Action::deposit) ?
            m_account.deposit(m_amount) : m_account.withdraw(m_amount);
    }
};

void test_bankaccount_example()
{
    BankAccount ba1{ 1000 };
    BankAccount ba2{ 1000 };

    std::vector<BankAccountCommand> commands
    {
        BankAccountCommand{ba1, BankAccountCommand::Action::withdraw, 200},
        BankAccountCommand{ba2, BankAccountCommand::Action::deposit, 200}
    };

    for (auto& cmd : commands)
        cmd.execute();

    std::cout << ba1.getBalance() << std::endl;
    std::cout << ba2.getBalance() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
