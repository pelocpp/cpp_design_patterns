// ===========================================================================
// ConceptualExample04.cpp // Observer // Variant 4 // std::function
// ===========================================================================

/**
 * Observer Design Pattern
 */

#include <cstddef>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <unordered_map>

namespace ObserverDesignPatternStdFunction {

    /**
     * The Subject owns some important state and notifies observers
     * when the state changes.
     */

    class Subject
    {
    private:
        std::unordered_map<std::size_t, std::function<void(const std::string&)>> m_observers;
        std::string m_message;

    public:
        virtual ~Subject() {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods.
         */
        void attach(std::size_t id, std::function<void(const std::string&)> observer) {
            m_observers.insert({ id, observer });
        }

        void detach(std::size_t id) {
             m_observers.erase(id);
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
            for (const auto& elem : m_observers) {
                const auto& [id, callback] = elem;
                callback(m_message);
            }
        }
    };

    // ===========================================================================

    class Observer {
    private:
        std::string m_messageFromSubject;
        static int  m_count;
        int         m_number;

    public:
        Observer()
        {
            ++Observer::m_count;
            std::println("Observer: {}", Observer::m_count);
            m_number = Observer::m_count;
        }

        virtual ~Observer()
        {
            std::println("d'tor Observer ({})", m_number);
        }

        void update(const std::string& messageFromSubject)
        {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void printInfo() const {
            std::println("Observer: new message is available --> \"{}\"", m_messageFromSubject);
        }
    };

    int Observer::m_count = 0;

    static void clientCode_01() {

        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<Observer> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer3{ std::make_shared<Observer>() };

        // Version 1: connect sink to source without intermediary lambda
        // need to use std::bind
        auto callback1 = std::bind(&Observer::update, observer1, std::placeholders::_1);
        auto callback2 = std::bind(&Observer::update, observer2, std::placeholders::_1);
        auto callback3 = std::bind(&Observer::update, observer3, std::placeholders::_1);

        subject->attach(1, callback1);
        subject->attach(2, callback2);
        subject->attach(3, callback3);

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        subject->detach(1);
        subject->detach(2);
        subject->detach(3);
    }

    static void clientCode_02()
    {
        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<Observer> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer3{ std::make_shared<Observer>() };

        auto handler1 = [&](const std::string& msg) { observer1->update(msg); };
        auto handler2 = [&](const std::string& msg) { observer1->update(msg); };
        auto handler3 = [&](const std::string& msg) { observer1->update(msg); };

        // Version 2: lambda connects sink to source
        subject->attach(1, handler1);
        subject->attach(2, handler2);
        subject->attach(3, handler3);

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        subject->detach(1);
        subject->detach(2);
        subject->detach(3);
    }
}

// ===========================================================================

void test_conceptual_example_04()
{
    ObserverDesignPatternStdFunction::clientCode_01();
    ObserverDesignPatternStdFunction::clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
