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
        virtual ~ISubject() {};
        virtual void attach(IObserver* observer) = 0;
        virtual void detach(IObserver* observer) = 0;
        virtual void notify() = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state and notifies observers
     * when the state changes.
     */

    class Subject : public ISubject {
    private:
        std::list<IObserver*> m_list_observers;
        std::string m_message;

    public:
        virtual ~Subject() {
            std::cout << "Goodbye, I was the Subject.\n";
        }

        /**
         * The subscription management methods.
         */
        void attach(IObserver* observer) override {
            m_list_observers.push_back(observer);
        }

        void detach(IObserver* observer) override {
            m_list_observers.remove(observer);
        }

        void notify() override {
            howManyObservers();
            for (const auto& observer : m_list_observers) {
                observer->update(m_message);
            }
        }

        void createMessage(std::string message = "<empty>") {
            m_message = message;
            notify();
        }

        void howManyObservers() {
            std::cout << "There are " << m_list_observers.size() << " observers in the list.\n";
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
    };

    // =======================================================================

    class Observer : public IObserver {
    private:
        std::string m_messageFromSubject;
        Subject& m_subject;
        static int m_static_number;
        int m_number;

    public:
        Observer(Subject& subject) : m_subject{ subject } 
        {
            m_subject.attach(this);
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
            m_subject.detach(this);
            std::cout 
                << "Observer \"" << m_number 
                << "\" removed from the list.\n";
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

    void clientCode()
    {
        Subject* subject{ new Subject };

        Observer* observer1 { new Observer{ *subject } };
        Observer* observer2 { new Observer{ *subject } };
        Observer* observer3 { new Observer{ *subject } };

        subject->createMessage("Hello World! :D");
        observer3->removeMeFromTheList();

        subject->createMessage("The weather is hot today! :p");
        Observer* observer4 = new Observer{ *subject };

        observer2->removeMeFromTheList();
        Observer* observer5 = new Observer{ *subject };

        subject->createMessage("My new car is great! ;)");
        observer5->removeMeFromTheList();

        subject->someBusinessLogic();

        observer4->removeMeFromTheList();
        observer1->removeMeFromTheList();

        delete observer5;
        delete observer4;
        delete observer3;
        delete observer2;
        delete observer1;
        delete subject;
    }
}

void test_conceptual_example_01() {
    using namespace ObserverDesignPatternClassic;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
