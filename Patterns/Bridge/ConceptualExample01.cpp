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
        void setImplementor(std::shared_ptr<Implementor> value)
        {
            m_implementor = value;
        }

        virtual void operation()
        {
            m_implementor->concreteOperation();
        }
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
        void concreteOperation() override
        {
            std::cout << "Concrete Implementor's Operation" << std::endl;
        }
    };

    void clientCode1(std::shared_ptr<Abstraction> abstraction) {
        // ...
        abstraction->operation();
        // ...
    }
}

void test_conceptual_example_01()
{
    using namespace ConceptualExampleBridge01;

    std::shared_ptr<Abstraction> abstraction = std::make_shared<RefinedAbstraction>();
    abstraction->setImplementor(std::make_shared<ConcreteImplementor>());
    clientCode1(abstraction);
}

// ===========================================================================
// End-of-File
// ===========================================================================
