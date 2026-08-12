// ===========================================================================
// ConceptualExample.h // State Pattern
// ===========================================================================

#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace ConceptualExample {

    class Context;

    class StateBase
    {
    public:
        virtual ~StateBase() = default;

        virtual void handle(Context& context) = 0;

        virtual std::string_view getDescription() const noexcept = 0;
    };

    class Context
    {
    private:
        std::unique_ptr<StateBase> m_state;

    public:
        explicit Context(std::unique_ptr<StateBase> state);

        void setState(std::unique_ptr<StateBase> state);

        void request();
    };

    class ConcreteStateA final : public StateBase
    {
    public:
        void handle(Context& context) override;

        [[nodiscard]]
        std::string_view getDescription() const noexcept override { return "State A"; }
    };

    class ConcreteStateB final : public StateBase
    {
    public:
        void handle(Context& context) override;

        [[nodiscard]]
        std::string_view getDescription() const noexcept override { return "State B"; }

    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
