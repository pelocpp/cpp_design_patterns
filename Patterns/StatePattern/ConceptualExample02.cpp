// ===========================================================================
// ConceptualExample02.cpp // State Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ConceptualExample02.h"

// very simple example of state pattern
namespace ConceptualExample02 {

    Context::Context(std::shared_ptr<StateBase> state)
    {
        m_state = state;
        setState(state);
    }

    void Context::request()
    {
        m_state->handle(*this);
    }

    void Context::setState(std::shared_ptr<StateBase> base) {
        m_state = base;
        std::cout << "Current state: " << typeid(*m_state).name() << std::endl;
    }

    void ConcreteStateA::handle(Context& context) 
    {
        std::shared_ptr<ConcreteStateB> newState = std::make_shared<ConcreteStateB>();
        context.setState(newState);
    }

    void ConcreteStateB::handle(Context& context)
    {
        std::shared_ptr<ConcreteStateA> newState = std::make_shared<ConcreteStateA>();
        context.setState(newState);
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExample02;

    std::shared_ptr<StateBase> initialState = std::make_shared<ConcreteStateA>();
    Context context(initialState);
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
