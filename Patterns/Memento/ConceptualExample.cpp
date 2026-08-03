// ===========================================================================
// ConceptualExample01.cpp // Memento Pattern
// ===========================================================================

#include <memory>
#include <print>
#include <string>
#include <vector>

// very simple example of memento pattern
namespace ConceptualExample01 {

    // forward declaration so that Memento is aware of the friend relationship
    class Originator;

    class Memento
    {
    private:
        // only the Originator is permitted to see Memento internals
        friend class Originator;

    private:
        std::string m_state;

        // private c'tor: no one other than the Originator can create Mementos.
        explicit Memento(std::string state) : m_state{ std::move(state) } {}

        // private getter: no one other than the originator can read the state.
        const auto& getState() const noexcept { return m_state; }
    };

    class Originator
    {
    private:
        std::string m_state;

    public:
        // c'tor
        explicit Originator(std::string state) : m_state{ std::move(state) } {}

        // getter / setter
        void setState(std::string state) { m_state = std::move(state); }

        const std::string& getState() const noexcept { return m_state; } const

        // public interface
        [[nodiscard]]
        std::unique_ptr<Memento> save() const {

            // hands over responsibility/ownership (std::unique_ptr) to the CareTaker.

            return std::unique_ptr<Memento>{ new Memento{ m_state } };
        
            // since the Memento constructor is private, std::make_unique does not work here:
            // we therefore use a regular 'new' call within a std::unique_ptr constructor call.
        }

        // accepts the state as a const reference, since the Originator only reads it.
        void restore(const Memento& memento) {
            m_state = memento.getState();   // allowed, since Originator is a friend.
        }
    };

    class CareTaker
    {
    private:
        // std::unique_ptr<Memento> m_memento;
        std::vector<std::unique_ptr<Memento>> m_history;

    public:
        // getter / setter
        void backup(std::unique_ptr<Memento> memento) {
            // handover by std::move signals a change of possession.    
            m_history.push_back(std::move(memento));
        }
  
        // returns the latest managed memento without relinquishing ownership.
        [[nodiscard]]
        std::unique_ptr<Memento> latest() noexcept
        {
            if (m_history.empty()) {
                return nullptr;
            }

            auto memento = std::move(m_history.back());
            m_history.pop_back();

            return memento;
        }

        bool empty() const noexcept
        {
            return m_history.empty();
        }

        std::size_t size() const noexcept
        {
            return m_history.size();
        }
    };
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    // create originator with state 'A'
    Originator originator{ "State A" };
    std::println("{}", originator.getState());

    // save state of originator using a Memento object with the help of a CareTaker
    CareTaker caretaker;
    caretaker.backup(originator.save());

    // originator changes state
    originator.setState(std::string{ "State B" });
    std::println("{}", originator.getState());
    
    // originator restores state
    auto memento = caretaker.latest();
    if (memento) {
        originator.restore(*memento);
    }

    // print current originators state
    std::println("{}", originator.getState());
}

void test_conceptual_example_02() {

    using namespace ConceptualExample01;

    // create originator with state 'A'
    Originator originator{ "State A" };
    std::println("{}", originator.getState());

    // save state of originator using a Memento object with the help of a CareTaker
    CareTaker caretaker;
    caretaker.backup(originator.save());

    // originator changes state
    originator.setState(std::string{ "State B" });
    std::println("{}", originator.getState());

    // save again current state of originator using a Memento object with the help of a CareTaker
    caretaker.backup(originator.save());

    // originator restores state for the first time
    auto memento = caretaker.latest();
    if (memento) {
        originator.restore(*memento);
    }

    // print current originators state
    std::println("{}", originator.getState());

    // originator restores state for the second time
    memento = caretaker.latest();
    if (memento) {
        originator.restore(*memento);
    }

    // print current originators state
    std::println("{}", originator.getState());
}

// ===========================================================================
// End-of-File
// ===========================================================================
