// ===========================================================================
// ConceptualExample04.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

/**
* Prototype Design Pattern
*
* Intent:
* Lets you copy existing objects without making your code dependent on
* their classes.
*/

namespace ConceptualExample04 {

    enum class Type
    {
        PROTOTYPE_1,
        PROTOTYPE_2
    };

    /**
     * The example class that has cloning ability. We'll see how the values of field
     * with different types will be cloned.
     */

    class Prototype
    {
    protected:
        std::string m_prototypeName;
        float m_prototypeField;

    public:
        Prototype() : m_prototypeName{}, m_prototypeField{} {}

        Prototype(std::string prototype_name) 
            : m_prototypeName{ prototype_name }, m_prototypeField{} {}

        virtual ~Prototype() {}

        virtual std::unique_ptr<Prototype> clone() const = 0;

        virtual void print() {
            std::cout << "print:  " << m_prototypeName << " with field : " << m_prototypeField << std::endl;
        }

        virtual void update(float prototype_field) {
            this->m_prototypeField = prototype_field;
            std::cout << "update: " << m_prototypeName << " with updated field : " << prototype_field << std::endl;
        }
    };

    /**
     * ConcretePrototype1 is a Sub-Class of Prototype and implements the clone Method
     * In this example all data members of Prototype Class are in the Stack. If you
     * have pointers in your properties for ex: String* m_name, you will need to
     * implement the Copy-Constructor to make sure you have a deep copy from the
     * clone method
     */

    class ConcretePrototype1 : public Prototype
    {
    private:
        float m_concretePrototypeField1;

    public:
        ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
            : Prototype{ prototype_name }, m_concretePrototypeField1{ concrete_prototype_field } {}

        /**
         * Notice that clone method returns a Pointer to a new ConcretePrototype1 replica.
         * So the client (who calls the clone method) has the responsability
         * to free that memory - or if you have smart pointer knowledge
         * you may prefer to use unique_pointer here.
         */
        virtual std::unique_ptr<Prototype> clone() const override {
            return std::make_unique<ConcretePrototype1>(*this);
        }
    };

    class ConcretePrototype2 : public Prototype
    {
    private:
        float m_concretePrototypeField2;

    public:
        ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
            : Prototype{ prototype_name }, m_concretePrototypeField2{ concrete_prototype_field } {}

        virtual std::unique_ptr<Prototype> clone() const override {
            return std::make_unique<ConcretePrototype2>(*this);
        }
    };

    /**
     * In PrototypeFactory you have two concrete prototypes, one for each concrete
     * prototype class, so each time you want to create a bullet , you can use the
     * existing ones and clone those.
     */

    class PrototypeFactory
    {
    private:
        // reserve space for two originals
        std::unordered_map<Type, std::shared_ptr<Prototype>> m_originals;

        /**
         * Be carefull of free all memory allocated. Again, if you have smart pointers
         * knowelege will be better to use it here.
         */

    public:
        PrototypeFactory()
        {
            m_originals[Type::PROTOTYPE_1] = std::make_shared<ConcretePrototype1>("PROTOTYPE_1", 100.0f);
            m_originals[Type::PROTOTYPE_2] = std::make_shared<ConcretePrototype2>("PROTOTYPE_2", 200.0f);
        }

        ~PrototypeFactory() {}

        /**
         * Notice here that you just need to specify the type of the prototype you
         * want and the method will create from the object with this type.
         */

        std::unique_ptr<Prototype> createPrototype(Type type) {
            return m_originals[type]->clone();
        }
    };

    void client(PrototypeFactory& factory)
    {
        std::cout << "Let's create a Prototype 1" << std::endl;

        std::unique_ptr<Prototype> prototype1 = factory.createPrototype(Type::PROTOTYPE_1);
        prototype1->print();
        prototype1->update(10);
        std::cout << std::endl;

        std::cout << "Let's create a Prototype 2" << std::endl;
        std::unique_ptr<Prototype> prototype2 = factory.createPrototype(Type::PROTOTYPE_2);
        prototype2->print();
        prototype2->update(20);
        std::cout << std::endl;
    }
}


void test_conceptual_example_05()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    using namespace ConceptualExample04;

    PrototypeFactory prototype_factory;
    client(prototype_factory);
}

// ===========================================================================
// End-of-File
// ===========================================================================
