// ===========================================================================
// ConceptualExample.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

#include <iostream>
#include <string>

namespace AbstractClassVsInterface {

    // interface declaration 
    class Interface
    {
    public:
        virtual ~Interface() {};

        virtual void method_first() = 0;             // only 'abstract' methods
        virtual void method_second() = 0;            // only 'abstract' methods
    };

    // abstract class declaration 
    class AbstractClass 
    {
    public:
        virtual ~AbstractClass() {}

        AbstractClass(std::string message)
            : m_message{ message }
        {}

        virtual void method_third() = 0;             // 'abstract' method

        virtual void method_fourth()                 // (virtual) method with implementation
        { 
            std::cout << m_message << std::endl;
        }

        void method_fifth() const                    // (final) method
        {
        }

    protected:
        std::string m_message;                       // some data
    };

    // abstract class inheriting from an interface 
    class AnotherAbstractClass : public Interface
    {
    public:
        AnotherAbstractClass(double value) : m_value { value } {}

        void method_first() override
        {
            std::cout << m_value << std::endl;
        }

    protected:
        double m_value;
    };

    // concrete class inheriting from an abstract class 
    class ConcreteClass : public AnotherAbstractClass
    {
    public:
        ConcreteClass() : ConcreteClass{ 1.0 } {}

        ConcreteClass(double value) 
            : AnotherAbstractClass{ value }, m_anotherValue{} {}

        ConcreteClass(double value1, double value2)
            : AnotherAbstractClass{ value1 }, m_anotherValue{ value2 } {}

        void method_second() override
        {
            std::cout << m_value << ", " << m_anotherValue << std::endl;
        }

    private:
        double m_anotherValue;
    };

    // concrete class inheriting directly from an interface 
    class AnotherConcreteClass : public Interface
    {
    public:
        AnotherConcreteClass() : m_oneMoreValue{ 1.0 } {}

        AnotherConcreteClass(double value) : m_oneMoreValue{ value } {}

        void method_first() override
        {
            std::cout << m_oneMoreValue << std::endl;
        }

        void method_second() override
        {
            method_first();
        }

        void my_method()
        {
        }

    private:
        double m_oneMoreValue;
    };

    // =======================================================================

    static Interface* getInterface()
    {
        AnotherConcreteClass* impl = new AnotherConcreteClass();
        // or
        // Interface* impl = new AnotherConcreteClass();

        return impl;
    }

    // =======================================================================

    static void test_client_of_interface()
    {
        Interface* ip = getInterface();

        ip->method_first();

        delete ip;
    }
}

// ===========================================================================

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

    // using references
    Interface& obj01{ obj4 };
    obj01.method_first();
    obj01.method_second();
    // AbstractClass& obj02{ obj4 };        // Error - no relationship with interface 'Interface'
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

    // using pointers
    Interface* obj001{ &obj4 };
    obj001->method_first();
    obj001->method_second();
    // AbstractClass* obj002{ &obj4 };     // Error
    AnotherAbstractClass* obj003{ &obj4 };
    obj003->method_first();
    obj003->method_second();
    ConcreteClass* obj004{ &obj4 };
    obj004->method_first();
    obj004->method_second();
    AnotherConcreteClass* obj005{ &obj5 };
    obj005->method_first();
    obj005->method_second();

    // ---------------------------------------------

    test_client_of_interface();
}

// ===========================================================================
// End-of-File
// ===========================================================================
