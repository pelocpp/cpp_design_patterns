// ===========================================================================
// ConceptualExample_01.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExample_Command_Pattern {

    /**
     * Receiver classes contain business logic.
     * They know how to perform all kinds of operations,
     * associated with carrying out a command.
     * In fact, any class may serve as a Receiver.
     */
    class Receiver
    {
    public:
        void action(std::string_view message) const
        {
            std::println("Action called with message {}", message);
        }
    };

    /**
     * The CommandBase interface declares a method for executing a command.
     */
    class CommandBase
    {
    private:
        std::shared_ptr<Receiver> m_receiver;

    protected:
        [[nodiscard]]
        const std::shared_ptr<Receiver>& getReceiver() const { return m_receiver; }

    public:
        virtual ~CommandBase() = default;

        explicit CommandBase(std::shared_ptr<Receiver> receiver)
            : m_receiver{ std::move(receiver) }
        {}

        virtual void execute() const = 0;
    };

    /**
     * Concrete implementation of CommandBase interface.
     */
    class ConcreteCommand final : public CommandBase
    {
    private:
        std::string m_data;

    public:
        ConcreteCommand(std::shared_ptr<Receiver> receiver, std::string data)
            : CommandBase{ std::move(receiver) }, m_data{ std::move(data) }
        {}

        void execute() const override
        {
            const std::shared_ptr<Receiver>& receiver = getReceiver();
            receiver->action(m_data);
        }
    };

    /**
     * Invoker executes Command
     */
    class Invoker final
    {
    private:
        // an invoker possesses the command exclusively
        std::unique_ptr<CommandBase> m_command;

    public:
        void setCommand(std::unique_ptr<CommandBase> command)
        {
            m_command = std::move(command);
        }

        void executeCommand()
        {
            if (m_command) {
                m_command->execute();
            }
        }
    };
}

void test_conceptual_example_01() {

    /**
     * Variant 1:
     * => classical Gang-of-Four implementation
     * => explicit Command hierarchy
     * => ideal for explaining the design pattern
     */

    using namespace ConceptualExample_Command_Pattern;

    auto receiver = std::make_shared<Receiver>();

    auto command = std::make_unique<ConcreteCommand>(receiver, "Hello, world!");

    Invoker invoker;

    invoker.setCommand(std::move(command));

    invoker.executeCommand();
}

// ===========================================================================
// End-of-File
// ===========================================================================
