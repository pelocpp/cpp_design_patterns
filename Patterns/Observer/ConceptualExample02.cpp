// ===========================================================================
// ConceptualExample02.cpp // Observer // Variant 2 // Using RAII-Subscription
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

namespace ConceptualExample_Observer_Pattern_RAII {

    class IObserver {
    public:
        virtual ~IObserver() = default;

        virtual void update(std::string_view message) = 0;
    };

    class Connection;

    class ISubject {
    public:
        virtual ~ISubject() = default;

     //   virtual void attach(std::weak_ptr<IObserver> observer) = 0;
           virtual void detach(const std::weak_ptr<IObserver>& observer) = 0;

        //   virtual Connection attach(std::weak_ptr<IObserver> observer) = 0;
    };

    // =======================================================================

    /**
     * The Subject owns some important state
     * and notifies observers when the state changes.
     *
     * Subscription is handled via RAII: attach() returns a move-only
     * Connection object. When that Connection is destroyed (goes out of
     * scope, is reset, etc.), the observer is automatically detached.
     * This removes the need for clients to remember to call detach().
     */

    class Subject : public ISubject {
    private:
        std::vector<std::weak_ptr<IObserver>> m_observers;
        std::string                           m_message;

    public:
        class Connection
        {
        public:
            Connection() = default;

            Connection(Subject* subject, std::weak_ptr<IObserver> observer)
                : m_subject(subject), m_observer(std::move(observer))
            {}
            
     //       ~Connection() { if (m_subject) m_subject->detach(m_observer); }

            ~Connection() {
                release();
            }
            
            // move-only: ownership of "being subscribed" can move,
            // but must not be duplicated (would cause double-detach).
            //Connection(Connection&&) noexcept = default;
            //Connection& operator=(Connection&&) noexcept = default;

            Connection(const Connection&) = delete;
            Connection& operator=(const Connection&) = delete;

            Connection(Connection&& other) noexcept
                : m_subject(other.m_subject), m_observer(std::move(other.m_observer))
            {
                other.m_subject = nullptr;
            }

            Connection& operator=(Connection&& other) noexcept {
                if (this != &other) {
                    release();
                    m_subject = other.m_subject;
                    m_observer = std::move(other.m_observer);
                    other.m_subject = nullptr;
                }
                return *this;
            }
        
            // manual early disconnect, if needed before scope end
            void disconnect() {
                release();
            }

            [[nodiscard]] bool isConnected() const {
                return m_subject != nullptr && !m_observer.expired();
            }

        private:
            void release() {
                if (m_subject != nullptr) {
                    m_subject->detach(m_observer);
                    m_subject = nullptr;
                }
            }

            Subject*                 m_subject{ nullptr };
            std::weak_ptr<IObserver> m_observer;
        };

        Subject() = default;

        ~Subject() override {
            std::println("d'tor Subject");
        }

        // Subject is referenced by outstanding Connection objects (raw
        // pointer back-reference), so copying/moving it would leave
        // those Connections dangling. Disable both.
        Subject(const Subject&) = delete;
        Subject& operator=(const Subject&) = delete;
        Subject(Subject&&) = delete;
        Subject& operator=(Subject&&) = delete;

        /**
         * subscription management methods
         */


        [[nodiscard]]
        Connection attach(std::weak_ptr<IObserver> observer) {
            m_observers.push_back(observer);
            return Connection{ this, std::move(observer) };
        }

        void detach(const std::weak_ptr<IObserver>& observer) override {

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

            //// 1) clean up expired weak pointers first
            //std::erase_if(m_observers, [](const std::weak_ptr<IObserver>& wp) {
            //    return wp.expired();
            //    }
            //);

            //// 2) notify on a snapshot copy, so that re-entrant attach()/detach()
            ////    calls from within an observer's update() don't invalidate
            ////    the vector we're currently iterating over.
            //auto snapshot = m_observers;
            //for (const auto& wp : snapshot) {
            //    if (auto sharedPtr = wp.lock()) {
            //        sharedPtr->update(m_message);
            //    }
            //}
        }
    };

    // ===========================================================================

    class Observer final : public IObserver {
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

    // ===========================================================================
    // Client code, Variant A:
    // Connections live in local variables and detach automatically
    // once they go out of scope - no manual detach() needed.

    static void clientCode_ScopedConnections() {

        Subject subject;

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };

        {
            auto connection1 = subject.attach(observer1);
            auto connection2 = subject.attach(observer2);
            auto connection3 = subject.attach(observer3);

            subject.setMessage("Hello World!");
            subject.setMessage("Hello World Again");

        }// <-- connection1/2/3 destroyed here => automatic detach
        
         // no more observers attached at this point
        subject.setMessage("Nobody is listening anymore");
    }


    // ===========================================================================
    // Client code, Variant B:
    // Connections are kept explicitly (e.g. as members or in a container),
    // so the client controls the subscription lifetime directly.

    static void clientCode_ManagedConnections() {

        Subject subject;

        std::shared_ptr<IObserver> observer1{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer2{ std::make_shared<Observer>() };
        std::shared_ptr<IObserver> observer3{ std::make_shared<Observer>() };

        std::vector<Subject::Connection> connections;
        connections.push_back(subject.attach(observer1));
        connections.push_back(subject.attach(observer2));
        connections.push_back(subject.attach(observer3));

        subject.setMessage("Hello World!");

        // explicitly disconnect just one observer early
        connections[0].disconnect();

        subject.setMessage("Hello World Again");

        // remaining connections are cleaned up automatically
        // when 'connections' goes out of scope.
    }
}

// ===========================================================================

void test_conceptual_example_02()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    using namespace ConceptualExample_Observer_Pattern_RAII;

    std::println("--- Scoped Connections ---");
    clientCode_ScopedConnections();

    std::println();
    std::println("--- Managed Connections ---");
    clientCode_ManagedConnections();
}

// ===========================================================================
// End-of-File
// ===========================================================================
