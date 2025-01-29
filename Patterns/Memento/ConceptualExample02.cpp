// ===========================================================================
// ConceptualExample02.cpp // Memento Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <chrono>
#include <ctime>

namespace ConceptualExample02 {

    /**
     * The Memento interface provides a way to retrieve the memento's metadata, such
     * as creation date or name. However, it doesn't expose the Originator's state.
     */
    class Memento {
    public:
        virtual ~Memento() {};

        virtual std::string getName() const = 0;
        virtual std::string getDate() const = 0;
        virtual std::string getState() const = 0;
    };

    /**
     * The Concrete Memento contains the infrastructure
     * for storing the Originator's state.
     */
    class ConcreteMemento : public Memento
    {
    private:
        std::string m_state;
        std::string m_date;

    public:
        ConcreteMemento(std::string state) : m_state{ state } {
            m_date = currentTimeToString();
        }

        ~ConcreteMemento() {
            std::cout << "d'tor ConcreteMemento" << std::endl;
        }

        /**
         * The Originator uses this method when restoring its state.
         */
        virtual std::string getState() const override {
            return m_state;
        }

        /**
         * The rest of the methods are used by the CareTaker to display metadata.
         */
        virtual std::string getName() const override {
            return m_date + " / [" + m_state.substr(0, 9) + " ...]";
        }

        virtual std::string getDate() const override {
            return m_date;
        }

    private:
        std::string currentTimeToString() {
            char str[32];
            std::time_t now{ std::time(0) };
            ctime_s(str, sizeof str, &now);
            return std::string{ str };
        }
    };

    /**
     * The Originator holds some important state that may change over time. It also
     * defines a method for saving the state inside a memento
     * and another method for restoring the state from it.
     */
    class Originator 
    {
    private:
        std::string m_state;  // originator's state

    public:
        Originator(std::string state) : m_state{ state } {
            std::cout << "Originator: initial state: " << m_state << std::endl;
        }

        /**
         * The Originator's business logic may affect its internal state. Therefore,
         * the client should backup the state before launching methods of the business
         * logic via the save() method.
         */
        void doSomething() {
            std::cout << "Originator: working ..." << std::endl;
            m_state = generateRandomString(30);  // now state of Originator changes!
            std::cout << "Originator: state has changed to: " << m_state << std::endl;
        }

        /**
         * Saves the current state inside a memento.
         */
        std::shared_ptr<Memento> save() {
            return std::make_shared<ConcreteMemento>(m_state);
        }

        /**
         * Restores the Originator's state from a memento object.
         */
        void restore(std::shared_ptr<Memento>& memento) {
            m_state = memento->getState();
            std::cout << "Originator: state has changed to: " << m_state << std::endl;
        }

    private:
        std::string generateRandomString(int length = 10) {

            std::string_view alphanum {
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
            };

            std::string randomString{};

            for (size_t i{}; i != length; ++i) {
                randomString += alphanum[std::rand() % alphanum.size()];
            }

            return randomString;
        }
    };

    /**
     * The CareTaker doesn't depend on the Concrete Memento class. Therefore, it
     * doesn't have access to the originator's state, stored inside the memento.
     * It works with all mementos via the base Memento interface.
     */
    class CareTaker {

    private:
        std::vector<std::shared_ptr<Memento>> m_mementos;
        std::shared_ptr<Originator> m_originator;

    public:
        CareTaker(std::shared_ptr<Originator> originator) 
            : m_originator{ originator } 
        {}

        void backup() {
            std::cout << std::endl << "CareTaker:  Saving Originator's state" << std::endl;

            const auto& state = m_originator->save();
            m_mementos.push_back(state);

            // m_mementos.push_back(m_originator->save());
        }

        void undo() {
            if (!m_mementos.size()) {
                return;
            }

            std::shared_ptr<Memento> memento{ m_mementos.back() };
            m_mementos.pop_back();

            std::cout << "CareTaker: Restoring state: " << memento->getName() << std::endl;
            
            try {
                m_originator->restore(memento);
            }
            catch (...) {
                undo();  // heuristic decision: take next snapshot, if former snapshot has failed
            }
        }

        void showHistory() const {
            std::cout << "CareTaker: List of mementos:" << std::endl;
            for (std::shared_ptr<Memento> memento : m_mementos) {
                std::cout << memento->getName() << std::endl;
            }
        }
    };

    static void clientCode()
    {
        std::shared_ptr<Originator> originator { 
            std::make_shared<Originator>("Original state of this Originator")
        };

        std::shared_ptr<CareTaker> caretaker{ 
            std::make_shared<CareTaker>(originator)
        };

        caretaker->backup();
        originator->doSomething();
        caretaker->backup();
        originator->doSomething();
        caretaker->backup();
        originator->doSomething();

        std::cout << std::endl;
        caretaker->showHistory();
        std::cout << "\nClient: Do a rollback!\n\n";
        caretaker->undo();
        std::cout << "\nClient: Do second rollback!\n\n";
        caretaker->undo();
        std::cout << "\nClient: Do third rollback!\n\n";
        caretaker->undo();
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExample02;
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
