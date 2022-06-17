// ===========================================================================
// ConceptualExample02.h // State Pattern
// ===========================================================================

namespace ConceptualExample02 {

    class Context;

    class StateBase
    {
    public:
        virtual ~StateBase() {};

        virtual void handle(std::shared_ptr<Context> context) = 0;

        virtual std::string getDescription() const = 0;
    };

    class Context : public std::enable_shared_from_this<Context>
    {
    private:
        std::shared_ptr<StateBase> m_state;

    public:
        Context(std::shared_ptr<StateBase> state);
        void setState(std::shared_ptr<StateBase> base);
        void request();
    };

    class ConcreteStateA;
    class ConcreteStateB;

    class ConcreteStateA : public StateBase {
    private:
        std::string m_description;

    public:
        ConcreteStateA() : m_description{ "State A" } {}

        void handle(std::shared_ptr<Context> context) override;

        virtual std::string getDescription()  const override {
            return m_description;
        }
    };

    class ConcreteStateB : public StateBase {
    private:
        std::string m_description;

    public:
        ConcreteStateB() : m_description{ "State B" } {}

        void handle(std::shared_ptr<Context> context) override;

        virtual std::string getDescription() const override {
            return m_description;
        }
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
