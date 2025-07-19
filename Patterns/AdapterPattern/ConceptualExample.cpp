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

    virtual std::string request() const = 0;
};

/**
 * Target implements ITarget - implementation usable by the client code
 */
class Target : public ITarget
{
public:
    Target() {}

    std::string request() const override
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

    std::string specificRequest() const
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
    std::unique_ptr<Adaptee> m_adaptee;

public:
    Adapter(std::unique_ptr<Adaptee> adaptee)
        : m_adaptee{ std::move(adaptee) }
    {}

    std::string request() const override {

        std::string toReverse{ m_adaptee->specificRequest() };

        std::reverse(
            toReverse.begin(),
            toReverse.end()
        );

        return std::string{ "Adapter: (TRANSLATED) " + toReverse };
    }
};

/**
 * The client code supports all classes that follow the Target interface
 */
static void clientCode(std::unique_ptr<ITarget> target) {

    std::string response{ target->request() };
    std::cout << response << std::endl << std::endl;
}

static void test_conceptual_example_01() {

    std::unique_ptr<Adaptee> adaptee{ std::make_unique<Adaptee>() };

    std::unique_ptr<Adapter> adapter{ std::make_unique<Adapter>(std::move(adaptee)) };

    clientCode(std::move(adapter));
}

static void test_conceptual_example_02() {

    std::cout << "Client: I can work fine with the Target object" << std::endl;
    std::unique_ptr<ITarget> target{ std::make_unique<Target>() };
    clientCode(std::move(target));

    std::unique_ptr<Adaptee> adaptee{ std::make_unique<Adaptee>() };
    std::cout << "Client: The Adaptee class has an incompatible interface:" << std::endl;
    std::string specificResponse = adaptee->specificRequest();
    std::cout << "Adaptee: " << specificResponse << std::endl << std::endl;

    std::cout << "Client: But I can work with the Adaptee via the Adapter:" << std::endl;
    std::unique_ptr<Adapter> adapter{ std::make_unique<Adapter>(std::move(adaptee)) };
    clientCode(std::move(adapter));
}

void test_conceptual_example() {

    test_conceptual_example_01();
    test_conceptual_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
