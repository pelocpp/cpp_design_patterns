// ===========================================================================
// ConceptualExample01.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample01 {

    class Prototype
    {
    private:
        int m_id;

    protected:
        Prototype(int id) : m_id{ id } {}

    public:
        int getId() { return m_id; }
        void setId(int id) { m_id = id; }

    public:
        virtual std::shared_ptr<Prototype> clone() = 0;
    };

    class ConcretePrototype : public Prototype
    {
    public:
        ConcretePrototype(int id) : Prototype{ id } {}

        virtual std::shared_ptr<Prototype> clone() override
        {
            std::shared_ptr<Prototype> copy = std::make_shared<ConcretePrototype>(getId());
            return copy;
        }
    };
}

void test_conceptual_example_01()
{
    using namespace ConceptualExample01;

    std::shared_ptr<ConcretePrototype> prototype {
        std::make_shared<ConcretePrototype>(1) 
    };

    std::shared_ptr<ConcretePrototype> clone {
        std::static_pointer_cast<ConcretePrototype> (prototype->clone()) 
    };

    clone->setId(2);

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
