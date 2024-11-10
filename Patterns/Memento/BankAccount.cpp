// ===========================================================================
// ConceptualExample01.cpp // Memento Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace BankAccountMemento
{
    class BankAccount
    {
        friend std::ostream& operator<<(std::ostream& os, const BankAccount& ac);

    private:
        int    m_balance;

        struct Memento
        {
            Memento(int balance) : m_balance{ balance } {}
            int m_balance;
        };

        size_t m_index;
        std::vector<std::shared_ptr<Memento>> m_mementos;

    public:
        // c'tors
        BankAccount();
        BankAccount(int balance);

        // public interface
        void deposit(int amount);
        void withdraw(int amount);

        void undo();
        void redo();

        void restore(const std::shared_ptr<Memento>& memento);
    };

    BankAccount::BankAccount() : BankAccount{ 0 } {}

    BankAccount::BankAccount(int balance)
        : m_balance{ balance }, m_index{ 0 } 
    {
        m_mementos.push_back(std::make_shared<Memento>(m_balance));
    }

    void BankAccount::deposit(int amount) {
        m_balance += amount;
        m_mementos.push_back(std::make_shared<Memento>(m_balance));
        m_index++;
    }

    void BankAccount::withdraw(int amount) {
        m_balance -= amount;
        m_mementos.push_back(std::make_shared<Memento>(m_balance));
        m_index++;
    }

    void BankAccount::restore(const std::shared_ptr<BankAccount::Memento>& memento) {
        if (memento) {
            m_balance = memento->m_balance;
            m_mementos.push_back(memento);
            m_index = m_mementos.size() - 1;
        }
    }

    void BankAccount::undo() {
        if (m_index > 0) {
            --m_index;
            m_balance = m_mementos[m_index]->m_balance;
        }
    }

    void BankAccount::redo() {
        if ((m_index + 1) < m_mementos.size()) {
            ++m_index;
            m_balance = m_mementos[m_index]->m_balance;
        }
    }

    std::ostream& operator<<(std::ostream& os, const BankAccount& ac) {
        return os << "Balance: " << ac.m_balance;
    }

    static void clientCode_01()
    {
        BankAccount ba{ 0 };
        ba.deposit(50);
        ba.deposit(100);
        ba.withdraw(75);
        std::cout << ba << std::endl; // 75

        ba.undo();
        std::cout << "Undo 1: " << ba << std::endl;
        ba.undo();
        std::cout << "Undo 2: " << ba << std::endl;
        ba.redo();
        std::cout << "Redo 1: " << ba << std::endl;
        ba.redo();
        std::cout << "Redo 2: " << ba << std::endl;
    }
    /*
    balance: 175
    Undo 1: balance: 150
    Undo 2: balance: 100
    Redo 2: balance: 150
    */

    static void clientCode_02()
    {
        BankAccount ba{ 100 };
        ba.deposit(50);
        ba.deposit(25);
        std::cout << ba << std::endl; // 175

        ba.undo();
        std::cout << "Undo 1: " << ba << std::endl;
        ba.undo();
        std::cout << "Undo 2: " << ba << std::endl;
        ba.redo();
        std::cout << "Redo 2: " << ba << std::endl;
    }
    /*
    balance: 175
    Undo 1: balance: 150
    Undo 2: balance: 100
    Redo 2: balance: 150
    */
}

void test_bank_account_example() 
{
    using namespace BankAccountMemento;

    clientCode_01();
    clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================

