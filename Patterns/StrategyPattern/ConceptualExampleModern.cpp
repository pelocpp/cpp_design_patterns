// ===========================================================================
// ConceptualExampleModern.cpp // Strategy Pattern
// ===========================================================================

#include <algorithm>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>
//
//WEITER:
//
//a) Absturz
//
//b) DFS // BFS
//
//https ://medium.com/@sabergholami72/strategy-design-pattern-when-and-how-to-use-it-60d5983f8ce2
//
//
//https://stackoverflow.com/questions/29031782/how-to-implement-strategy-pattern-in-c-with-stdfunction
//
//
//2. Biuld für Strategy Pattern --- evtl. siehe Iglberger


namespace StrategyConceptualExampleModern {

    /**
     * The Strategy Interface declares operations
     * common to all supported versions of some algorithm.
     *
     * The Context uses this interface to call the algorithm
     * defined by Concrete Strategies.
     *
     * In Modern C++ the Strategy Interface is defined througs a std::function type.   // TBD
     */

    class StrategyBase
    {
    public:
        virtual ~StrategyBase() {}

        virtual std::string doAlgorithm(const std::vector<std::string>& data) const = 0;
        // virtual std::string getName() const = 0;
    };

    using Strategy = std::function<std::string(const std::vector<std::string>&)>;

    /**
     * Concrete strategies implement the algorithm
     * while following the base Strategy interface.
     * The interface makes them interchangeable in the Context.
     */

    static std::string doAlgorithmA(const std::vector<std::string>& data)
    {
        std::string result{};

        std::for_each(
            data.begin(),
            data.end(),
            [&](const std::string& letter) {
                result += letter;
            }
        );

        std::sort(
            result.begin(),
            result.end()
        );

        return result;
    }

    static std::string doAlgorithmB(const std::vector<std::string>& data)
    {
        std::string result{};

        std::for_each(
            data.begin(),
            data.end(),
            [&](const std::string& letter) {
                result += letter;
            }
        );

        std::sort(
            result.begin(),
            result.end()
        );

        std::reverse(
            result.begin(),
            result.end()
        );

        return result;
    }

    /**
     * The Context defines the interface of interest to clients.
     */
    class Context
    {
        /**
         * The Context maintains an object implementing one of the available strategies,
         * in our case an std::function<> object.
         * The Context doesn't have any knowledge of the concrete implementation of the wrapped function.
         * It can just call this function via the std::function<> object.
         */
    private:
        Strategy m_strategy;

        /**
         * Usually, the Context accepts a strategy through the constructor,
         * but also provides setter metzhods to change the strategy at runtime.
         */
    public:
        // c'tor(s), d'tor
        Context(Strategy&& strategy) : m_strategy{ std::move(strategy) } {}
        Context(Strategy& strategy) : m_strategy{ strategy } {}
        ~Context() {}

        /**
         * Usually, the Context allows replacing a Strategy object at runtime.
         */
        void setStrategy(Strategy&& strategy)
        {
            m_strategy = std::move(strategy);
        }

        void setStrategy(Strategy& strategy)
        {
            m_strategy = strategy;
        }

        /**
         * The Context delegates some work to the strategy object instead of
         * implementing multiple versions of the algorithm on its own.
         */
        void doSomeBusinessLogic() const
        {
            std::vector<std::string> someStrings{ "A", "E", "C", "B", "D" };

            std::println("Context: Sorting data ...");

            std::string result{ m_strategy(someStrings) };

            std::println("Result: {}", result);
        }
    };

    /**
     * The client code picks a concrete strategy and passes it to the context.
     * The client should be aware of the differences between strategies
     * in order to make the right choice.
     */

    static void clientCode()
    {
        std::println("Client: Strategy is set to 'Normal Sorting':");

        Context context{ doAlgorithmA };
        context.doSomeBusinessLogic();
        std::println();

        std::println("Client: Strategy is set to 'Reverse Sorting':");
        context.setStrategy(doAlgorithmB);
        context.doSomeBusinessLogic();
    }
}

void test_conceptual_example_modern()
{
    using namespace StrategyConceptualExampleModern;

    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
