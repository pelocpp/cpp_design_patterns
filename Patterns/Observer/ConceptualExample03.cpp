// ===========================================================================
// ConceptualExample.cpp // Observer // Variant 3
// ===========================================================================

#include <iostream>

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
#include <memory>

namespace ObserverDesignPatternSmartPointerEx {

    class IObserver {
    public:
        virtual ~IObserver() {};
        virtual void update(const std::string&) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() {};
        virtual void attach(std::shared_ptr<IObserver>) = 0;
        virtual void detach(std::shared_ptr<IObserver>) = 0;
        virtual void notify() = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state and notifies observers
     * when the state changes.
     */

    class Subject : public ISubject {
    private:
        std::list<std::shared_ptr<IObserver>> m_list_observers;
        std::string m_message;

    public:
        virtual ~Subject() {
            std::cout << "Goodbye, I was the Subject.\n";
        }

        /**
         * subscription management methods.
         */
        void attach(std::shared_ptr<IObserver> observer) override {
            m_list_observers.push_back(observer);
        }

        void detach(std::shared_ptr<IObserver> observer) override {
            m_list_observers.remove(observer);
        }

        void notify() override {
            std::list<std::shared_ptr<IObserver>>::iterator iterator = m_list_observers.begin();
            howManyObserver();
            while (iterator != m_list_observers.end()) {
                (*iterator)->update(m_message);
                ++iterator;
            }
        }

        void createMessage(std::string message = "<empty>") {
            m_message = message;
            notify();
        }

        void howManyObserver() {
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

    // ===========================================================================

    class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
    private:
        std::string m_messageFromSubject;
        std::shared_ptr<Subject> m_subject;
        static int m_static_number;
        int m_number;

    public:
        Observer(std::shared_ptr<Subject> subject) : m_subject(subject) {
            std::cout << "Hi, I'm the Observer \"" << ++Observer::m_static_number << "\".\n";
            m_number = Observer::m_static_number;
        }

        virtual ~Observer() {
            std::cout << "Goodbye, I was the Observer \"" << m_number << "\".\n";
        }

        void update(const std::string& m_messagefrom_subject) override {
            m_messageFromSubject = m_messagefrom_subject;
            printInfo();
        }

        void removeMeFromTheList() {
            try
            {
                std::shared_ptr<Observer> me = shared_from_this();
                m_subject->detach(me);
                std::cout << "Observer \"" << m_number << "\" removed from the list.\n";
            }
            catch (const std::exception& ex) {
                std::cout << "exception: " << ex.what() << "\".\n";
            }
        }

        void printInfo() {
            std::cout << "Observer \"" << m_number << "\": a new message is available --> " << m_messageFromSubject << "\n";
        }
    };

    int Observer::m_static_number = 0;

    void clientCode() {

        std::shared_ptr<Subject> subject = std::make_shared<Subject>();

        std::shared_ptr<Observer> observer1 = std::make_shared<Observer>(subject);
        subject->attach(observer1);

        std::shared_ptr<Observer> observer2 = std::make_shared<Observer>(subject);
        subject->attach(observer2);

        std::shared_ptr<Observer> observer3 = std::make_shared<Observer>(subject);
        subject->attach(observer3);

        subject->createMessage("Hello World! :D");
        observer3->removeMeFromTheList();

        subject->createMessage("The weather is hot today! :p");
        std::shared_ptr<Observer> observer4 = std::make_shared<Observer>(subject);
        subject->attach(observer4);

        observer2->removeMeFromTheList();

        std::shared_ptr<Observer> observer5 = std::make_shared<Observer>(subject);
        subject->attach(observer5);

        subject->createMessage("My new car is great! ;)");

        observer5->removeMeFromTheList();

        subject->someBusinessLogic();

        observer4->removeMeFromTheList();
        observer1->removeMeFromTheList();
    }
}

// ===========================================================================

void test_conceptual_example_03() {
    using namespace ObserverDesignPatternSmartPointerEx;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
