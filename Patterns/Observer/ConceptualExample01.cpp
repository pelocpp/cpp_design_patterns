// ===========================================================================
// ConceptualExample01.cpp // Observer // Variant 1
// ===========================================================================

/**
 * Observer Design Pattern
 */

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <map>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace ConceptualExample_Observer_Pattern {

    class IObserver {
    public:
        virtual ~IObserver() = default;

        virtual void update(std::string_view message) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() = default;

        virtual void attach(std::weak_ptr<IObserver> observer) = 0;
        virtual void detach(std::weak_ptr<IObserver> observer) = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state
     * and notifies observers when the state changes.
     */

    class Subject : public ISubject {
    private:
        std::vector<std::weak_ptr<IObserver>> m_observers;
        std::string                           m_message;

    public:
        ~Subject() override {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods
         */
        void attach(std::weak_ptr<IObserver> observer) override {
            m_observers.push_back(std::move(observer));
        }

        void detach(std::weak_ptr<IObserver> observer) override {

            // https://stackoverflow.com/questions/10120623/removing-item-from-list-of-weak-ptrs

            // C++20: std::erase_if is the modern and cleanest way to implement the erase-remove pattern.
            std::erase_if(m_observers, [&observer](const std::weak_ptr<IObserver>& wp) {
                return sameOwner(wp, observer);
                }
            );
        }

        void setMessage(std::string_view message) {
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
            setMessage("changing this message");
        }

    private:
        static bool sameOwner(const std::weak_ptr<IObserver>& lhs, const std::weak_ptr<IObserver>& rhs)
        {
            return !lhs.owner_before(rhs) && !rhs.owner_before(lhs);
        }

        void notify() {

            // clean up expired weak pointers while notifying active observers
            std::erase_if(
                m_observers,
                [this](const std::weak_ptr<IObserver>& wp) {
                    if (auto sharedPtr = wp.lock()) {
                        sharedPtr->update(m_message);
                        return false; // keep, as actively notified.
                    }
                    return true; // remove, because expired
                }
            );
        }
    };

    // ===========================================================================

    class Observer : public IObserver {
    private:
        std::string m_messageFromSubject;
        std::size_t m_number;

    public:
        Observer() 
        {
            static std::size_t nextNumber = 0;
            m_number = nextNumber++;
            std::println("Observer: {}", m_number);
        }

        ~Observer() override
        {
            std::println("d'tor Observer ({})", m_number);
        }

        void update(std::string_view messageFromSubject) override
        {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void printInfo() const {
            std::println("Observer: new message is available --> \"{}\"", m_messageFromSubject);
        }
    };

    static void example_01() {

        Subject subject;

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };

        subject.attach(observer1);
        subject.attach(observer2);
        subject.attach(observer3);

        subject.setMessage("Hello World!");
        subject.setMessage("Hello World Again");

        subject.detach(observer1);
        subject.detach(observer2);
        subject.detach(observer3);
    }

    static void example_02() {

        std::shared_ptr<Subject> subject{ std::make_shared<Subject>() };

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };

        subject->attach(observer1);
        subject->attach(observer2);

        {
            std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };
            subject->attach(observer3);
            subject->setMessage("Hello World!");
        }

        // Note: Watch contents of 'm_observers' list
        // Expired weak_ptr will be cleaned up on next notify()

        subject->setMessage("Hello World Again");

        subject->detach(observer1);
        subject->detach(observer2);
    }
}

// ===========================================================================

void test_conceptual_example_01()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    using namespace ConceptualExample_Observer_Pattern;

    example_01();
    example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
