// ===========================================================================
// ConceptualExample02.cpp // Bridge Pattern
// ===========================================================================

#include <iostream>
#include <memory>

namespace ConceptualExampleBridge02 {

    /**
     * The Implementor defines the interface for all implementation classes.
     * It doesn't have to match the Abstraction's interface.
     * In fact, the two interfaces can be entirely different.
     * Typically the Implementor interface provides only primitive operations, 
     * while the Abstraction defines higher-level operations based on those primitives.
     */

    class Implementor
    {
    public:
        virtual ~Implementor() {}

        virtual std::string operationImplementation() const = 0;
    };

    /**
     * Each Concrete Implementation corresponds to a specific platform and
     * implements the Implementor interface using that platform's API.
     */
    class ConcreteImplementationA : public Implementor
    {
    public:
        std::string operationImplementation() const override
        {
            return "ConcreteImplementationA: Here's the result on the platform A.";
        }
    };

    class ConcreteImplementationB : public Implementor
    {
    public:
        std::string operationImplementation() const override
        {
            return "ConcreteImplementationB: Here's the result on the platform B.";
        }
    };

    // ===========================================================================
        
    /**
     * The Abstraction defines the interface for the "control" part
     * of the two class hierarchies. It maintains a reference to an object
     * of the Implementor hierarchy and delegates all of the real work to this object.
     */
    class Abstraction
    {
    protected:
        std::unique_ptr<Implementor> m_implementor;

    public:
        Abstraction(std::unique_ptr<Implementor>& implementor)
            : m_implementor{ std::move(implementor) }
        {}

        virtual ~Abstraction() {}

        virtual std::string operation() const
        {
            return "Abstraction: Base operation with:\n" +
                m_implementor->operationImplementation();
        }
    };

    /**
     * You can extend the Abstraction without changing the Implementor classes.
     */
    class ExtendedAbstraction : public Abstraction
    {
    public:
        ExtendedAbstraction(std::unique_ptr<Implementor>& implementor)
            : Abstraction{ implementor }
        {}

        std::string operation() const override
        {
            return "ExtendedAbstraction: Extended operation with:\n" +
                m_implementor->operationImplementation();
        }
    };

    /**
     * Except for the initialization phase, where an Abstraction object gets linked
     * with a specific Implementor object, the client code should only depend on
     * the Abstraction class. This way the client code can support any abstraction-
     * implementation combination.
     */
    static void clientCode(std::unique_ptr<Abstraction>& abstraction)
    {
        // ...
        std::cout << abstraction->operation() << std::endl;
        // ...
    }
}

void test_conceptual_example_02() 
{
    using namespace ConceptualExampleBridge02;

    /**
     * The client code should be able to work with any pre-configured
     * abstraction-implementation combination.
     */
    std::unique_ptr<Implementor> implementor1{ std::make_unique<ConcreteImplementationA>() };
    std::unique_ptr<Abstraction> abstraction1{ std::make_unique<Abstraction>(implementor1) };
    clientCode(abstraction1);
    std::cout << std::endl;

    std::unique_ptr<Implementor> implementor2{ std::make_unique<ConcreteImplementationB>() };
    std::unique_ptr<Abstraction> abstraction2{ std::make_unique<ExtendedAbstraction>(implementor2) };
    clientCode(abstraction2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
