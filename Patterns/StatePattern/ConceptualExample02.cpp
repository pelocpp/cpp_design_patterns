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
        setState(state);
    }

    void Context::request()
    {
        m_state->handle(shared_from_this());
    }

    void Context::setState(std::shared_ptr<StateBase> base)
    {
        m_state = base;
        std::cout << "Current state: " << m_state->getDescription() << std::endl;
    }

    void ConcreteStateA::handle(std::shared_ptr<Context> context)
    {
        std::shared_ptr<StateBase> newState = std::make_shared<ConcreteStateB>();
        context->setState(newState);
    }

    void ConcreteStateB::handle(std::shared_ptr<Context> context)
    {
        std::shared_ptr<StateBase> newState = std::make_shared<ConcreteStateA>();
        context->setState(newState);
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExample02;

    std::shared_ptr<StateBase> initialState{ std::make_shared<ConcreteStateA>() };

    std::shared_ptr<Context> context{ std::make_shared<Context>(initialState) };

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
