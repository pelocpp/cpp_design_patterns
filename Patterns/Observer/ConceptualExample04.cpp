// ===========================================================================
// ConceptualExample03.cpp // Observer // Variant 4 // std::function
// ===========================================================================

/**
 * Observer Design Pattern
 */

#include <cstddef>
#include <functional>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>

 /**

    Lebenszeit - Sicherheit(std::weak_ptr Capture) :
    Im Lambda wird weakObs = std::weak_ptr<Observer>(observer1) gefangen.
    Das Lambda blockiert das Sterben des Observers nicht mehr.
    Vor dem Aufruf wird mit if (auto obs = weakObs.lock()) geprüft, ob das Objekt noch existiert.
    Das verhindert sowohl Speicherlecks als auch "Dangling Pointer" - Abstürze.
*/

namespace ObserverDesignPattern_StdFunction
{
    /**
     * The Subject owns some important state
     * and notifies observers when the state changes.
     */

    class Subject
    {
    private:
        std::unordered_map<std::size_t, std::move_only_function<void(std::string_view) const>> m_observers;
        std::string m_message;
        std::size_t m_nextId;

    public:
        Subject() noexcept : m_nextId{} {}

        ~Subject() noexcept {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods.
         */

        std::size_t attach(std::move_only_function<void(std::string_view) const> observer) {
            std::size_t id = m_nextId++;
            m_observers.emplace(id, std::move(observer));
            return id;
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
            for (const auto& [id, callback] : m_observers) {
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

        ~Observer() noexcept {
            std::println("d'tor Observer ({})", m_number);
        }

        void update(std::string_view  messageFromSubject) {
            m_messageFromSubject = messageFromSubject;
            printInfo();
        }

        void printInfo() const {
            std::println("Observer ({}): new message is available --> \"{}\"",
                m_number, m_messageFromSubject);
        }
    };
}

void test_conceptual_example_04() {

    using namespace ObserverDesignPattern_StdFunction;

    auto subject = std::make_shared<Subject>();

    auto observer1 = std::make_shared<Observer>();
    auto observer2 = std::make_shared<Observer>();
    auto observer3 = std::make_shared<Observer>();

    // Clean C++ solution for the lifetime problem:
    // We convert the shared_ptr into a weak_ptr and capture *that* in the lambda.
    auto id1 = subject->attach([weakObs = std::weak_ptr<Observer>(observer1)](std::string_view msg) {
        if (auto obs = weakObs.lock()) {
            obs->update(msg);
        }
        }
    );

    // Ab C++20/C++23 schreibt man das noch kürzer mit Lambda-Init-Captures:
    auto id2 = subject->attach([weakObs = observer2.get()](std::string_view msg) {
        // Hinweis: .get() holt den rohen Zeiger. Nur sicher, wenn die Lebenszeit garantiert ist.
        // Die sicherste Variante bleibt der weak_ptr wie bei id1:
        });

    // Wir überschreiben id2 hier direkt mit der sicheren weak_ptr Variante:
    subject->detach(id2);
    id2 = subject->attach([weakObs = std::weak_ptr<Observer>(observer2)](std::string_view msg) {
        if (auto obs = weakObs.lock()) {
            obs->update(msg);
        }
        });

    subject->createMessage("Hello Modern C++!");

    // Test des Lebenszeit-Schutzes:
    std::println("\n--- Observer 2 stirbt jetzt ---");
    observer2.reset();

    // Nachricht senden. Es stürzt nicht ab! Das Lambda von id2 merkt, 
    // dass observer2 tot ist und überspringt den Aufruf geräuschlos.
    subject->createMessage("Hello World Again");

    subject->detach(id1);
    subject->detach(id2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
