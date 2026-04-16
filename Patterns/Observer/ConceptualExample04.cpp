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
        virtual ~Subject() noexcept {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods.
         */

        std::size_t attach(std::function<void(const std::string&)> observer) {
            static std::size_t nextId = 0;
            std::size_t id = nextId++;
            m_observers.emplace(id, std::move(observer));
            return id;  // return the ID for later detachment
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
            for (const auto& observer : m_observers) {
                const auto& [id, callback] = observer;
                callback(m_message);
            }
        }
    };

    // ===========================================================================

    class Observer {
    private:
        std::string m_messageFromSubject;
        std::size_t m_number;

    public:
        Observer() {
            static std::size_t nextNumber = 0;
            m_number = nextNumber++;
            std::println("Observer: {}", m_number);
        }

        virtual ~Observer() noexcept {
            std::println("d'tor Observer ({})", m_number);
        }

        void update(const std::string& messageFromSubject) {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void printInfo() const {
            std::println("Observer ({}): new message is available --> \"{}\"",
                m_number, m_messageFromSubject);
        }
    };

    static void clientCode_01() {

        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<Observer> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer3{ std::make_shared<Observer>() };

        // Version 1:
        // Connect sink to source without intermediary lambda, need to use std::bind
        auto callback1{ std::bind(&Observer::update, observer1, std::placeholders::_1) };
        auto callback2{ std::bind(&Observer::update, observer2, std::placeholders::_1) };
        auto callback3{ std::bind(&Observer::update, observer3, std::placeholders::_1) };

        // Store the returned IDs
        auto id1{ subject->attach(callback1) };
        auto id2{ subject->attach(callback2) };
        auto id3{ subject->attach(callback3) };

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        // Use the returned IDs for detachment
        subject->detach(id1);
        subject->detach(id2);
        subject->detach(id3);
    }

    static void clientCode_02()
    {
        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<Observer> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<Observer> observer3{ std::make_shared<Observer>() };

        auto handler1{ [=](const std::string& msg) { observer1->update(msg); } };
        auto handler2{ [=](const std::string& msg) { observer2->update(msg); } };
        auto handler3{ [=](const std::string& msg) { observer3->update(msg); } };

        // Version 2:
        // Lambdas connect sink to source (storing the returned IDs)
        auto id1{ subject->attach(handler1) };
        auto id2{ subject->attach(handler2) };
        auto id3{ subject->attach(handler3) };

        subject->createMessage("Hello World!");
        subject->createMessage("Hello World Again");

        // Use the returned IDs for detachment
        subject->detach(id1);
        subject->detach(id2);
        subject->detach(id3);
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
