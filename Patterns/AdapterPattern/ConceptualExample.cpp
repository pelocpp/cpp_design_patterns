// ===========================================================================
// ConceptualExample.cpp - Adapter Pattern
// ===========================================================================

#include <algorithm>
#include <format>
#include <memory>
#include <print>
#include <string>

/**
 * ITarget defines the domain-specific interface used by the client code
 */
class ITarget
{
public:
    virtual ~ITarget() = default;

    virtual std::string request() const = 0;
};

/**
 * Target implements ITarget - implementation usable by the client code
 */
class Target final : public ITarget
{
public:
    std::string request() const override
    {
        return "Target: The target's default behavior.";
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
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface
 * compatible with the ITarget's interface.
 */
class Adapter final : public ITarget
{
private:
    std::unique_ptr<Adaptee> m_adaptee;

public:
    explicit Adapter(std::unique_ptr<Adaptee> adaptee)
        : m_adaptee{ std::move(adaptee) }
    {}

    std::string request() const override {

        if (!m_adaptee) {
            return {};
        }

        std::string original{ m_adaptee->specificRequest() };

        std::reverse(original.begin(), original.end());

        return std::format("Adapter: (TRANSLATED) {}", original);
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 * Passed as a const reference, since the client does not need to own the object.
 */
static void clientCode(const ITarget& target) {

    std::string response{ target.request() };

    std::println("{}", response);
}

static void test_conceptual_example_01() {

    std::unique_ptr<Adaptee> adaptee{ std::make_unique<Adaptee>() };

    std::unique_ptr<Adapter> adapter{ std::make_unique<Adapter>(std::move(adaptee)) };

    clientCode(*adapter);
}

static void test_conceptual_example_02() {

    std::println("Client: I can work fine with the Target object:");
    auto target = std::make_unique<Target>();
    clientCode(*target);

    auto adaptee = std::make_unique<Adaptee>();
    std::println("Client: The Adaptee class has an incompatible interface:");
    std::string specificResponse = adaptee->specificRequest();
    std::println("Adaptee: {}", specificResponse);

    std::println("Client: But I can work with the Adaptee via the Adapter:"); 
    auto adapter = std::make_unique<Adapter>(std::move(adaptee));
    clientCode(*adapter);
}

void test_conceptual_example() {

    test_conceptual_example_01();
    test_conceptual_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
