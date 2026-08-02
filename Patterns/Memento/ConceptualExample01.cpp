// ===========================================================================
// ConceptualExample01.cpp // Memento Pattern
// ===========================================================================

#include <iostream>
#include <memory>
#include <string>

// very simple example of memento pattern
namespace ConceptualExample01 {

    // forward declaration so that Memento is aware of the friend relationship.
    class Originator;

    class Memento
    {
    private:
        // only the Originator is permitted to see Memento internals.
        friend class Originator;

    private:
        std::string m_state;

        // private c'tor: No one other than the Originator can create Mementos.
        explicit Memento(const std::string& state) : m_state{ state } {}

        // private getter: No one other than the originator can read the state.
        const auto& getState() const { return m_state; }
    };

    class Originator
    {
    private:
        std::string m_state;

    public:
        // c'tor
        explicit Originator(const std::string& state) : m_state{ state } {}

        // getter / setter
        void setState(std::string state) { m_state = std::move(state); }

        std::string getState() const { return m_state; }

        // public interface
        std::unique_ptr<Memento> createMemento() const {

            // Hands over responsibility/ownership (unique_ptr) to the CareTaker.
            return std::unique_ptr<Memento>{ new Memento{ m_state } };
        
            // Since the Memento constructor is private, std::make_unique does not work directly here. 
            // We therefore use a regular new call within the unique_ptr.
        }

        // accepts the state as a const reference, since the Originator only reads it.
        void setMemento(const Memento& memento) {
            m_state = memento.getState();   // allowed, since Originator is a friend.
        }
    };

    class CareTaker
    {
    private:
        std::unique_ptr<Memento> m_memento;

    public:
        // getter / setter
        // Handover by Move signals a change of possession.
        void setMemento(std::unique_ptr<Memento> memento) {
            m_memento = std::move(memento);
        }

        //std::shared_ptr<Memento> getMemento() {
        //    return m_memento;
        //}
                
        // Liefert eine Referenz auf das verwaltete Memento, ohne den Besitz abzugeben
        // ?????????????????????????????
        const Memento* getMemento() const {
            return m_memento.get();
        }


    };
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    // create originator with state 'A'
    Originator originator{ "State A" };
    std::cout << originator.getState() << std::endl;

    // save state of originator using a Memento object
    // with the help of a CareTaker
    CareTaker caretaker{ };
  // std::shared_ptr<Memento> memento{ originator.createMemento() };
    caretaker.setMemento(originator.createMemento());

    // originator changes state
    originator.setState(std::string{ "State B" });
    std::cout << originator.getState() << std::endl;
    
    // originator restores state
    const Memento* memento = caretaker.getMemento();
    if (memento) {
        originator.setMemento(*memento);
    }
    std::cout << originator.getState() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
