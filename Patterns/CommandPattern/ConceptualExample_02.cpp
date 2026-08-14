// ===========================================================================
// ConceptualExample_02.cpp // Command Pattern
// ===========================================================================

#include <functional>    // std::move_only_function (C++23) or std::function
#include <print>         // std::println
#include <string>
#include <string_view>

namespace ConceptualExample_Command_Pattern_Modern {

    class Receiver final {
    public:
        void action(std::string_view message) const {
            std::println("Action called with message {}", message);
        }
    };

    class FunctionalInvoker final {
    private:
        // C++23:
        // std::move_only_function is perfect for exclusive/movable callables (like lambdas with unique_ptr)
        // In case of you are using C++20: use std::function<void()> instead.
        
        std::move_only_function<void() const> m_command;

    public:
        void setCommand(std::move_only_function<void() const> command) {
            m_command = std::move(command);
        }

        void executeCommand() const {
            if (m_command) {
                m_command();
            }
        }
    };
}

void test_conceptual_example_02() {

    /**
     * Variant 2:
     * => idiomatic Modern C++
     * => command represented by a callable
     * => usually preferred unless polymorphic commands are required
     */

    using namespace ConceptualExample_Command_Pattern_Modern;

    auto receiver = std::make_shared<Receiver>();

    FunctionalInvoker invoker;

    std::string data{ "Hello from Lambda!" };

    /**
     * The "command" is a lambda expression that captures both the receiver and the data.
     * Note the use of the "Generalized Lambda Capture"
     */
    
    invoker.setCommand(
        [receiver, data = std::move(data)]() {
            receiver->action(data);
        }
    );

    invoker.executeCommand();
}

// ===========================================================================
// End-of-File
// ===========================================================================
