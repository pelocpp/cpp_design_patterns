// ===========================================================================
// ConceptualExample03.cpp // State Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>

namespace ConceptualExample03 {

    /**
     * The base State class declares methods that all Concrete State should
     * implement and also provides a backreference to the Context object, associated
     * with the State.
     * This backreference can be used by States to transition the Context to another State.
     */

    class Context;

    class State {
    protected:
        Context* m_context;

    public:
        virtual ~State() {}

        void setContext(Context* context) {
            m_context = context;
        }

        virtual void handle1() = 0;
        virtual void handle2() = 0;
    };

    /**
     * The Context defines the interface of interest to clients. It also maintains a
     * reference to an instance of a State subclass, which represents the current
     * state of the Context.
     */
    class Context {
    private:
        State* m_state;

    public:
        Context(State* state) : m_state(nullptr) {
            transitionTo(state);
        }

        ~Context() {
            delete m_state;
        }

        /**
         * The Context allows changing the State object at runtime.
         */
        void transitionTo(State* state) {
            std::cout << "Context: Transition to " << typeid(*state).name() << "." << std::endl;
            if (m_state != nullptr)
                delete m_state;
            m_state = state;
            m_state->setContext(this);
        }

        /**
         * The Context delegates part of its behavior to the current State object.
         */
        void request1() {
            m_state->handle1();
        }

        void request2() {
            m_state->handle2();
        }
    };

    /**
     * Concrete States implement various behaviors,
     * associated with a state of the Context.
     */

    class ConcreteStateA : public State {
    public:
        void handle1() override;
        void handle2() override;
    };

    class ConcreteStateB : public State {
    public:
        void handle1() override;
        void handle2() override;
    };

    void ConcreteStateA::handle1() 
    {
        std::cout << "ConcreteStateA handles request1." << std::endl;
        std::cout << "ConcreteStateA wants to change the state of the context." << std::endl;
        m_context->transitionTo(new ConcreteStateB());
    }

    void ConcreteStateA::handle2()
    {
        std::cout << "ConcreteStateA handles request2." << std::endl;
    }

    void ConcreteStateB::handle1() 
    {
        std::cout << "ConcreteStateB handles request1." << std::endl;
    }

    void ConcreteStateB::handle2() 
    {
        std::cout << "ConcreteStateB handles request2." << std::endl;
        std::cout << "ConcreteStateB wants to change the state of the context." << std::endl;
        m_context->transitionTo(new ConcreteStateA());
    }

    /**
     * The client code.
     */
    static void clientCode() {
        Context* context = new Context(new ConcreteStateA);
        context->request1();
        context->request2();
        context->request1();
        context->request2();
        delete context;
    }
}

void test_conceptual_example_03() {

    using namespace ConceptualExample03;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
