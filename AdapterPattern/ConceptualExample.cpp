// ===========================================================================
// ConceptualExample.cpp // Adapter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target {
public:
    Target() = default;

    virtual ~Target() = default;

    virtual std::string getRequest() const {
        return std::string{ "Target: The default target's behavior." };
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee {
public:
    Adaptee() = default;

    std::string getSpecificRequest() const {
        return std::string{ ".eetpadA eht fo roivaheb laicepS" };
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's interface.
 */
class Adapter : public Target {
private:
    std::shared_ptr<Adaptee> m_adaptee;

public:
    Adapter(std::shared_ptr<Adaptee> adaptee) : m_adaptee(adaptee) {}

    std::string getRequest() const override {
        std::string to_reverse = m_adaptee->getSpecificRequest();

        // note: std::reverse() operates in place
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(std::shared_ptr<Target> target) {
    std::string request = target->getRequest();
    std::cout << request << std::endl << std::endl;
}

void test_conceptual_example() {

    std::cout << "Client: I can work just fine with the Target objects:\n";
    std::shared_ptr<Target> target = std::shared_ptr<Target>(new Target{});
    ClientCode(target);

    std::shared_ptr<Adaptee> adaptee = std::shared_ptr<Adaptee>(new Adaptee{ });
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:" << std::endl;
    std::string specificRequest = adaptee->getSpecificRequest();
    std::cout << "Adaptee: " << specificRequest << std::endl << std::endl;

    std::cout << "Client: But I can work with it via the Adapter:" << std::endl;
    std::shared_ptr<Adapter> adapter = std::shared_ptr<Adapter>(new Adapter{ adaptee });
    ClientCode(adapter);
}

// ===========================================================================
// End-of-File
// ===========================================================================
