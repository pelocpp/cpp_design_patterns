// ===========================================================================
// ConceptualExample.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

class Prototype
{
private:
    std::string m_id;

protected:
    Prototype(std::string id) : m_id(id) {}

public:
    std::string getId() { return m_id; }

public:
    virtual std::shared_ptr<Prototype> Clone() = 0;
};

class ConcretePrototype : public Prototype
{
public:
    ConcretePrototype(std::string id) : Prototype(id) {}

    std::shared_ptr<Prototype> Clone() override
    {
        std::shared_ptr<Prototype> copy = std::make_shared<ConcretePrototype>(getId());
        return copy;
    }
};

void test_conceptual_example()
{
    std::shared_ptr<ConcretePrototype> prototype = 
        std::make_shared<ConcretePrototype>("1");

    std::shared_ptr<ConcretePrototype> clone = 
        std::static_pointer_cast<ConcretePrototype> (prototype->Clone());

    std::cout << "Cloned: " << clone->getId();
}

// ===========================================================================
// End-of-File
// ===========================================================================
