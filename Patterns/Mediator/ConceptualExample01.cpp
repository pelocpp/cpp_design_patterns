// ===========================================================================
// ConceptualExample01.cpp // Mediator
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample01 {

    /**
     * The Mediator interface declares a method used by components to notify the
     * mediator about various events. The Mediator may react to these events and
     * pass the execution to other components.
     */
    class ColleagueBase;

    class MediatorBase 
    {
    public:
        virtual void notify(ColleagueBase* sender, std::string event) const = 0;
    };

    /**
     * The Base Component provides the basic functionality
     * of storing a mediator's instance inside component objects.
     */
    class ColleagueBase 
    {
    protected:
        MediatorBase* m_mediator;

    public:
        ColleagueBase(MediatorBase* mediator = nullptr) 
            : m_mediator{ mediator } {}

        void setMediator(MediatorBase* mediator) 
        {
            m_mediator = mediator;
        }
    };

    /**
     * Concrete Components implement various functionality. They don't depend on
     * other components. They also don't depend on any concrete mediator classes.
     */
    class ConcreteColleagueA : public ColleagueBase 
    {
    public:
        void operationA() 
        {
            std::cout << "Component 1 does operation A." << std::endl;
            m_mediator->notify(this, "A");
        }

        void operationB()
        {
            std::cout << "Component 1 does operation B." << std::endl;
            m_mediator->notify(this, "B");
        }
    };

    class ConcreteColleagueB : public ColleagueBase 
    {
    public:
        void operationC()
        {
            std::cout << "Component 2 does operation C." << std::endl;
            m_mediator->notify(this, "C");
        }

        void operationD()
        {
            std::cout << "Component 2 does operation D." << std::endl;
            m_mediator->notify(this, "D");
        }
    };

    /**
     * Concrete Mediators implement cooperative behavior
     * by coordinating several components.
     */
    class ConcreteMediator : public MediatorBase 
    {
    private:
        ConcreteColleagueA* m_component1;
        ConcreteColleagueB* m_component2;

    public:
        ConcreteMediator(ConcreteColleagueA* c1, ConcreteColleagueB* c2) 
            : m_component1{ c1 }, m_component2{ c2 }
        {
            m_component1->setMediator(this);
            m_component2->setMediator(this);
        }

        void notify(ColleagueBase* sender, std::string event) const override
        {
            if (event == "A")
            {
                std::cout << "Mediator reacts on operation A and triggers following operations:" << std::endl;
                m_component2->operationC();
            }

            if (event == "D")
            {
                std::cout << "Mediator reacts on operation D and triggers following operations:" << std::endl;
                m_component1->operationB();
                m_component2->operationC();
            }
        }
    };

    void clientCode()
    {
        ConcreteColleagueA* c1{ new ConcreteColleagueA{} };
        ConcreteColleagueB* c2{ new ConcreteColleagueB{} };
        ConcreteMediator* mediator{ new ConcreteMediator(c1, c2) };

        std::cout << "Client triggers operation A." << std::endl;
        c1->operationA();
        std::cout << std::endl;
        std::cout << "Client triggers operation D." << std::endl;
        c2->operationD();

        delete c1;
        delete c2;
        delete mediator;
    }
}

void test_conceptual_example01()
{
    using namespace ConceptualExample01;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
