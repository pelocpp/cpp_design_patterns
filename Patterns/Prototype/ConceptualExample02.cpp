// ===========================================================================
// ConceptualExample02.cpp // Prototype Pattern
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

namespace ConceptualExample02 {

    enum class Type {
        PROTOTYPE_1,
        PROTOTYPE_2
    };

    /**
     * The example class that has cloning ability. 
     * We'll see how the values of fields with different types will be cloned.
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

        virtual Prototype* clone() const = 0;

        virtual void print() {
            std::cout << "print:  " << m_prototypeName << " with field : " << m_prototypeField << std::endl;
        }

        virtual void update(float prototype_field) {
            this->m_prototypeField = prototype_field;
            std::cout << "Call update from " << m_prototypeName << " with field : " << prototype_field << std::endl;
        }
    };

    /**
     * ConcretePrototype1 is a Sub-Class of Prototype and implements the clone method.
     * In this example all data members of Prototype Class are on the Stack. If you
     * have pointers in your properties, for example: String* m_name, you will need to
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
         * Notice that the clone method returns a pointer to a new ConcretePrototype1
         * replica. so, the client (who calls the clone method) has the responsability
         * to free that memory. I you have smart pointer knowledge you may prefer to
         * use unique_pointer here.
         */
        virtual Prototype* clone() const override {
            return new ConcretePrototype1{ *this };
        }
    };

    class ConcretePrototype2 : public Prototype 
    {
    private:
        float m_concretePrototypeField2;

    public:
        ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
            : Prototype{ prototype_name }, m_concretePrototypeField2{ concrete_prototype_field } {}

        virtual Prototype* clone() const override {
            return new ConcretePrototype2{ *this };
        }
    };

    /**
     * In PrototypeFactory you have two concrete prototypes, one for each concrete
     * prototype class, so each time you want to create a bullet, you can use the
     * existing ones and clone those.
     */

    class PrototypeFactory 
    {
    private:
        std::unordered_map<Type, Prototype*> m_originals;

    public:
        PrototypeFactory()
        {
            m_originals[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
            m_originals[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
        }

        /**
         * Be carefull of free all memory allocated. Again, if you have smart pointers
         * knowelege will be better to use it here.
         */

        ~PrototypeFactory() {
            delete m_originals[Type::PROTOTYPE_1];
            delete m_originals[Type::PROTOTYPE_2];
        }

        /**
         * Notice here that you just need to specify the type of the prototype you
         * want and the method will create from the object with this type.
         */
        Prototype* createPrototype(Type type) {
            return m_originals[type]->clone();
        }
    };

    void client(PrototypeFactory& factory) 
    {
        std::cout << "Let's create a Prototype 1" << std::endl;

        Prototype* prototype = factory.createPrototype(Type::PROTOTYPE_1);
        prototype->print();
        prototype->update(10);
        delete prototype;
        std::cout << std::endl;

        std::cout << "Let's create a Prototype 2" << std::endl;
        prototype = factory.createPrototype(Type::PROTOTYPE_2);
        prototype->print();
        prototype->update(20);
        delete prototype;
        std::cout << std::endl;
    }
}

void test_conceptual_example_02()
{
    using namespace ConceptualExample02;

    PrototypeFactory* prototype_factory = new PrototypeFactory();
    client(*prototype_factory);
    delete prototype_factory;
}

// ===========================================================================
// End-of-File
// ===========================================================================
