// ===========================================================================
// ConceptualExample01.cpp // Prototype Pattern
// ===========================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

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
        // but 'virtual ConcretePrototype* clone()' compiles too
        virtual Prototype* clone() const override
        {
            return new ConcretePrototype(*this);
        }
    };

    void clientCode(Prototype* original)
    {
        Prototype* copy{ original->clone() };

        std::cout << "Copy: " << copy->getId() << std::endl;

        delete copy;
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
        // 'std::shared_ptr<ConcretePrototype> clone()' doesn't compile !!!
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

    Prototype* prototype{ 
        new ConcretePrototype { 123 }
    };

    clientCode(prototype);

    delete prototype;
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

    delete prototype;
    delete clone;
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
