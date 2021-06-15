// ===========================================================================
// ConceptualExample01.cpp // Memento Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

// very simple example of memento pattern
namespace ConceptualExample01 {

    class Memento
    {
    private:
        std::string m_state;

    public:
        Memento(const std::string& state) {
            m_state = state;
        }

        std::string getState() {
            return m_state;
        }
    };

    class Originator
    {
    private:
        std::string m_state;

    public:
        Originator(const std::string& state) : m_state{ state } {}

        // getter / setter
        void setState(const std::string& state) {
            m_state = state;
        }

        std::string getState() {
            return m_state;
        }

        // public interface
        std::shared_ptr<Memento> createMemento() {
            return std::make_shared<Memento>(m_state);
        }

        void setMemento(std::shared_ptr<Memento> memento) {
            setState (memento->getState());
        }
    };

    class CareTaker
    {
    private:
        std::shared_ptr<Memento> m_memento;

    public:
        // getter / setter
        void setMemento(std::shared_ptr<Memento> memento) {
            m_memento = memento;
        }

        std::shared_ptr<Memento> getMemento() {
            return m_memento;
        }
    };
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    // create originator with state 'A'
    std::shared_ptr<Originator> originator{ std::make_shared<Originator>(std::string{ "State A" }) };
    std::cout << originator->getState() << std::endl;

    // save state of originator using a Memento object with the help of a CareTaker
    std::shared_ptr<CareTaker> caretaker{ std::make_shared<CareTaker>() };
    std::shared_ptr<Memento> memento{ originator->createMemento() };
    caretaker->setMemento(memento);

    // originator changes state
    originator->setState(std::string{ "State B" });
    std::cout << originator->getState() << std::endl;
    
    // originator restores state
    memento = caretaker->getMemento();
    originator->setMemento(memento);
    std::cout << originator->getState() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
