// ===========================================================================
// ConceptualExample01.cpp // Bridge Pattern
// ===========================================================================

#include <memory>
#include <print>

/**
 *  Basic Example
 */

namespace ConceptualExample_Bridge_Pattern {

    class Implementor
    {
    public:
        virtual ~Implementor() = default;

        virtual void concreteOperation() = 0;
    };

    class Abstraction
    {
    protected:
        std::unique_ptr<Implementor> m_implementor;

    public:
        explicit Abstraction(std::unique_ptr<Implementor> implementor)
            : m_implementor{ std::move(implementor) } 
        {}

        virtual ~Abstraction() = default;

        virtual void operation() = 0;
    };

    class RefinedAbstraction final : public Abstraction
    {
    public:
        using Abstraction::Abstraction;

        // or

        //RefinedAbstraction(std::unique_ptr<Implementor> implementor)
        //    : Abstraction{ std::move(implementor) }
        //{}

        void operation() override
        {
            m_implementor->concreteOperation();
        }
    };

    class ConcreteImplementor final : public Implementor
    {
    public:
        void concreteOperation() override
        {
            std::println("Concrete Implementor's Operation");
        }
    };

    static void clientCode(Abstraction& abstraction) {
        // ...
        abstraction.operation();
        // ...
    }
}

void test_conceptual_example_01()
{
    using namespace ConceptualExample_Bridge_Pattern;

    auto implementor = std::make_unique<ConcreteImplementor>();

    auto abstraction = std::make_unique<RefinedAbstraction>(std::move(implementor));

    clientCode(*abstraction);
}

// ===========================================================================
// End-of-File
// ===========================================================================
