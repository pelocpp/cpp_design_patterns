// ===========================================================================
// ConceptualExample02.cpp // Mediator
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample03 {

    /**
     * The Mediator interface declares a method used by components to notify the
     * mediator about various events. The Mediator may react to these events and
     * pass the execution to other components.
     */
    class ColleagueBase;

    class MediatorBaseAlternate 
    {
    public:
        virtual ~MediatorBaseAlternate() {}
        virtual void notify(std::shared_ptr<ColleagueBase> sender) const = 0;
    };

    /**
     * The Base Component provides the basic functionality of storing a mediator's
     * instance inside component objects.
     */
    class ColleagueBase 
    {
    protected:
        std::weak_ptr<MediatorBaseAlternate> m_mediator;

    public:
        ColleagueBase() = default;

        ColleagueBase(std::shared_ptr<MediatorBaseAlternate> mediator) 
            : m_mediator{ mediator } {}

        void setMediator(std::shared_ptr<MediatorBaseAlternate> mediator)
        {
            m_mediator = mediator;
        }
    };

    /**
     * Concrete Components implement various functionality. They don't depend on
     * other components. They also don't depend on any concrete mediator classes.
     */
    class ConcreteColleagueA : public ColleagueBase, public std::enable_shared_from_this<ConcreteColleagueA> {
    public:
        void operationA()
        {
            std::cout << "Component Colleague A does operation A." << std::endl;
            std::shared_ptr<MediatorBaseAlternate> sp = m_mediator.lock();
            sp->notify(shared_from_this());
        }

        void operationX()
        {
            std::cout << "Component Colleague A does operation X." << std::endl;
        }
    };

    class ConcreteColleagueB : public ColleagueBase, public std::enable_shared_from_this<ConcreteColleagueB> 
    {
    public:

        void operationB()
        {
            std::cout << "Component Colleague B does operation B." << std::endl;
            std::shared_ptr<MediatorBaseAlternate> sp = m_mediator.lock();
            sp->notify(shared_from_this());
        }

        void operationY()
        {
            std::cout << "Component Colleague B does operation Y." << std::endl;
        }

        void operationZ()
        {
            std::cout << "Component Colleague B does operation Z." << std::endl;
        }
    };

    /**
     * Concrete Mediators implement cooperative behavior
     * by coordinating several components.
     */
    class ConcreteMediator : public MediatorBaseAlternate, public std::enable_shared_from_this<ConcreteMediator> 
    {
    private:
        std::shared_ptr<ConcreteColleagueA> m_componentA;
        std::shared_ptr<ConcreteColleagueB> m_componentB;

    public:
        ConcreteMediator(std::shared_ptr<ConcreteColleagueA> c1, std::shared_ptr<ConcreteColleagueB> c2)
            : m_componentA{ c1 }, m_componentB{ c2 } {}

        ~ConcreteMediator() {}

        void setConcreteColleagueA()
        {
            m_componentA->setMediator(shared_from_this());
        }

        void setConcreteColleagueB()
        {
            m_componentB->setMediator(shared_from_this());
        }

        void setConcreteColleagues()
        {
            m_componentA->setMediator(shared_from_this());
            m_componentB->setMediator(shared_from_this());
        }

        void notify(std::shared_ptr<ColleagueBase> sender) const override
        {
            if (sender == m_componentA) {
                std::cout << "Mediator reacts on Component A and triggers following operations:" << std::endl;
                m_componentA->operationX();
                m_componentB->operationY();
            }

            if (sender == m_componentB) {
                std::cout << "Mediator reacts on Component B and triggers following operations:" << std::endl;
                m_componentA->operationX();
                m_componentB->operationY();
                m_componentB->operationZ();
            }
        }
    };

    void clientCode()
    {
        std::shared_ptr<ConcreteColleagueA> c1{ 
            new ConcreteColleagueA()
        };
        
        std::shared_ptr<ConcreteColleagueB> c2{ 
            new ConcreteColleagueB()
        };

        std::shared_ptr<ConcreteMediator> mediator{ 
            std::make_shared<ConcreteMediator>(c1, c2) 
        };

        // Note: this method call CANNOT be integrated into the c'tor call before:
        // the shared pointer object must be fully constructed before 'shared_from_this()'
        // may be called without runtime error !!!
        mediator->setConcreteColleagues();

        std::cout << "Client triggers operation A." << std::endl;
        c1->operationA();
        std::cout << std::endl;
        std::cout << "Client triggers operation D." << std::endl;
        c2->operationB();
    }
}

void test_conceptual_example03()
{
    using namespace ConceptualExample03;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
