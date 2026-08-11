// ===========================================================================
// ConceptualExample01.cpp // Mediator
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

#include <memory>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExample01 {

    /**
     * The Mediator interface declares a method used by components to notify the
     * mediator about various events. The Mediator may react to these events and
     * pass the execution to other components.
     */

    enum class Event { A, B, C, D };

    class ColleagueBase;

    class MediatorBase {
    public:
        virtual ~MediatorBase() = default;

        virtual void notify(const ColleagueBase& sender, Event event) = 0;
    };

    /**
     * The Base Component provides the basic functionality of storing a mediator's
     * instance inside component objects.
     */
    class ColleagueBase 
    {
    private:
        std::string                 m_name;

    protected:
        std::weak_ptr<MediatorBase> m_mediator;

    public:
        ColleagueBase() = delete;

        explicit ColleagueBase(std::string name) : m_name{ std::move(name) } {}

        void setMediator(std::shared_ptr<MediatorBase> mediator)
        {
            m_mediator = std::move(mediator);
        }

        [[nodiscard]]
        std::string_view getName () const { return m_name; }
    };

    /**
     * Concrete Components implement various functionality. They don't depend on
     * other components. They also don't depend on any concrete mediator classes.
     */
    class ConcreteColleagueA : public ColleagueBase
    {
    public:
        explicit ConcreteColleagueA(const std::string& name) : ColleagueBase{ name } {}

        void operationA()
        {
            std::println("Component {} does operation A.", getName());
            
            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(*this, Event::A);
            }

            if (auto mediator = m_mediator.lock())
            {
                mediator->notify(*this, Event::A);
            }
        }

        void operationB()
        {
            std::println("Component {} does operation B.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(*this, Event::B);
            }

            if (auto mediator = m_mediator.lock())
            {
                mediator->notify(*this, Event::B);
            }
        }
    };

    class ConcreteColleagueB : public ColleagueBase
    {
    public:
        explicit ConcreteColleagueB(const std::string& name) : ColleagueBase{ name } {}

        void operationC()
        {
            std::println("Component {} does operation C.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(*this, Event::C);
            }

            if (auto mediator = m_mediator.lock())
            {
                mediator->notify(*this, Event::C);
            }
        }

        void operationD()
        {
            std::println("Component {} does operation D.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(*this, Event::D);
            }

            if (auto mediator = m_mediator.lock())
            {
                mediator->notify(*this, Event::D);
            }
        }
    };

    /**
     * Concrete Mediators implement cooperative behavior
     * by coordinating several components.
     */
    class ConcreteMediator : public MediatorBase
    {
    private:
        std::shared_ptr<ConcreteColleagueA> m_componentA;
        std::shared_ptr<ConcreteColleagueB> m_componentB;

    public:
        explicit ConcreteMediator(
            std::shared_ptr<ConcreteColleagueA> colleagueA,
            std::shared_ptr<ConcreteColleagueB> colleagueB)
            : m_componentA{ std::move(colleagueA) }, 
              m_componentB{ std::move(colleagueB) }
        {}

    public:
        // static Factory method to ensure proper initialization of this mediator
        static std::shared_ptr<ConcreteMediator> create(
            std::shared_ptr<ConcreteColleagueA> cA,
            std::shared_ptr<ConcreteColleagueB> cB)
        {
            auto mediator = std::make_shared<ConcreteMediator>(cA, cB);

            cA->setMediator(mediator);
            cB->setMediator(mediator);

            return mediator;
        }

    public:
        ~ConcreteMediator() = default;

        void notify(const ColleagueBase& sender, Event event) override
        {
            std::println("Notify => Sender: {}", sender.getName());

            switch (event) {
            case Event::A:
                std::println("Mediator reacts on A and triggers following operations:");
                m_componentB->operationC();
                break;
            case Event::D:
                std::println("Mediator reacts on D and triggers following operations:");
                m_componentA->operationB();
                m_componentB->operationC();
                break;
            case Event::B:
            case Event::C:
                break;
            }
        }
    };

    static void clientCode()
    {
        auto cA = std::make_shared<ConcreteColleagueA>("Colleague A");
        auto cB = std::make_shared<ConcreteColleagueB>("Colleague B");

        auto mediator = ConcreteMediator::create(cA, cB);

        std::println("Client triggers operation A.");
        cA->operationA();
        std::println();

        std::println("Client triggers operation D.");
        cB->operationD();
    }
}

void test_conceptual_example01()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace ConceptualExample01;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
