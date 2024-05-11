// ===========================================================================
// ConceptualExample.cpp // Facade
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample {

    /**
     * The Subsystem can accept requests either from the facade or client directly.
     * In any case, to the Subsystem, the Facade is yet another client.
     */
    class Subsystem1 {
    public:
        Subsystem1() { std::cout << "Subsystem1: Created." << std::endl; }
        ~Subsystem1() { std::cout << "Subsystem1: Released." << std::endl; }

        std::string complexOperation1() const {
            return "Subsystem1: Initialized!\n";
        }

        std::string complexOperation2() const {
            return "Subsystem1: Works!\n";
        }
    };

    /**
     * Some facades can work with multiple subsystems at the same time.
     */
    class Subsystem2 {
    public:
        Subsystem2() { std::cout << "Subsystem2: Created." << std::endl; }
        ~Subsystem2() { std::cout << "Subsystem2: Released." << std::endl; }

        std::string complexOperation1() const {
            return "Subsystem2: Initialized!\n";
        }

        std::string complexOperation2() const {
            return "Subsystem2: Works too!\n";
        }
    };

    /**
     * The Facade class provides a simple interface to the complex logic of one or
     * several subsystems. The Facade delegates the client requests to the
     * appropriate objects within the subsystem. The Facade is also responsible for
     * managing their lifecycle. All of this shields the client from the undesired
     * complexity of the subsystem.
     */
    class Facade {
    private:
        std::shared_ptr<Subsystem1> m_subsystem1;
        std::shared_ptr<Subsystem2> m_subsystem2;

        /**
         * Depending on your application's needs, you can provide the Facade with
         * existing subsystem objects or force the Facade to create them on its own.
         */
    public:
        /**
         * In this case we will delegate the memory ownership to Facade Class
         */
        Facade() {
            m_subsystem1 = std::make_shared<Subsystem1>();
            m_subsystem2 = std::make_shared<Subsystem2>();
        }

        ~Facade() {}

        /**
         * The Facade's methods are convenient shortcuts to the sophisticated
         * functionality of the subsystems. However, clients get only to a fraction of
         * a subsystem's capabilities.
         */
        std::string simpleOperation() const {
            std::string result = "Facade initializes subsystems:\n";
            result += m_subsystem1->complexOperation1();
            result += m_subsystem2->complexOperation1();

            result += "Facade orders subsystems to perform actions:\n";
            result += m_subsystem1->complexOperation2();
            result += m_subsystem2->complexOperation2();
            return result;
        }
    };

    /**
     * The client code works with complex subsystems through a simple interface
     * provided by the Facade. When a facade manages the lifecycle of the subsystem,
     * the client might not even know about the existence of the subsystem. This
     * approach lets you keep the complexity under control.
     */
    static void clientCode(const Facade& facade) {
        // ...
        std::cout << facade.simpleOperation();
        // ...
    }
}

void test_conceptual_example () {
    using namespace ConceptualExample;

    Facade facade;
    clientCode(facade);
}

// ===========================================================================
// End-of-File
// ===========================================================================
