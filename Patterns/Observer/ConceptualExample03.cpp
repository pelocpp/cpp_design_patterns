// ===========================================================================
// ConceptualExample03.cpp // Observer // Variant 3
// ===========================================================================

/**
 * Observer Design Pattern
 */

#include <list>
#include <memory>
#include <print>
#include <string>

namespace ObserverDesignPatternSmartPointerEx {

    class IObserver {
    public:
        virtual ~IObserver() {}

        virtual void update(const std::string&) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() {}

        virtual void attach(std::weak_ptr<IObserver>) = 0;
        virtual void detach(std::weak_ptr<IObserver>) = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state and notifies observers
     * when the state changes.
     */

    class Subject : public ISubject {
    private:
        std::list<std::weak_ptr<IObserver>> m_observers;
        std::string                         m_message;

    public:
        virtual ~Subject() {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods.
         */
        void attach(std::weak_ptr<IObserver> observer) override {
            m_observers.push_back(observer);
        }

        void detach(std::weak_ptr<IObserver> observer) override {
            m_observers.remove_if([&](std::weak_ptr<IObserver> wp) {
                return !observer.owner_before(wp) && !wp.owner_before(observer);
                }
            );
        }

        void createMessage(const std::string& message) {
            m_message = message;
            notify();
        }

        /**
         * Usually, the subscription logic is only a fraction of what a Subject can
         * really do. Subjects commonly hold some important business logic, that
         * triggers a notification method whenever something important is about to
         * happen (or after it).
         */
        void someBusinessLogic() {
            std::println("Subject: changing state ...");
            m_message = "changing this message";
            notify();
        }

    private:
        void notify() const {
            for (const std::weak_ptr<IObserver>& weakPtr : m_observers) {
                std::shared_ptr<IObserver> sharedPtr{ weakPtr.lock() };
                if (sharedPtr != nullptr) {
                    sharedPtr->update(m_message);
                }
            }
        }
    };

    // ===========================================================================

    class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
    private:
        std::shared_ptr<Subject> m_subject;
        std::string              m_messageFromSubject;
        static int               m_count;
        int                      m_number;

    public:
        Observer() : m_subject{ nullptr }
        {
            ++Observer::m_count;
            std::println("Observer: {}", Observer::m_count);
            m_number = Observer::m_count;
        }

        Observer(std::shared_ptr<Subject> subject) : m_subject{ subject } 
        {
            ++Observer::m_count;
            std::println("Observer: {}", Observer::m_count);
            m_number = Observer::m_count;
        }

        virtual ~Observer()
        {
            std::println("d'tor Observer ({})", m_number);
        }

        void update(const std::string& messageFromSubject) override
        {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void removeMeFromTheList() 
        {
            if (m_subject != nullptr) {
                try {
                    std::shared_ptr<Observer> me{ shared_from_this() };
                    m_subject->detach(me);
                    std::println("Observer {} removed from the list.", m_number);
                }
                catch (const std::exception& ex) {
                    std::println("Exception: {}", ex.what());
                }
            }
        }

        void printInfo() const {
            std::println("Observer: new message is available --> \"{}\"", m_messageFromSubject);
        }
    };

    int Observer::m_count = 0;

    static void clientCode_01() {

        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };

        subject->attach(observer1);
        subject->attach(observer2);
        subject->attach(observer3);

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        subject->detach(observer1);
        subject->detach(observer2);
        subject->detach(observer3);
    }

    static void clientCode_02()
    {
        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<Observer> observer1{ std::make_shared<Observer>(subject) };
        std::shared_ptr<Observer> observer2{ std::make_shared<Observer>(subject) };
        std::shared_ptr<Observer> observer3{ std::make_shared<Observer>(subject) };

        subject->attach(observer1);
        subject->attach(observer2);
        subject->attach(observer3);

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        observer1->removeMeFromTheList();
        observer2->removeMeFromTheList();
        observer3->removeMeFromTheList();
    }
}

// ===========================================================================

void test_conceptual_example_03()
{
    ObserverDesignPatternSmartPointerEx::clientCode_01();
    ObserverDesignPatternSmartPointerEx::clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
