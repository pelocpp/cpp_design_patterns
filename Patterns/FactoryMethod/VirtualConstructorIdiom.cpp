// ===========================================================================
// VirtualConstructor.cpp // Factory Method // Virtual Constructor Idiom
// ===========================================================================

#include <iostream>
#include <string>

namespace VirtualConstructorIdiom {

    class Base
    {
    public:
        Base() {}
        virtual ~Base() {}

        // the "Virtual Constructor"
        static Base* Create(int id);

        // the "Virtual Copy Constructor"
        virtual Base* Clone() = 0;

        virtual void printMe() = 0;
    };

    class Derived1 : public Base
    {
    public:
        Derived1()
        {
            std::cout << "default c'tor Derived1" << std::endl;
        }

        Derived1(const Derived1& rhs)
        {
            std::cout << "copy c'tor Derived1" << std::endl;
        }

        ~Derived1()
        {
            std::cout << "c'tor Derived1" << std::endl;
        }

        Base* Clone() override
        {
            return new Derived1(*this);
        }

        void printMe()
        {
            std::cout << "I'm a Derived1" << std::endl;
        }
    };

    class Derived2 : public Base
    {
    public:
        Derived2()
        {
            std::cout << "default c'tor Derived2" << std::endl;
        }

        Derived2(const Derived1& rhs)
        {
            std::cout << "copy c'tor Derived2" << std::endl;
        }

        ~Derived2()
        {
            std::cout << "c'tor Derived2" << std::endl;
        }

        Base* Clone() override
        {
            return new Derived2(*this);
        }

        void printMe()
        {
            std::cout << "I'm a Derived2" << std::endl;
        }
    };

    Base* Base::Create(int id)
    {
        if (id == 1)
        {
            return new Derived1();
        }
        else
        {
            return new Derived2();
        }
    }

    Base* CreateCopy(Base* pBase)
    {
        return pBase->Clone();
    }
}

void test_virtual_constructor_idiom()
{
    using namespace VirtualConstructorIdiom;

    std::cout << "Enter Id (1 or 2): ";
    int input;
    std::cin >> input;
    Base* pBase = Base::Create(input);
    Base* pCopy = CreateCopy(pBase);

    // dont know what object is created but still access functions through base pointer
    pBase->printMe();
    pCopy->printMe();

    delete pBase;
    delete pCopy;
}

// ===========================================================================
// End-of-File
// ===========================================================================
