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

#include <memory>
#include <print>

namespace ConceptualExample01
{
    class Prototype
    {
    private:
        std::size_t m_id;

    public:
        Prototype(std::size_t id) : m_id{ id } {}

        virtual ~Prototype() {}
        
        virtual Prototype* clone() const = 0;

    public:
        std::size_t getId() const { return m_id; }
        void setId(std::size_t id) { m_id = id; }
    };

    class ConcretePrototype : public Prototype
    {
    public:
        ConcretePrototype(std::size_t id) : Prototype{ id } {}

        // Note: Return Type = Type of base class - 
        // but 'virtual ConcretePrototype* clone()' compiles too
        Prototype* clone() const override
        {
            return new ConcretePrototype{ *this };
        }
    };

    static void clientCode(Prototype* original)
    {
        Prototype* copy{ original->clone() };

        // std::cout << "Copy: " << copy->getId() << std::endl;
        std::println("Copy: {}", copy->getId());

        delete copy;
    }
}

namespace ConceptualExample02
{
    class Prototype
    {
    private:
        std::size_t m_id;

    protected:
        Prototype(std::size_t id) : m_id{ id } {}

    public:
        std::size_t getId() const { return m_id; }
        void setId(std::size_t id) { m_id = id; }

    public:
        virtual std::shared_ptr<Prototype> clone() const = 0;
    };

    class ConcretePrototype : public Prototype
    {
    public:
        ConcretePrototype(std::size_t id) : Prototype{ id } {}

        // Note: Return Type = Type of base class - 
        // 'std::shared_ptr<ConcretePrototype> clone() const override' doesn't compile !!!
        std::shared_ptr<Prototype> clone() const override
        {
            // Preserve full object state by copying *this instead of
            // reconstructing from a single property (getId()).
            std::shared_ptr<Prototype> copy {
                std::make_shared<ConcretePrototype>(*this)
            };

            return copy;
        }
    };
}

void test_conceptual_example_01()
{
    using namespace ConceptualExample01;

    Prototype* prototype{ new ConcretePrototype { 123 } };

    clientCode(prototype);

    delete prototype;
}

void test_conceptual_example_02()
{
    using namespace ConceptualExample01;

    Prototype* prototype{ new ConcretePrototype(123) };
        
    Prototype* clone{  prototype->clone() };

    std::println("Prototype: {}", prototype->getId());
    std::println("Clone:     {}", clone->getId());

    clone->setId(456);

    std::println("Prototype: {}", prototype->getId());
    std::println("Clone:     {}", clone->getId());

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

    std::println("Prototype: {}", prototype->getId());
    std::println("Clone:     {}", clone->getId());

    clone->setId(456);

    std::println("Prototype: {}", prototype->getId());
    std::println("Clone:     {}", clone->getId());
}

// ===========================================================================
// End-of-File
// ===========================================================================
