// ===========================================================================
// ConceptualExample01.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample01
{
    class Prototype
    {
    private:
        int m_id;

    public:
        Prototype(int id) : m_id{ id } {}

        virtual ~Prototype() {}
        
        virtual Prototype* clone() const = 0;

    public:
        int getId() const { return m_id; }
        void setId(int id) { m_id = id; }
    };

    class ConcretePrototype : public Prototype
    {
    public:
        ConcretePrototype(int id) : Prototype{ id } {}

        // Note: Return Type = Type of base class - 
        // but 'virtual Prototype* clone()' compiles too
        virtual ConcretePrototype* clone() const override
        {
            return new ConcretePrototype(*this);
        }
    };

    void clientCode (std::unique_ptr<Prototype>& original)
    {
        std::unique_ptr<Prototype> copy{ original->clone() };
    }
}

namespace ConceptualExample02
{
    class Prototype
    {
    private:
        int m_id;

    protected:
        Prototype(int id) : m_id{ id } {}

    public:
        int getId() const { return m_id; }
        void setId(int id) { m_id = id; }

    public:
        virtual std::shared_ptr<Prototype> clone() const = 0;
    };

    class ConcretePrototype : public Prototype
    {
    public:
        ConcretePrototype(int id) : Prototype{ id } {}

        // Note: Return Type = Type of base class - 
        // but 'std::shared_ptr<ConcretePrototype> clone()' doesn't compile
        std::shared_ptr<Prototype> clone() const override
        {
            std::shared_ptr<Prototype> copy {
                std::make_shared<ConcretePrototype>(getId()) 
            };

            return copy;
        }
    };
}

void test_conceptual_example_01()
{
    using namespace ConceptualExample01;

    std::unique_ptr<Prototype> prototype{
        std::make_unique<ConcretePrototype>(123)
    };

    clientCode(prototype);
}

void test_conceptual_example_02()
{
    using namespace ConceptualExample01;

    Prototype* prototype{
        new ConcretePrototype(123)
    };
        
    Prototype* clone{ 
        prototype->clone() 
    };

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;

    clone->setId(456);

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;
}

void test_conceptual_example_03()
{
    using namespace ConceptualExample02;

    std::shared_ptr<Prototype> prototype {
        std::make_shared<ConcretePrototype>(123) 
    };

    std::shared_ptr<Prototype> clone { 
        prototype->clone() 
    };

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;

    clone->setId(456);

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
