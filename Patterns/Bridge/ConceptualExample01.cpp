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
        std::shared_ptr<Implementor> m_implementor;

    public:
        void setImplementor(const std::shared_ptr<Implementor>& implementor)
        {
            m_implementor = implementor;
        }

        virtual void operation() = 0;
    };

    class RefinedAbstraction : public Abstraction
    {
    public:
        virtual void operation() override
        {
            m_implementor->concreteOperation();
        }
    };

    class ConcreteImplementor : public Implementor
    {
    public:
        virtual void concreteOperation() override
        {
            std::cout << "Concrete Implementor's Operation" << std::endl;
        }
    };

    static void clientCode(const std::shared_ptr<Abstraction>& abstraction) {
        // ...
        abstraction->operation();
        // ...
    }
}

void test_conceptual_example_01()
{
    using namespace ConceptualExampleBridge01;

    std::shared_ptr<Abstraction> abstraction {
        std::make_shared<RefinedAbstraction>()
    };

    std::shared_ptr<Implementor> implementation {
        std::make_shared<ConcreteImplementor>()
    };
    
    abstraction->setImplementor(implementation);
    
    clientCode(abstraction);
}

// ===========================================================================
// End-of-File
// ===========================================================================
