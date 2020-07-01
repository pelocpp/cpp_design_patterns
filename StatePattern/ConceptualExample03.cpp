// ===========================================================================
// ConceptualExample03.cpp // State Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ConceptualExample03.h"

// very simple example of state pattern
namespace ConceptualExample03 {

    Context::Context(std::shared_ptr<StateBase> state)
    {
        m_state = state;
        setState(state);
    }

    void Context::Request()
    {
        m_state->Handle(*this);
    }

    void Context::setState(std::shared_ptr<StateBase> base) {
        m_state = base;
        std::cout << "Current state: " << typeid(*m_state).name() << std::endl;
    }

    void ConcreteStateA::Handle(Context& context) 
    {
        std::shared_ptr<ConcreteStateB> newState = std::make_shared<ConcreteStateB>();
        context.setState(newState);
    }

    void ConcreteStateB::Handle(Context& context)
    {
       // context->setState (new ConcreteStateA());
        std::shared_ptr<ConcreteStateA> newState = std::make_shared<ConcreteStateA>();
        context.setState(newState);
    }
}

void test_conceptual_example_03() {

    using namespace ConceptualExample03;

   //  ConcreteStateA* ptr = new ConcreteStateA();
    std::shared_ptr<StateBase> initialState = std::make_shared<ConcreteStateA>();
    //Context* context = new Context(initialState);
    //context->Request();
    //context->Request();
    //context->Request();
    //context->Request();
    //context->Request();
    //context->Request();

    Context context(initialState);
    context.Request();
    context.Request();
    context.Request();
    context.Request();
    context.Request();
    context.Request();
    context.Request();
    context.Request();
}

// ===========================================================================
// End-of-File
// ===========================================================================
