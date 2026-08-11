// ===========================================================================
// ConceptualExample01.cpp // Mediator
// ===========================================================================

#include <memory>
#include <print>
#include <string>

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

        virtual void notify(const std::shared_ptr<ColleagueBase>& sender, Event event) const = 0;
    };

    /**
     * The Base Component provides the basic functionality of storing a mediator's
     * instance inside component objects.
     */
    class ColleagueBase 
    {
    protected:
        std::string                 m_name;
        std::weak_ptr<MediatorBase> m_mediator;

    public:
        ColleagueBase() = delete;

        explicit ColleagueBase(const std::string& name) : m_name{ name } {}

        void setMediator(const std::shared_ptr<MediatorBase>& mediator)
        {
            m_mediator = mediator;
        }

        const std::string& getName () const { return m_name; }
    };

    /**
     * Concrete Components implement various functionality. They don't depend on
     * other components. They also don't depend on any concrete mediator classes.
     */
    class ConcreteColleagueA 
        : public ColleagueBase,
          public std::enable_shared_from_this<ConcreteColleagueA> 
    {
    public:
        explicit ConcreteColleagueA(const std::string& name) : ColleagueBase{ name } {}

        void operationA()
        {
            std::println("Component {} does operation A.", getName());
            
            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(shared_from_this(), Event::A);
            }
        }

        void operationB()
        {
            std::println("Component {} does operation B.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(shared_from_this(), Event::B);
            }
        }
    };

    class ConcreteColleagueB 
        : public ColleagueBase, 
          public std::enable_shared_from_this<ConcreteColleagueB>
    {
    public:
        explicit ConcreteColleagueB(const std::string& name) : ColleagueBase{ name } {}

        void operationC()
        {
            std::println("Component {} does operation C.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(shared_from_this(), Event::C);
            }
        }

        void operationD()
        {
            std::println("Component {} does operation D.", getName());

            std::shared_ptr<MediatorBase> sp{ m_mediator.lock() };
            if (sp != nullptr) {
                sp->notify(shared_from_this(), Event::D);
            }
        }
    };

    /**
     * Concrete Mediators implement cooperative behavior
     * by coordinating several components.
     */
    class ConcreteMediator 
        : public MediatorBase,
          public std::enable_shared_from_this<ConcreteMediator> 
    {
    private:
        std::shared_ptr<ConcreteColleagueA> m_componentA;
        std::shared_ptr<ConcreteColleagueB> m_componentB;

        ConcreteMediator(
            std::shared_ptr<ConcreteColleagueA> colleagueA,
            std::shared_ptr<ConcreteColleagueB> colleagueB)
            : m_componentA{ std::move(colleagueA) }, m_componentB{ std::move(colleagueB) }
        {}

        void setConcreteColleagues()
        {
            m_componentA->setMediator(shared_from_this());
            m_componentB->setMediator(shared_from_this());
        }

    public:
        // static Factory method to ensure proper initialization of this mediator
        static std::shared_ptr<ConcreteMediator> create(
            std::shared_ptr<ConcreteColleagueA> a,
            std::shared_ptr<ConcreteColleagueB> b)
        {
            auto mediator = std::shared_ptr<ConcreteMediator>(new ConcreteMediator(std::move(a), std::move(b)));
            mediator->setConcreteColleagues();
            return mediator;
        }

    public:
        ~ConcreteMediator() = default;

        void notify(const std::shared_ptr<ColleagueBase>& sender, Event event) const override
        {
            std::println("Notify => Sender: {}", sender->getName());

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
    using namespace ConceptualExample01;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
