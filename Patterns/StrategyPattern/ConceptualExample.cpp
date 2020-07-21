// ===========================================================================
// ConceptualExample.cpp // Strategy Pattern
// ===========================================================================

// https://refactoring.guru/design-patterns/strategy/cpp/example

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * The Strategy interface declares operations common to all supported versions
 * of some algorithm.
 *
 * The Context uses this interface to call the algorithm
 * defined by Concrete Strategies.
 */
class Strategy
{
public:
    virtual ~Strategy() {}
    virtual std::string doAlgorithm(const std::vector<std::string>& data) const = 0;
    virtual std::string getName() const = 0;
};

/**
 * The Context defines the interface of interest to clients.
 */

class Context
{
    /**
     * @var Strategy The Context maintains a reference to one of the Strategy
     * objects. The Context does not know the concrete class of a strategy. It
     * should work with all strategies via the Strategy interface.
     */
private:
    Strategy* m_strategy;

    /**
     * Usually, the Context accepts a strategy through the constructor,
     * but also provides a setter to change it at runtime.
     */
public:
    Context(Strategy* strategy = nullptr) : m_strategy(strategy)
    {
    }

    ~Context()
    {
        delete m_strategy;
    }

    /**
     * Usually, the Context allows replacing a Strategy object at runtime.
     */
    void setStrategy(Strategy* strategy)
    {
        delete m_strategy;
        m_strategy = strategy;
    }

    /**
     * The Context delegates some work to the Strategy object instead of
     * implementing +multiple versions of the algorithm on its own.
     */
    void doSomeBusinessLogic() const
    {
        // ...
        std::vector<std::string> someStrings {"A", "E", "C", "B", "D"};
        std::cout 
            << "Context: Sorting data using strategy " 
            << "'" << m_strategy->getName() << "'" << std::endl;
        
        std::string result = m_strategy->doAlgorithm(someStrings);
        std::cout << result << "\n";
        // ...
    }
};

/**
 * Concrete Strategies implement the algorithm while following the base Strategy
 * interface. The interface makes them interchangeable in the Context.
 */
class ConcreteStrategyA : public Strategy
{
public:
    std::string getName() const override {
        return "Normal Sorting";
    }

    std::string doAlgorithm(const std::vector<std::string>& data) const override
    {
        std::string result;
        std::for_each(std::begin(data), std::end(data), [&result](const std::string& letter) {
            result += letter;
            });
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    std::string getName() const override {
        return "Reverse Sorting";
    }

    std::string doAlgorithm(const std::vector<std::string>& data) const override
    {
        std::string result;
        std::for_each(std::begin(data), std::end(data), [&result](const std::string& letter) {
            result += letter;
            });
        std::sort(std::begin(result), std::end(result));
        for (unsigned i = 0; i < result.size() / 2; i++)
        {
            std::swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};

/**
 * The client code picks a concrete strategy and passes it to the context.
 * The client should be aware of the differences between strategies in order
 * to make the right choice.
 */

void ClientCode()
{
    Strategy* strategy = new ConcreteStrategyA();
    Context* context = new Context(strategy);
    std::cout << "Client: Strategy is set to normal sorting:" << std::endl;
    context->doSomeBusinessLogic();
    std::cout << std::endl;

    std::cout << "Client: Strategy is set to reverse sorting:" << std::endl;
    strategy = new ConcreteStrategyB();
    context->setStrategy(strategy);
    context->doSomeBusinessLogic();

    delete context;
}

void test_conceptual_example()
{
    ClientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
