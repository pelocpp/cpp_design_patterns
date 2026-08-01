// ===========================================================================
// ConceptualExample_01.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExample01 {

    /**
     * Receiver classes contain business logic.
     * They know how to perform all kinds of operations,
     * associated with carrying out a command.
     * In fact, any class may serve as a Receiver.
     */
    class Receiver
    {
    public:
        void action(std::string_view message)
        {
           // std::cout << "Action called with message " << message << std::endl;
            std::println("Action called with message {}", message);
        }
    };

    /**
     * The CommandBase interface declares a method for executing a command.
     */
    class CommandBase
    {
    protected:
        std::shared_ptr<Receiver> m_receiver;

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
        ConcreteCommand(std::shared_ptr<Receiver> receiver)
            : CommandBase{ std::move(receiver) }
        {}

        void setData(std::string data)
        {
            // note: accept by value and assign using `std::move` (avoids copies when called with rvalues).
            m_data = std::move(data);
        }

        virtual void execute() const override
        {
            if (m_receiver) {
                m_receiver->action(m_data);
            }
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
        void setCommand(std::unique_ptr <CommandBase> command)
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

    using namespace ConceptualExample01;

    auto receiver = std::make_shared<Receiver>();

    auto command = std::make_unique<ConcreteCommand>(receiver);

    command->setData("Hello, world!");

    Invoker invoker;

    invoker.setCommand(std::move(command));

    invoker.executeCommand();
}

// ===========================================================================
// End-of-File
// ===========================================================================
