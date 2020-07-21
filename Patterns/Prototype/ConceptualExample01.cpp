// ===========================================================================
// ConceptualExample01.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

class Prototype
{
private:
    int m_id;

protected:
    Prototype(int id) : m_id(id) {}

public:
    int getId() { return m_id; }
    void setId(int id) { m_id = id; }

public:
    virtual std::shared_ptr<Prototype> Clone() = 0;
};

class ConcretePrototype : public Prototype
{
public:
    ConcretePrototype(int id) : Prototype(id) {}

    std::shared_ptr<Prototype> Clone() override
    {
        std::shared_ptr<Prototype> copy = std::make_shared<ConcretePrototype>(getId());
        return copy;
    }
};

void test_conceptual_example_01()
{
    std::shared_ptr<ConcretePrototype> prototype = 
        std::make_shared<ConcretePrototype>(1);

    std::shared_ptr<ConcretePrototype> clone = 
        std::static_pointer_cast<ConcretePrototype> (prototype->Clone());

    clone->setId(2);

    std::cout << "Prototype: " << prototype->getId() << std::endl;
    std::cout << "Clone:     " << clone->getId() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
