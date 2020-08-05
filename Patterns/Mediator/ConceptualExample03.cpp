// ===========================================================================
// ConceptualExample02.cpp // Mediator
// ===========================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

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

    class MediatorBaseAlternate {
    public:
        virtual ~MediatorBaseAlternate() {}
        virtual void notify(std::shared_ptr<ColleagueBase> sender) const = 0;
    };

    /**
     * The Base Component provides the basic functionality of storing a mediator's
     * instance inside component objects.
     */
    class ColleagueBase {
    protected:
        std::weak_ptr<MediatorBaseAlternate> m_mediator;

    public:
        // Important !!! Otherwise child classes like ConcreteColleagueA won't compile !!!
        ColleagueBase() = default;

        ColleagueBase(std::shared_ptr<MediatorBaseAlternate> mediator) : m_mediator(mediator) {}

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
        void DoA()
        {
            std::cout << "Component 1 does A." << std::endl;
            std::shared_ptr<MediatorBaseAlternate> sp = m_mediator.lock();
            sp->notify(shared_from_this());
        }

        void DoX()
        {
            std::cout << "Component 1 does X." << std::endl;
        }
    };

    class ConcreteColleagueB : public ColleagueBase, public std::enable_shared_from_this<ConcreteColleagueB> {
    public:

        void DoB()
        {
            std::cout << "Component 2 does B." << std::endl;
            std::shared_ptr<MediatorBaseAlternate> sp = m_mediator.lock();
            sp->notify(shared_from_this());
        }

        void DoY()
        {
            std::cout << "Component 2 does Y." << std::endl;
        }

        void DoZ()
        {
            std::cout << "Component 2 does Z." << std::endl;
        }
    };

    /**
     * Concrete Mediators implement cooperative behavior
     * by coordinating several components.
     */
    class ConcreteMediator : public MediatorBaseAlternate, public std::enable_shared_from_this<ConcreteMediator> {
    private:
        std::shared_ptr<ConcreteColleagueA> m_component1;
        std::shared_ptr<ConcreteColleagueB> m_component2;

    public:
        ConcreteMediator(std::shared_ptr<ConcreteColleagueA> c1, std::shared_ptr<ConcreteColleagueB> c2)
            : m_component1(c1), m_component2(c2) {}

        ~ConcreteMediator() {}

        void setConcreteColleagueA()
        {
            m_component1->setMediator(shared_from_this());
        }

        void setConcreteColleagueB()
        {
            m_component2->setMediator(shared_from_this());
        }

        void setConcreteColleagues()
        {
            m_component1->setMediator(shared_from_this());
            m_component2->setMediator(shared_from_this());
        }

        void notify(std::shared_ptr<ColleagueBase> sender) const override
        {
            if (sender == m_component1) {
                std::cout << "Mediator reacts on Component A and triggers following operations:" << std::endl;
                m_component1->DoX();
                m_component2->DoY();
            }

            if (sender == m_component2) {
                std::cout << "Mediator reacts on Component B and triggers following operations:" << std::endl;
                m_component1->DoX();
                m_component2->DoY();
                m_component2->DoZ();
            }
        }
    };

    void clientCode()
    {
        std::shared_ptr<ConcreteColleagueA> c1 = std::shared_ptr<ConcreteColleagueA>(new ConcreteColleagueA());
        std::shared_ptr<ConcreteColleagueB> c2 = std::shared_ptr<ConcreteColleagueB>(new ConcreteColleagueB());

        std::shared_ptr<ConcreteMediator> mediator = std::make_shared<ConcreteMediator>(c1, c2);

        // Note: this method call CANNOT be integrated into the c'tor call before:
        // the shared pointer object must be fully constructed before 'shared_from_this()'
        // may be called without runtime error !!!
        mediator->setConcreteColleagues();

        std::cout << "Client triggers operation A." << std::endl;
        c1->DoA();
        std::cout << std::endl;
        std::cout << "Client triggers operation D." << std::endl;
        c2->DoB();
    }
}

void test_conceptual_example03()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace ConceptualExample03;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
