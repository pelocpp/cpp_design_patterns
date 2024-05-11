// ===========================================================================
// ConceptualExample.cpp // Adapter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

/**
 * ITarget defines the domain-specific interface used by the client code
 */
class ITarget
{
public:
    virtual ~ITarget() {}

    virtual std::string getRequest() const = 0;
};

/**
 * Target implements ITarget - implementation usable by the client code
 */
class Target : public ITarget
{
public:
    Target() {}

    virtual std::string getRequest() const override
    {
        return std::string{ "Target: The target's default behavior." };
    }
};

/**
 * The Adaptee contains some useful behavior,
 * but its interface is incompatible with the existing client code.
 * The Adaptee needs some adaptation before the client code can use it.
 */
class Adaptee
{
public:
    Adaptee() {}

    std::string getSpecificRequest() const
    {
        return std::string{ ".eetpadA eht fo roivaheb laicepS" };
    }
};

/**
 * The Adapter makes the Adaptee's interface
 * compatible with the ITarget's interface.
 */
class Adapter : public ITarget
{
private:
    std::shared_ptr<Adaptee> m_adaptee;

public:
    Adapter(std::shared_ptr<Adaptee> adaptee) 
        : m_adaptee{ adaptee }
    {}

    std::string getRequest() const override {

        std::string toReverse{ m_adaptee->getSpecificRequest() };

        std::reverse(std::begin(toReverse), std::end(toReverse));

        return std::string{ "Adapter: (TRANSLATED) " + toReverse };
    }
};

/**
 * The client code supports all classes that follow the Target interface
 */
static static void clientCode(std::shared_ptr<ITarget> target) {

    std::string request{ target->getRequest() };
    std::cout << request << std::endl << std::endl;
}

void test_conceptual_example() {

    std::cout << "Client: I can work fine with the Target object" << std::endl;
    std::shared_ptr<ITarget> target{ new Target{} };
    clientCode(target);

    std::shared_ptr<Adaptee> adaptee{ new Adaptee{ } };
    std::cout << "Client: The Adaptee class has an incompatible interface:" << std::endl;
    std::string specificRequest = adaptee->getSpecificRequest();
    std::cout << "Adaptee: " << specificRequest << std::endl << std::endl;

    std::cout << "Client: But I can work with the Adaptee via the Adapter:" << std::endl;
    std::shared_ptr<Adapter> adapter{ new Adapter{ adaptee } };
    clientCode(adapter);
}

// ===========================================================================
// End-of-File
// ===========================================================================
