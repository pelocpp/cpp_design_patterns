// ===========================================================================
// ConceptualExample02.cpp // Bridge Pattern
// ===========================================================================

#include <format>
#include <memory>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExample_Bridge_Pattern {

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
        virtual ~Implementor() = default;

        [[nodiscard]]
        virtual std::string_view operationImplementation() const = 0;
    };

    /**
     * Each Concrete Implementation corresponds to a specific platform and
     * implements the Implementor interface using that platform's API.
     */
    class ConcreteImplementationA : public Implementor
    {
    public:
        [[nodiscard]]
        std::string_view operationImplementation() const override
        {
            return "ConcreteImplementationA: Here's the result on the platform A.";
        }
    };

    class ConcreteImplementationB : public Implementor
    {
    public:
        [[nodiscard]]
        std::string_view operationImplementation() const override
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
        // Abstraction owns its Implementor.
        // This allows the two hierarchies to evolve independently.
        std::unique_ptr<Implementor> m_implementor;

    public:
        explicit Abstraction(std::unique_ptr<Implementor> implementor)
            : m_implementor{ std::move(implementor) }
        {}

        virtual ~Abstraction() = default;

        virtual std::string operation() const
        {
            return std::format("Abstraction: Base operation with:\n{}",
                m_implementor->operationImplementation());
        }
    };

    /**
     * You can extend the Abstraction without changing the Implementor classes.
     */
    class ExtendedAbstraction : public Abstraction
    {
    public:
        //ExtendedAbstraction(std::unique_ptr<Implementor> implementor)
        //    : Abstraction{ std::move(implementor) }
        //{}

        using Abstraction::Abstraction;

        std::string operation() const override
        {
            return std::format("ExtendedAbstraction: Extended operation with:\n{}",
                m_implementor->operationImplementation());
        }
    };

    /**
     * Except for the initialization phase, where an Abstraction object gets linked
     * with a specific Implementor object, the client code should only depend on
     * the Abstraction class. This way the client code can support any abstraction-
     * implementation combination.
     */
    static void clientCode(const Abstraction& abstraction)
    {
        // ...
        std::println("{}", abstraction.operation());
        // ...
    }
}

void test_conceptual_example_02() 
{
    using namespace ConceptualExample_Bridge_Pattern;

    /**
     * The client code should be able to work with any pre-configured
     * abstraction-implementation combination.
     */
    //std::unique_ptr<Implementor> implementor1{ std::make_unique<ConcreteImplementationA>() };

    //std::unique_ptr<Abstraction> abstraction1{ std::make_unique<Abstraction>(std::move(implementor1)) };

    auto abstraction1 =
        std::make_unique<Abstraction>(
            std::make_unique<ConcreteImplementationA>());

    clientCode(*abstraction1);
    std::println();

    //std::unique_ptr<Implementor> implementor2{ std::make_unique<ConcreteImplementationB>() };

    //std::unique_ptr<Abstraction> abstraction2{ std::make_unique<ExtendedAbstraction>(std::move(implementor2)) };

    auto abstraction2 =
        std::make_unique<Abstraction>(
            std::make_unique<ConcreteImplementationB>());

    clientCode(*abstraction2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
