// ===========================================================================
// ConceptualExample_01.cpp // Command Pattern
// ===========================================================================

// https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command

#include <iostream>
#include <string>
#include <memory>

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
class CommandBase {
protected:
    std::shared_ptr<Receiver> m_receiver;

public:
    CommandBase(std::shared_ptr<Receiver> receiver) : m_receiver(receiver) {}
    virtual ~CommandBase() {}
    virtual void execute() const = 0;
};

//
//public abstract class CommandBase
//{
//    protected readonly Receiver _receiver;
//
//    public CommandBase(Receiver receiver)
//    {
//        _receiver = receiver;
//    }
//
//    public abstract void Execute();
//}

class ConcreteCommand : public CommandBase
{
private:
    std::string m_data;
public:
    ConcreteCommand (std::shared_ptr<Receiver> receiver) : CommandBase(receiver) {}

    void setData(std::string data) { m_data = data; }


    //public string Parameter { get; set; }

    //public ConcreteCommand(Receiver receiver) : base(receiver) { }

    //public override void Execute()
    //{
    //    _receiver.Action(Parameter);
    //}

    void execute() const override {
        m_receiver->action(m_data);
    }
};


class Invoker
{
private:
    std::shared_ptr<CommandBase> m_command;

public:
    void setCommand(std::shared_ptr<CommandBase> command) {
        m_command = command;
    }

    void executeCommand() {
        m_command->execute();
    }
};

/**
 * The client code can parameterize an invoker with any commands.
 */
void test_conceptual_example_01() {
    std::shared_ptr<Invoker> invoker = std::make_shared<Invoker>();
    std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>();
    std::shared_ptr<ConcreteCommand> command = std::make_shared<ConcreteCommand>(receiver);
    command->setData("Hello, world!");
    invoker->setCommand(command);
    invoker->executeCommand();
}

// ===========================================================================
// End-of-File
// ===========================================================================
