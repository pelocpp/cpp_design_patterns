// ===========================================================================
// ConceptualExample.cpp // Strategy Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

/**
 * The StrategyBase interface declares operations
 * common to all supported versions of some algorithm.
 *
 * The Context uses this interface to call the algorithm
 * defined by Concrete Strategies.
 */
class StrategyBase
{
public:
    virtual ~StrategyBase() {}

    virtual std::string doAlgorithm(const std::vector<std::string>& data) const = 0;
    virtual std::string getName() const = 0;
};

/**
 * The Context defines the interface of interest to clients.
 */
class Context
{
    /**
     * The Context maintains a reference to one of the Strategy objects.
     * The Context does not know the concrete class of a strategy.
     * It should work with all strategies via the 'Strategy' interface.
     */
private:
    std::unique_ptr<StrategyBase> m_strategy;

    /**
     * Usually, the Context accepts a strategy through the constructor,
     * but also provides a setter to change it at runtime.
     */
public:
    Context(std::unique_ptr<StrategyBase> strategy)
        : m_strategy{ std::move(strategy) } 
    {}

    ~Context() {}

    /**
     * Usually, the Context allows replacing a Strategy object at runtime.
     */
    void setStrategy(std::unique_ptr<StrategyBase> strategy)
    {
        m_strategy = std::move(strategy);
    }

    /**
     * The Context delegates some work to the Strategy object instead of
     * implementing multiple versions of the algorithm on its own.
     */
    void doSomeBusinessLogic() const
    {
        std::vector<std::string> someStrings {"A", "E", "C", "B", "D"};

        std::cout 
            << "Context: Sorting data using strategy " 
            << "'" 
            << m_strategy->getName()
            << "'"
            << std::endl;
        
        std::string result{ m_strategy->doAlgorithm(someStrings) };

        std::cout << result << std::endl;
    }
};

/**
 * Concrete strategies implement the algorithm
 * while following the base Strategy interface.
 * The interface makes them interchangeable in the Context.
 */
class ConcreteStrategyA : public StrategyBase
{
public:
    virtual std::string getName() const override {
        return { "Normal Sorting" };
    }

    virtual std::string doAlgorithm(const std::vector<std::string>& data) const override
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
};

class ConcreteStrategyB : public StrategyBase
{
public:
    virtual std::string getName() const override {
        return { "Reverse Sorting" };
    }

    virtual std::string doAlgorithm(const std::vector<std::string>& data) const override
    {
        std::string result;

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
};

/**
 * The client code picks a concrete strategy and passes it to the context.
 * The client should be aware of the differences between strategies
 * in order to make the right choice.
 */

static void clientCode()
{
    std::cout << "Client: Strategy is set to normal sorting:" << std::endl;

    Context context{ std::make_unique<ConcreteStrategyA>() };
    context.doSomeBusinessLogic();
    std::cout << std::endl;

    std::cout << "Client: Strategy is set to reverse sorting:" << std::endl;
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

void test_conceptual_example()
{
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
