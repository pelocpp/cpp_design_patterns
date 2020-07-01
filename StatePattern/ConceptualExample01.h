// ===========================================================================
// ConceptualExample01.h // State Pattern
// ===========================================================================

namespace ConceptualExample01 {

    class Context;

    class StateBase
    {
    public:
        virtual void Handle(Context* context) = 0;
    };

    class Context
    {
    private:
        StateBase* m_state;

    public:
        Context(StateBase* state);
        void Request();
        void setState(StateBase* base);
    };

    class ConcreteStateA;
    class ConcreteStateB;

    class ConcreteStateA : public StateBase {
    public:
        ConcreteStateA() = default;
        virtual void Handle(Context* context);
    };

    class ConcreteStateB : public StateBase {
    public:
        ConcreteStateB() = default;
        virtual void Handle(Context* context);
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
