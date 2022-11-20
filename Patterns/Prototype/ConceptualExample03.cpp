// ===========================================================================
// ConceptualExample03.cpp // Prototype Pattern
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

namespace ConceptualExample03 {

    enum class Type {
        Prototype_1,
        Prototype_2
    };

    /**
     * The example class that has cloning ability.
     * We'll see how the values of fields with different types will be cloned.
     */

    class Prototype
    {
    protected:
        std::string m_name;
        float m_field;

    public:
        Prototype() : m_name{}, m_field{} {}

        Prototype(std::string prototype_name)
            : m_name{ prototype_name }, m_field{} {}

        virtual ~Prototype() {}

        virtual Prototype* clone() const = 0;

        virtual void print() {
            std::cout << "print:  " << m_name << " with field : " << m_field << std::endl;
        }

        virtual void update(float field) {
            m_field = field;
            std::cout << "Call update from " << m_name << " with field : " << m_field << std::endl;
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
        float m_concreteField1;

    public:
        ConcretePrototype1(std::string name, float concrete_field)
            : Prototype{ name }, m_concreteField1{ concrete_field } {}

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
        float m_concreteField2;

    public:
        ConcretePrototype2(std::string name, float concrete_field)
            : Prototype{ name }, m_concreteField2{ concrete_field } {}

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
            m_originals[Type::Prototype_1] = new ConcretePrototype1("Prototype_1 ", 50.f);
            m_originals[Type::Prototype_2] = new ConcretePrototype2("Prototype_2 ", 60.f);
        }

        /**
         * Be carefull of free all memory allocated. Again, if you have smart pointers
         * knowelege will be better to use it here.
         */

        ~PrototypeFactory() {
            delete m_originals[Type::Prototype_1];
            delete m_originals[Type::Prototype_2];
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

        Prototype* prototype = factory.createPrototype(Type::Prototype_1);
        prototype->print();
        prototype->update(10);
        delete prototype;
        std::cout << std::endl;

        std::cout << "Let's create a Prototype 2" << std::endl;
        prototype = factory.createPrototype(Type::Prototype_2);
        prototype->print();
        prototype->update(20);
        delete prototype;
        std::cout << std::endl;
    }
}

void test_conceptual_example_03()
{
    using namespace ConceptualExample03;

    PrototypeFactory* prototype_factory = new PrototypeFactory();
    client(*prototype_factory);
    delete prototype_factory;
}


// ===========================================================================
// End-of-File
// ===========================================================================

