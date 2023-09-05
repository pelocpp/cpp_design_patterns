// ===========================================================================
// ConceptualExample.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

#include <iostream>
#include <string>

namespace AbstractClassVsInterface {

    /* interface declaration */
    class Interface
    {
    public:
        virtual void method_first() = 0;             // only 'abstract' methods
        virtual void method_second() = 0;
    };

    /* abstract class declaration */
    class AbstractClass 
    {
    public:
        AbstractClass(std::string message) : m_message{ message } {}

        virtual void method_third() = 0;             // 'abstract' method

        virtual void method_fourth()                 // method with implementation
        { 
            std::cout << m_message << std::endl;
        }

    private:
        std::string m_message;                       // data
    };

    /* abstract class inheriting from an interface */
    class AnotherAbstractClass : public Interface
    {
    public:
        AnotherAbstractClass(double value) : m_value { value } {}

        virtual void method_first() override
        {
            std::cout << m_value << std::endl;
        }

    protected:
        double m_value;
    };

    /* concrete class inheriting from an abstract class */
    class ConcreteClass : public AnotherAbstractClass
    {
    public:
        ConcreteClass() : ConcreteClass{ 1.0 } {}

        ConcreteClass(double value) 
            : AnotherAbstractClass{ value }, m_anotherValue{} {}

        ConcreteClass(double value1, double value2)
            : AnotherAbstractClass{ value1 }, m_anotherValue{ value2 } {}

        virtual void method_second() override
        {
            std::cout << m_value << ", " << m_anotherValue << std::endl;
        }

    private:
        double m_anotherValue;
    };

    /* concrete class inheriting from an interface */
    class AnotherConcreteClass : public Interface
    {
    public:
        AnotherConcreteClass() : m_oneMoreValue{ 1.0 } {}

        AnotherConcreteClass(double value) : m_oneMoreValue{ value } {}

        virtual void method_first() override
        {
            std::cout << m_oneMoreValue << std::endl;
        }

        virtual void method_second() override
        {
            method_first();
        }

    private:
        double m_oneMoreValue;
    };

    Interface* getInterface()
    {
        AnotherConcreteClass* obj = new AnotherConcreteClass();
        // or
        // Interface* obj = new AnotherConcreteClass();

        return obj;
    }

    void client()
    {
        Interface* ip;
        ip = getInterface();
        ip->method_first();
    }
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
    AnotherConcreteClass obj5{ 3.5 };
    obj5.method_first();
    obj5.method_second();

    // ---------------------------------------------

    Interface& obj01{ obj4 };
    obj01.method_first();
    obj01.method_second();
    // AbstractClass& obj02{ obj4 };        // Error
    AnotherAbstractClass& obj03{ obj4 };
    obj03.method_first();
    obj03.method_second();
    ConcreteClass obj04{ obj4 };
    obj04.method_first();
    obj04.method_second();
    AnotherConcreteClass obj05{ obj5 };
    obj05.method_first();
    obj05.method_second();

    // ---------------------------------------------

    Interface* obj001{ &obj4 };
    obj001->method_first();
    obj001->method_second();
    //  AbstractClass* obj002{ &obj4 };     // Error
    AnotherAbstractClass* obj003{ &obj4 };
    obj003->method_first();
    obj003->method_second();
    ConcreteClass* obj004{ &obj4 };
    obj004->method_first();
    obj004->method_second();
    AnotherConcreteClass* obj005{ &obj5 };
    obj005->method_first();
    obj005->method_second();
}

// ===========================================================================
// End-of-File
// ===========================================================================
