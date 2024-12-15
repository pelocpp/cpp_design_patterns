// ===========================================================================
// ConceptualExample_01.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <memory>
#include <string>

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
        void action(std::string message)
        {
            std::cout << "Action called with message " << message << std::endl;
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
        virtual ~CommandBase() {}

        CommandBase(std::shared_ptr<Receiver> receiver)
            : m_receiver{ receiver }
        {}

        virtual void execute() const = 0;
    };

    /**
     * Concrete implementation of CommandBase interface.
     */
    class ConcreteCommand : public CommandBase
    {
    private:
        std::string m_data;

    public:
        ConcreteCommand(std::shared_ptr<Receiver> receiver)
            : CommandBase{ receiver }
        {}

        void setData(std::string data)
        {
            m_data = data;
        }

        virtual void execute() const override
        {
            m_receiver->action(m_data);
        }
    };

    /**
     * Invoker executes Command
     */
    class Invoker
    {
    private:
        std::shared_ptr<CommandBase> m_command;

    public:
        void setCommand(std::shared_ptr<CommandBase> command)
        {
            m_command = command;
        }

        void executeCommand()
        {
            m_command->execute();
        }
    };
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    auto receiver { std::make_shared<Receiver>() };

    auto command { std::make_shared<ConcreteCommand>(receiver) };

    command->setData("Hello, world!");

    Invoker invoker{};

    invoker.setCommand(command);

    invoker.executeCommand();
}

// ===========================================================================
// End-of-File
// ===========================================================================
