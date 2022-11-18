// ===========================================================================
// ConceptualExample_02.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample02 {

    /**
     * The CommandBase interface declares a method for executing a command
     */
    class CommandBase {
    public:
        virtual ~CommandBase() {}
        virtual void execute() const = 0;
    };

    /**
     * Some commands can implement simple operations on their own:
     * Not the standard use case: no 'receiver' object used
     */
    class SimpleCommand : public CommandBase {
    private:
        std::string m_payLoad;

    public:
        explicit SimpleCommand(std::string pay_load) 
            : m_payLoad(pay_load) {}

        ~SimpleCommand() {}

        void execute() const override {
            std::cout << "SimpleCommand: Doing simple things like printing (" << m_payLoad << ")" << std::endl;
        }
    };

    /**
     * Receiver class with 'business logic'
     */
    class Receiver {
    public:
        ~Receiver() {}

        void doSomething(const std::string& data) {
            std::cout << "Receiver: Working on (" << data << ".)" << std::endl;
        }

        void doSomethingElse(const std::string& data) {
            std::cout << "Receiver: Also working on (" << data << ".)" << std::endl;
        }
    };

    /**
     * Mostly commands delegate more complex operations to other objects,
     * called "receivers"
     */
    class ComplexCommand : public CommandBase {
    private:
        std::shared_ptr<Receiver> m_receiver;

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
            : m_receiver{ receiver }, m_a{ a }, m_b{ b } {}

        ~ComplexCommand() {}

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
        std::shared_ptr<CommandBase> m_onStart;
        std::shared_ptr<CommandBase> m_onFinish;

    public:
        Invoker() : m_onStart{ nullptr }, m_onFinish{ nullptr } {}

        ~Invoker() {}

        void setOnStart(std::shared_ptr<CommandBase> command) {
            m_onStart = command;
        }

        void setOnFinish(std::shared_ptr<CommandBase> command) {
            m_onFinish = command;
        }

        /**
         * The Invoker does not depend on concrete command or receiver classes.
         * The Invoker passes a request to a receiver indirectly, by executing a command.
         */
        void doSomethingImportant() {
            std::cout << "Invoker: Does anybody want something done before I begin?" << std::endl;
            if (m_onStart) {
                m_onStart->execute();
            }
            std::cout << "Invoker: ... doing something really important ..." << std::endl;
            std::cout << "Invoker: Does anybody want something done after I finish?" << std::endl;
            if (m_onFinish) {
                m_onFinish->execute();
            }
        }
    };
}

/**
 * The client code can parameterize an invoker with any commands.
 */
void test_conceptual_example_02() {

    using namespace ConceptualExample02;

    Invoker invoker;

    std::shared_ptr<SimpleCommand> simpleCmd {
        std::make_shared<SimpleCommand>("Say Hi!") 
    };

    std::shared_ptr<Receiver> receiver {
        std::make_shared<Receiver>()
    };

    std::shared_ptr<ComplexCommand> complexCmd {
        std::make_shared<ComplexCommand>(
            receiver,
            std::string("Send email"),
            std::string("Save report")
        ) 
    };

    invoker.setOnStart(simpleCmd);

    invoker.setOnFinish(complexCmd);

    invoker.doSomethingImportant();
}

// ===========================================================================
// End-of-File
// ===========================================================================
