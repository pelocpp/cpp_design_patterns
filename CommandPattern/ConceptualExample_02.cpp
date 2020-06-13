// ===========================================================================
// ConceptualExample_02.cpp // Command Pattern
// ===========================================================================

// https://refactoring.guru/design-patterns/command/cpp/example#example-0

#include <iostream>
#include <string>
#include <memory>

/**
 * The Command interface declares a method for executing a command.
 */
class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

/**
 * Some commands can implement simple operations on their own.
 */
class SimpleCommand : public Command {
private:
    std::string m_payLoad;

public:
    explicit SimpleCommand(std::string pay_load) : m_payLoad(pay_load) {}
    ~SimpleCommand() { std::cout << "d'tor SimpleCommand" << std::endl; }

    void execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << m_payLoad << ")" << std::endl;
    }
};

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request.
 * In fact, any class may serve as a Receiver.
 */
class Receiver {
public:
    ~Receiver() { std::cout << "d'tor Receiver" << std::endl; }

    void doSomething(const std::string& a) {
        std::cout << "Receiver: Working on (" << a << ".)" << std::endl;;
    }

    void doSomethingElse(const std::string& b) {
        std::cout << "Receiver: Also working on (" << b << ".)" << std::endl;;
    }
};

/**
 * However, some commands can delegate more complex operations to other objects,
 * called "receivers."
 */
class ComplexCommand : public Command {
private:
    std::shared_ptr<Receiver>  m_receiver;

    /**
     * Context data, required for launching the receiver's methods.
     */
    std::string m_a;
    std::string m_b;

    /**
     * Complex commands can accept one or several receiver objects
     * along with any context data via the constructor
     */
public:
    ComplexCommand(std::shared_ptr<Receiver> receiver, std::string a, std::string b)
        : m_receiver(receiver), m_a(a), m_b(b) {}

    ~ComplexCommand() { std::cout << "d'tor ComplexCommand" << std::endl; }

    /**
     * Commands can delegate to any methods of a receiver.
     */
    void execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object." << std::endl;
        m_receiver->doSomething(m_a);
        m_receiver->doSomethingElse(m_b);
    }
};

/**
 * The Invoker is associated with one or several commands.
 * It sends a request to the command.
 */
class Invoker {
private:
    std::shared_ptr<Command> m_onStart;
    std::shared_ptr<Command> m_onFinish;

public:
    ~Invoker() {
        std::cout << "d'tor Invoker" << std::endl;
    }

    void SetOnStart(std::shared_ptr<Command> command) {
        m_onStart = command;
    }

    void SetOnFinish(std::shared_ptr<Command> command) {
        m_onFinish = command;
    }

    /**
     * The Invoker does not depend on concrete command or receiver classes. The
     * Invoker passes a request to a receiver indirectly, by executing a command.
     */
    void DoSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (m_onStart) {
            m_onStart->execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (m_onFinish) {
            m_onFinish->execute();
        }
    }
};

/**
 * The client code can parameterize an invoker with any commands.
 */
void test_conceptual_example_02() {

    std::shared_ptr<Invoker> invoker = std::make_shared<Invoker>();
    std::shared_ptr<SimpleCommand> simpleCmd = std::make_shared<SimpleCommand>("Say Hi!");
    invoker->SetOnStart(simpleCmd);

    std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>();
    std::shared_ptr<ComplexCommand> complexCmd = 
        std::make_shared<ComplexCommand>(receiver, std::string("Send email"), std::string("Save report"));

    invoker->SetOnFinish(complexCmd);
    invoker->DoSomethingImportant();
}

// ===========================================================================
// End-of-File
// ===========================================================================
