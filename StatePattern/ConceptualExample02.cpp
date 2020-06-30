// ===========================================================================
// ConceptualExample02.cpp // State Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>

namespace ConceptualExample02 {

    /**
     * The base State class declares methods that all Concrete State should
     * implement and also provides a backreference to the Context object, associated
     * with the State. This backreference can be used by States to transition the
     * Context to another State.
     */

    class Context;

    class State {
    protected:
        Context* m_context;

    public:
        virtual ~State() {}

        void set_context(Context* context) {
            m_context = context;
        }

        virtual void Handle1() = 0;
        virtual void Handle2() = 0;
    };

    /**
     * The Context defines the interface of interest to clients. It also maintains a
     * reference to an instance of a State subclass, which represents the current
     * state of the Context.
     */
    class Context {
        /**
         * @var State A reference to the current state of the Context.
         */
    private:
        State* m_state;

    public:
        Context(State* state) : m_state(nullptr) {
            this->TransitionTo(state);
        }
        ~Context() {
            delete m_state;
        }
        /**
         * The Context allows changing the State object at runtime.
         */
        void TransitionTo(State* state) {
            std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
            if (this->m_state != nullptr)
                delete this->m_state;
            this->m_state = state;
            this->m_state->set_context(this);
        }
        /**
         * The Context delegates part of its behavior to the current State object.
         */
        void Request1() {
            this->m_state->Handle1();
        }
        void Request2() {
            this->m_state->Handle2();
        }
    };

    /**
     * Concrete States implement various behaviors, associated with a state of the
     * Context.
     */

    class ConcreteStateA : public State {
    public:
        void Handle1() override;

        void Handle2() override {
            std::cout << "ConcreteStateA handles request2.\n";
        }
    };

    class ConcreteStateB : public State {
    public:
        void Handle1() override {
            std::cout << "ConcreteStateB handles request1.\n";
        }
        void Handle2() override {
            std::cout << "ConcreteStateB handles request2.\n";
            std::cout << "ConcreteStateB wants to change the state of the context.\n";
            this->m_context->TransitionTo(new ConcreteStateA);
        }
    };

    void ConcreteStateA::Handle1() {
        std::cout << "ConcreteStateA handles request1.\n";
        std::cout << "ConcreteStateA wants to change the state of the context.\n";

        this->m_context->TransitionTo(new ConcreteStateB);
    }

    /**
     * The client code.
     */
    void clientCode() {
        Context* context = new Context(new ConcreteStateA);
        context->Request1();
        context->Request2();
        delete context;
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExample02;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
