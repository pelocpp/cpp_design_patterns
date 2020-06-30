//// ===========================================================================
//// ConceptualExample01.cpp // State Pattern
//// ===========================================================================
//
//#include <iostream>
//#include <string>
//#include <memory>
//
//// very simple example of state pattern
//namespace ConceptualExample01 {
//
//    class Context;
//    class ConcreteStateA;
//    class ConcreteStateB;
//    class StateBase;
//
//    class StateBase
//    {
//    public:
//        virtual void Handle(Context* context) = 0;
//    };
//
//    class ConcreteStateA : public StateBase
//    {
//    public:
//        void Handle(Context* context) override
//        {
//            context->setState (new ConcreteStateB());
//        }
//    };
//
//    class ConcreteStateB : public StateBase
//    {
//    public:
//        void Handle(Context* context) override
//        {
//            context->setState(new ConcreteStateA());
//        }
//    };
//
//    class Context
//    {
//    private:
//        StateBase* _state;
//
//    public:
//        Context(StateBase* state)
//        {
//            _state = state;
//            // State = _state;
//            setState(state);
//        }
//
//        void Request()
//        {
//            _state->Handle(this);  // Das ist shitty !!!!
//        }
//
//        void setState(StateBase* base) {
//            _state = base;
//            //Console.WriteLine("Current state: {0}",_state.GetType());
//        }
//    };
//}
//
//void test_conceptual_example_01() {
//
//    using namespace ConceptualExample01;
//
//    //Context* context = new Context(new ConcreteStateA());
//    //context->Request();
//    //context->Request();
//    //context->Request();
//    //context->Request();
//}
//
//// ===========================================================================
//// End-of-File
//// ===========================================================================
