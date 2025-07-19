// ===========================================================================
// ConceptualExample01.cpp // Bridge Pattern
// ===========================================================================

#include <iostream>
#include <memory>

/**
 *  Basic Example
 */

namespace ConceptualExampleBridge01 {

    class Implementor
    {
    public:
        virtual void concreteOperation() = 0;
    };

    class Abstraction
    {
    protected:
        std::unique_ptr<Implementor> m_implementor;

    public:
        void setImplementor(std::unique_ptr<Implementor>& implementor)
        {
            m_implementor = std::move(implementor);
        }

        virtual void operation() = 0;
    };

    class RefinedAbstraction : public Abstraction
    {
    public:
        void operation() override
        {
            m_implementor->concreteOperation();
        }
    };

    class ConcreteImplementor : public Implementor
    {
    public:
        void concreteOperation() override
        {
            std::cout << "Concrete Implementor's Operation" << std::endl;
        }
    };

    static void clientCode(const std::unique_ptr<Abstraction>& abstraction) {
        // ...
        abstraction->operation();
        // ...
    }
}

void test_conceptual_example_01()
{
    using namespace ConceptualExampleBridge01;

    std::unique_ptr<Abstraction> abstraction {
        std::make_unique<RefinedAbstraction>()
    };

    std::unique_ptr<Implementor> implementation {
        std::make_unique<ConcreteImplementor>()
    };
    
    abstraction->setImplementor(implementation);
    
    clientCode(abstraction);
}

// ===========================================================================
// End-of-File
// ===========================================================================
