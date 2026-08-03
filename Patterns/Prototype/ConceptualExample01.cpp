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

namespace ConceptualExample_New_Delete
{
    class Prototype
    {
    private:
        std::size_t m_id;

    protected:
        explicit Prototype(std::size_t id) : m_id{ id } {}

    public:    
        virtual ~Prototype() = default;

        [[nodiscard]]
        virtual Prototype* clone() const = 0;

    public:
        std::size_t getId() const noexcept { return m_id; }
        void setId(std::size_t id) noexcept { m_id = id; }
    };

    class ConcretePrototype final : public Prototype
    {
    public:
        explicit ConcretePrototype(std::size_t id) : Prototype{ id } {}

        ConcretePrototype(const ConcretePrototype&) = default;

        // Note: Return Type = Type of base class - 
        // but 'virtual ConcretePrototype* clone()' compiles too:
        // Covariant return types are supported for raw pointers.
        Prototype* clone() const override
        {
            return new ConcretePrototype{ *this };
        }
    };

    static void clientCode(const Prototype& original)
    {
        auto* copy{ original.clone() };

        std::println("Copy: {}", copy->getId());

        delete copy;
    }
}

namespace ConceptualExample_UniquePtr
{
    class Prototype
    {
    private:
        std::size_t m_id;

    protected:
        explicit Prototype(std::size_t id) : m_id{ id } {}

    public:
        virtual ~Prototype() = default;

        std::size_t getId() const noexcept { return m_id; }
        void setId(std::size_t id) noexcept { m_id = id; }

    public:
        [[nodiscard]]
        virtual std::unique_ptr<Prototype> clone() const = 0;
    };

    class ConcretePrototype final : public Prototype
    {
    public:
        explicit ConcretePrototype(std::size_t id) : Prototype{ id } {}

        ConcretePrototype(const ConcretePrototype&) = default;

        // Note: Return Type = Type of base class - 
        // 'std::unique_ptr<ConcretePrototype> clone() const override' doesn't compile:
        // Covariant return types are NOT supported for std::unique_ptr.
        std::unique_ptr<Prototype> clone() const override
        {
            // preserve the complete object state by invoking the copy constructor.
            return std::make_unique<ConcretePrototype>(*this);
        }
    };
}

void test_conceptual_example_new_delete()
{
    using namespace ConceptualExample_New_Delete;

    Prototype* prototype{ new ConcretePrototype { 123 } };

    clientCode(*prototype);

    delete prototype;
}

void test_conceptual_example_unique_ptr()
{
    using namespace ConceptualExample_UniquePtr;

    std::unique_ptr<Prototype> object{
        std::make_unique<ConcretePrototype>(123)
    };

    std::unique_ptr<Prototype> copy{
        object->clone()
    };

    std::println("Prototype: {}", object->getId());
    std::println("Clone:     {}", copy->getId());

    copy->setId(456);

    std::println("Prototype: {}", object->getId());
    std::println("Clone:     {}", copy->getId());
}

// ===========================================================================
// End-of-File
// ===========================================================================
