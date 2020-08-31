// ===========================================================================
// ConceptualExample02.h // State Pattern
// ===========================================================================

namespace ConceptualExample02 {

    class Context;

    class StateBase
    {
    public:
        virtual void handle(Context& context) = 0;
    };

    class Context
    {
    private:
        std::shared_ptr<StateBase> m_state;

    public:
        Context(std::shared_ptr<StateBase> state);
        void request();
        void setState(std::shared_ptr<StateBase> base);
    };

    class ConcreteStateA;
    class ConcreteStateB;

    class ConcreteStateA : public StateBase {
    public:
        ConcreteStateA() = default;
        virtual void handle(Context& context);
    };

    class ConcreteStateB : public StateBase {
    public:
        ConcreteStateB() = default;
        virtual void handle(Context& context);
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
