// ===========================================================================
// ConceptualExample01.h // State Pattern
// ===========================================================================

namespace ConceptualExample01 {

    class Context;

    class StateBase
    {
    public:
        virtual ~StateBase() {};

        virtual void handle(Context* context) = 0;
        virtual std::string getDescription() = 0;
    };

    class Context
    {
    private:
        StateBase* m_state;

    public:
        Context(StateBase* state);
        ~Context();

        void request();
        void setState(StateBase* base);
    };

    class ConcreteStateA;
    class ConcreteStateB;

    class ConcreteStateA : public StateBase {
    private:
        std::string m_description;

    public:
        ConcreteStateA() : m_description{"State A"} {}
        virtual void handle(Context* context) override;
        virtual std::string getDescription() override {
            return m_description;
        }
    };

    class ConcreteStateB : public StateBase {
    private:
        std::string m_description;

    public:
        ConcreteStateB() : m_description{ "State B" } {}
        virtual void handle(Context* context) override;
        virtual std::string getDescription() override {
            return m_description;
        }
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
