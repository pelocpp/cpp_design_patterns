// ===========================================================================
// ConceptualExample.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <memory>

namespace AbstractClassVsInterface {

    /* interface declaration */
    class Interface
    {
    public:
        virtual void method_first() = 0;  
        virtual void method_second() = 0;
    };

    /* abstract class declaration*/
    class AbstractClass 
    {
    public:
        AbstractClass(std::string message) : m_message(message) {}

        virtual void method_third() = 0;             // 'abstract' method

        virtual void method_fourth()                 // method with implementation
        { 
            std::cout << m_message << std::endl;
        }

    private:
        std::string m_message;
    };

    /* abstract class inheriting from an interface */
    class AnotherAbstractClass : public Interface
    {
    public:
        AnotherAbstractClass(double value) : m_value(value) {}

        virtual void method_first() override
        {
            std::cout << m_value << std::endl;
        }

    protected:
        double m_value;
    };

    /* abstract class implementing an interface */
    class ConcreteClass : public AnotherAbstractClass
    {
    public:
        ConcreteClass() : ConcreteClass(0.0) {}

        ConcreteClass(double value) 
            : AnotherAbstractClass(value), m_anotherValue{} {}

        ConcreteClass(double value1, double value2)
            : AnotherAbstractClass(value1), m_anotherValue{ value2 } {}

        virtual void method_second() override
        {
            std::cout << m_value << ", " << m_anotherValue << std::endl;
        }

    private:
        double m_anotherValue;
    };
}

void test_conceptual_example()
{
    using namespace AbstractClassVsInterface;

    // Interface obj1;                      // Error
    // AbstractClass obj2;                  // Error
    // AnotherAbstractClass obj3;           // Error
    ConcreteClass obj4{ 1.5, 2.5 };
    obj4.method_first();
    obj4.method_second();

    Interface& obj01{ obj4 };
    obj01.method_first();
    obj01.method_second();
    // AbstractClass& obj02{ obj4 };        // Error
    AnotherAbstractClass& obj03{ obj4 };
    obj03.method_first();
    obj03.method_second();

    Interface* obj001{ &obj4 };
    obj001->method_first();
    obj001->method_second();
    //  AbstractClass* obj002{ &obj4 };     // Error
    AnotherAbstractClass* obj003{ &obj4 };
    obj003->method_first();
    obj003->method_second();
}

// ===========================================================================
// End-of-File
// ===========================================================================
