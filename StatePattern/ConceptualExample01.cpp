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

    void Context::Request()
    {
        m_state->Handle(this);
    }

    void Context::setState(StateBase* base) {
        m_state = base;
        std::cout << "Current state: " << typeid(*m_state).name() << std::endl;
    }

    void ConcreteStateA::Handle(Context* context) 
    {
        context->setState(new ConcreteStateB());
    }

    void ConcreteStateB::Handle(Context* context)
    {
        context->setState (new ConcreteStateA());
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    ConcreteStateA* ptr = new ConcreteStateA();
    Context* context = new Context(ptr);
    context->Request();
    context->Request();
    context->Request();
    context->Request();
    context->Request();
    context->Request();
}

// ===========================================================================
// End-of-File
// ===========================================================================
