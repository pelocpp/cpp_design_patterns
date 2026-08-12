// ===========================================================================
// ConceptualExample.cpp // State Pattern
// ===========================================================================

#include "ConceptualExample.h"

#include <iostream>
#include <memory>
#include <print>
#include <string>

// very simple example of state pattern
namespace ConceptualExample {

    Context::Context(std::unique_ptr<StateBase> state)
    {
        setState(std::move(state)); // transfer of ownership
    }

    void Context::request()
    {
        if (m_state) {
            m_state->handle(*this); // use passing by reference
        }
    }

    void Context::setState(std::unique_ptr<StateBase> state)
    {
        m_state = std::move(state);

        std::println("Current state: {}", m_state->getDescription());
    }

    void ConcreteStateA::handle(Context& context)
    {
        // generate the next state and pass it to the context.
        context.setState(std::make_unique<ConcreteStateB>());
    }

    void ConcreteStateB::handle(Context& context)
    {
        // generate the next state and pass it to the context.
        context.setState(std::make_unique<ConcreteStateA>());
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample;

    // let context simply reside on the stack.
    Context context{ std::make_unique<ConcreteStateA>() };

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
