// ===========================================================================
// ConceptualExample01.cpp // State Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ConceptualExample01.h"

// very simple example of state pattern
namespace ConceptualExample01 {

    Context::Context(StateBase* state)
    {
        m_state = (StateBase*) 0;
        setState(state);
    }

    Context::~Context()
    {
        if (m_state != NULL) {
            delete m_state;
        }
    }

    void Context::request()
    {
        m_state->handle(this);
    }

    void Context::setState(StateBase* base)
    {
        if (m_state != (StateBase*) 0) {
            delete m_state;
        }

        m_state = base;

        std::cout << "Current state: " << m_state->getDescription() << std::endl;
    }

    void ConcreteStateA::handle(Context* context) 
    {
        StateBase* base = new ConcreteStateB();
        context->setState(base);
    }

    void ConcreteStateB::handle(Context* context)
    {
        StateBase* base = new ConcreteStateA();
        context->setState (base);
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    ConcreteStateA* initialState{ new ConcreteStateA };

    Context context (initialState);

    context.request();
    context.request();
    context.request();
    context.request();
    context.request();
    context.request();
}

// ===========================================================================
// End-of-File
// ===========================================================================
