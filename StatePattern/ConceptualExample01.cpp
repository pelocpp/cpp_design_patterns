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
        m_state = state;
        setState(state);
    }

    void Context::request()
    {
        m_state->handle(this);
    }

    void Context::setState(StateBase* base) {
        m_state = base;
        std::cout << "Current state: " << typeid(*m_state).name() << std::endl;
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

    ConcreteStateA* ptr = new ConcreteStateA();
    Context* context = new Context(ptr);
    context->request();
    context->request();
    context->request();
    context->request();
    context->request();
    context->request();
}

// ===========================================================================
// End-of-File
// ===========================================================================
