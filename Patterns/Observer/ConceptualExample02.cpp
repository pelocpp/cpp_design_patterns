// ===========================================================================
// ConceptualExample02.cpp // Observer // Variant 2
// ===========================================================================

/**
 * Observer Design Pattern
 */

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <memory>

namespace ObserverDesignPatternSmartPointer {

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
            std::cout << "Goodbye, I was the Subject.\n";
        }

        /**
         * subscription management methods.
         */
        void attach(std::weak_ptr<IObserver> observer) override {
            m_observers.push_back(observer);
        }

        void detach(std::weak_ptr<IObserver> observer) override {

            // https://stackoverflow.com/questions/10120623/removing-item-from-list-of-weak-ptrs

            m_observers.remove_if([&](std::weak_ptr<IObserver> wp) {
                return !observer.owner_before(wp) && !wp.owner_before(observer);
                }
            );
        }

        void createMessage(std::string message = "<empty>") {
            m_message = message;
            notify();
        }

        void howManyObservers() {
            std::cout << "There are " << m_observers.size() << " observers in the list.\n";
        }

        /**
         * Usually, the subscription logic is only a fraction of what a Subject can
         * really do. Subjects commonly hold some important business logic, that
         * triggers a notification method whenever something important is about to
         * happen (or after it).
         */
        void someBusinessLogic() {
            m_message = "changing this message";
            notify();
            std::cout << "I'm about to do some important things" << std::endl;
        }

    private:
        void notify() {
            howManyObservers();
            for (std::weak_ptr<IObserver>& weakPtr : m_observers) {
                std::shared_ptr<IObserver> sharedPtr{ weakPtr.lock() };
                if (sharedPtr != nullptr) {
                    sharedPtr->update(m_message);
                }
            }
        }
    };

    // ===========================================================================

    class Observer : public IObserver {
    private:
        std::string m_messageFromSubject;
        static int m_static_number;
        int m_number;

    public:
        Observer() 
        {
            std::cout << "Hi, I'm the Observer \"" << ++Observer::m_static_number << "\".\n";
            m_number = Observer::m_static_number;
        }

        virtual ~Observer() 
        {
            std::cout << "Goodbye, I was the Observer \"" << m_number << "\".\n";
        }

        void update(const std::string& messageFromSubject) override
        {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void printInfo() const
        {
            std::cout 
                << "Observer \"" << m_number 
                << "\": a new message is available --> " 
                << m_messageFromSubject << "\n";
        }
    };

    int Observer::m_static_number = 0;

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

    static void clientCode_02() {

        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };

        subject->attach(observer1);
        subject->attach(observer2);

        {
            std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };
            subject->attach(observer3);
            subject->createMessage("Hello World!");
        }

        // Note: Watch contents of 'm_observers' list

        subject->createMessage("Hello World Again");

        subject->detach(observer1);
        subject->detach(observer2);
    }
}

// ===========================================================================

void test_conceptual_example_02()
{
    ObserverDesignPatternSmartPointer::clientCode_01();
    ObserverDesignPatternSmartPointer::clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
