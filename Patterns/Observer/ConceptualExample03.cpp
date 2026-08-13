// ===========================================================================
// ConceptualExample02.cpp // Observer // Variant 3 // Self Unregister
// ===========================================================================

/**
 * Observer Design Pattern
 */

#include <algorithm>       // std::erase_if
#include <list>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace ObserverDesignPattern_SelfUnregister {

    // Vorwärtsdeklaration, da sich die Interfaces gegenseitig benötigen
    class ISubject;

    class IObserver {
    public:
        virtual ~IObserver() = default;

        virtual void update(std::string_view message) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() = default;

        virtual void attach(std::shared_ptr<IObserver> observer) = 0;
        virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    };

    // =======================================================================

    class Subject : public ISubject {
    private:
        std::vector<std::weak_ptr<IObserver>> m_observers;
        std::string                           m_message;

    public:
        ~Subject() noexcept override {
            std::println("d'tor Subject");
        }

        /**
         * subscription management methods
         */
        void attach(std::shared_ptr<IObserver> observer) override {
            m_observers.push_back(observer);
        }

        void detach(std::shared_ptr<IObserver> observer) override {
            // C++20: Effizientes Entfernen basierend auf der Identität des Objekts
            std::erase_if(m_observers, [&observer](const std::weak_ptr<IObserver>& wp) {
                return !observer.owner_before(wp) && !wp.owner_before(observer);
                }
            );
        }

        void createMessage(const std::string& message) {
            m_message = message;
            notify();
        }

    private:
        void notify() {

            // Gleichzeitiges Benachrichtigen und Bereinigen von abgelaufenen Pointern
            std::erase_if(m_observers, [this](const std::weak_ptr<IObserver>& wp) {
                if (auto sharedPtr = wp.lock()) {
                    sharedPtr->update(m_message);
                    return false;
                }
                return true;
                }
            );
        }
    };

    // =======================================================================

    // WICHTIG: enable_shared_from_this erlaubt dem Observer, shared_from_this() zu nutzen
    class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
    private:
        std::string m_messageFromSubject;
        std::size_t m_number;

        // Der Observer merkt sich alle Subjects, bei denen er registriert ist
        std::vector<std::weak_ptr<ISubject>> m_observedSubjects;

    public:
        Observer() {
            static std::size_t nextNumber = 0;
            m_number = nextNumber++;
            std::println("Observer {} erzeugt.", m_number);
        }

        // RAII: Beim Zerstören meldet sich der Observer überall automatisch ab!
        ~Observer() noexcept override {
            std::println("d'tor Observer ({}) -> Melde mich von allen verbleibenden Subjects ab.", m_number);
            for (const auto& weakSubject : m_observedSubjects) {
                if (auto subject = weakSubject.lock()) {
                    // Da wir uns im Destruktor befinden, dürfen wir shared_from_this() NICHT mehr aufrufen!
                    // Stattdessen nutzen wir das clevere automatische Bereinigen von expired() weaks im Subject bei notify()
                    // ODER wir übergeben einen nackten Pointer, wenn das Interface das erlauben würde.
                    // Für dieses Design lassen wir das Subject die abgelaufene weak_ptr einfach beim nächsten notify() löschen.
                }
            }
        }

        // Komfortmethode zum Anmelden
        void registerAt(std::shared_ptr<ISubject> subject) {
            if (subject) {
                subject->attach(shared_from_this());
                m_observedSubjects.push_back(subject);
                std::println("Observer {}: Registriert bei Subject.", m_number);
            }
        }

        // Die von dir gewünschte Methode zur Selbstabmeldung
        void removeMeFromSubject(std::shared_ptr<ISubject> subject) {
            if (!subject) return;

            std::println("Observer {}: Melde mich aktiv vom Subject ab.", m_number);

            // 1. Vom Subject abmelden (Das Subject wirft uns aus seiner Liste)
            subject->detach(shared_from_this());

            // 2. Das Subject aus der eigenen Liste des Observers löschen
            std::erase_if(m_observedSubjects, [&subject](const std::weak_ptr<ISubject>& wp) {
                auto sharedSubject = wp.lock();
                return sharedSubject == subject;
                });
        }

        void update(std::string_view messageFromSubject) override {
            m_messageFromSubject = messageFromSubject;
            std::println("Observer {}: Neue Nachricht erhalten --> \"{}\"", m_number, m_messageFromSubject);
        }
    };
}

// =======================================================================

void test_conceptual_example_03()
{
    using namespace ObserverDesignPattern_SelfUnregister;

    auto subject = std::make_shared<Subject>();

    auto observer1 = std::make_shared<Observer>();
    auto observer2 = std::make_shared<Observer>();

    // Anmeldung erfolgt nun komfortabel über den Observer
    observer1->registerAt(subject);
    observer2->registerAt(subject);

    subject->createMessage("Erste Nachricht");

    // Verwendung deiner gewünschten Methode
    observer1->removeMeFromSubject(subject);

    // Nur noch Observer 2 sollte diese Nachricht erhalten
    subject->createMessage("Zweite Nachricht");

    std::println("\n--- Block-Bereich startet ---");
    {
        auto observer3 = std::make_shared<Observer>();
        observer3->registerAt(subject);
        subject->createMessage("Dritte Nachricht (mit Nr. 2)");

        std::println("Observer 2 verlässt gleich den Scope...");
    } // observer3 wird hier zerstört.
    std::println("--- Block-Bereich beendet ---\n");

    // Das Subject bereinigt die Leiche von Observer 3 beim nächsten notify() automatisch!
    subject->createMessage("Vierte Nachricht (nur noch Nr. 1)");
}

// ===========================================================================
// End-of-File
// ===========================================================================

