// ===========================================================================
// ConceptualExample03.h // State Pattern
// ===========================================================================

namespace ConceptualExample03 {

    class Context;

    class StateBase
    {
    public:
        virtual void Handle(Context& context) = 0;
    };

    class Context
    {
    private:
        std::shared_ptr<StateBase> m_state;

    public:
        Context(std::shared_ptr<StateBase> state);
        void Request();
        void setState(std::shared_ptr<StateBase> base);
    };

    class ConcreteStateA;
    class ConcreteStateB;

    class ConcreteStateA : public StateBase {
    public:
        ConcreteStateA() = default;
        virtual void Handle(Context& context);
    };

    class ConcreteStateB : public StateBase {
    public:
        ConcreteStateB() = default;
        virtual void Handle(Context& context);
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
