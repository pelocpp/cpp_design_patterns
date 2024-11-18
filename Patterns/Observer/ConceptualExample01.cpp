// ===========================================================================
// ConceptualExample01.cpp // Observer // Variant 1
// ===========================================================================

/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>

namespace ObserverDesignPatternClassic {

    class IObserver {
    public:
        virtual ~IObserver() {};

        virtual void update(const std::string& messageFromSubject) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() {}

        virtual void attach(IObserver* observer) = 0;
        virtual void detach(IObserver* observer) = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state and notifies observers
     * when the state changes.
     */

    class Subject : public ISubject {
    private:
        std::list<IObserver*> m_observers;
        std::string           m_message;

    public:
        virtual ~Subject() {
            std::cout << "Goodbye, I was the Subject.\n";
        }

        /**
         * The subscription management methods.
         */
        void attach(IObserver* observer) override {
            m_observers.push_back(observer);
        }

        void detach(IObserver* observer) override {
            m_observers.remove(observer);
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
            for (const auto& observer : m_observers) {
                observer->update(m_message);
            }
        }
    };

    // =======================================================================

    class Observer : public IObserver {
    private:
        Subject*    m_subject;
        std::string m_messageFromSubject;
        int         m_number;
        static int  m_static_number;

    public:
        Observer() {
            m_subject = nullptr;
            std::cout << "Hi, I'm the Observer \"" << ++Observer::m_static_number << "\".\n";
            m_number = Observer::m_static_number;
        }

        // Information of 'subject' needed
        // to demonstrate 'removeMeFromTheList' method

        Observer(Subject* subject) : m_subject{ subject } {
            m_subject->attach(this);
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

        void removeMeFromTheList() 
        {
            if (m_subject != nullptr) {
                m_subject->detach(this);
                std::cout
                    << "Observer \"" << m_number
                    << "\" removed from the list.\n";
            }
        }

        void printInfo() 
        {
            std::cout 
                << "Observer \"" << m_number 
                << "\": a new message is available --> " 
                << m_messageFromSubject << "\n";
        }
    };

    int Observer::m_static_number = 0;

    static void clientCode_01()
    {
        Subject* subject{ new Subject };

        Observer* observer1{ new Observer{} };
        Observer* observer2{ new Observer{} };
        Observer* observer3{ new Observer{} };

        subject->attach(observer1);
        subject->attach(observer2);
        subject->attach(observer3);

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        subject->detach(observer1);
        subject->detach(observer2);
        subject->detach(observer3);

        delete observer3;
        delete observer2;
        delete observer1;
        delete subject;
    }

    static void clientCode_02()
    {
        Subject* subject{ new Subject };

        Observer* observer1{ new Observer{subject} };
        Observer* observer2{ new Observer{subject} };
        Observer* observer3{ new Observer{subject} };

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        observer1->removeMeFromTheList();
        observer2->removeMeFromTheList();
        observer3->removeMeFromTheList();

        delete observer3;
        delete observer2;
        delete observer1;
        delete subject;
    }
}

void test_conceptual_example_01() {
    ObserverDesignPatternClassic::clientCode_01();
    ObserverDesignPatternClassic::clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
