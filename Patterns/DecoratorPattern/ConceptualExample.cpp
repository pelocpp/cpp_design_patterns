// ===========================================================================
// ConceptualExample.cpp - Decorator Pattern
// ===========================================================================

#include <cassert>
#include <format>
#include <memory>
#include <print>
#include <string>

/**
 * The base Component interface defines operations
 * that can be altered by decorators.
 */
class IComponent {
public:
    virtual ~IComponent() = default;

    [[nodiscard]]
    virtual std::string operation() const = 0;
};

/**
 * Concrete Components provide default implementations of the operation(s).
 * There might be several variations of these classes.
 */
class ConcreteComponent final : public IComponent {
public:
    std::string operation() const override {
        return "CONCRETE COMPONENT";
    }
};

// ---------------------------------------------------------------------------

/**
 * The base Decorator class follows the same interface as the concrete components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize it.
 * 
 * Note: DecoratorBase should not be instantiable: Therefore the constructor is protected.
 */
class DecoratorBase : public IComponent {
private:
   std::unique_ptr<IComponent> m_component;

protected:
    explicit DecoratorBase(std::unique_ptr<IComponent> component)
        // exclusive ownership saves reference-counting overhead
        : m_component{ std::move(component) }
    {
        // I would prefer to safeguard the constructor:
        // A decorator cannot meaningfully exist without a component!
        assert(m_component);
    }

public:
    /**
     * The Decorator delegates all work to the wrapped component
     * (nullptr in an existing DecoratorBase object cannot exist!).
     */
    std::string operation() const override {
        return m_component->operation();
    }
};

// ---------------------------------------------------------------------------

/**
 * Concrete Decorators call the wrapped object and alter its result in some way.
 */
class ConcreteDecoratorA final : public DecoratorBase {
    /**
     * Decorators may call parent implementation of the operation, instead of
     * calling the wrapped object directly. This approach simplifies extension of
     * decorator classes.
     */
public:
    explicit ConcreteDecoratorA(std::unique_ptr<IComponent> component)
        : DecoratorBase{ std::move(component) }
    {}

    std::string operation() const override {
        return std::format("ConcreteDecoratorA ( {} )", DecoratorBase::operation());

    }
};

// ---------------------------------------------------------------------------

/**
 * Decorators can execute their behavior either before or after
 * the call to a wrapped object.
 */
class ConcreteDecoratorB final : public DecoratorBase {
public:
    explicit ConcreteDecoratorB(std::unique_ptr<IComponent> component)
        : DecoratorBase{ std::move(component) }
    {}

    std::string operation() const override {
        return std::format("ConcreteDecoratorB [ {} ]", DecoratorBase::operation());
    }
};

// ---------------------------------------------------------------------------

/**
 * Need one more Decorator class to demonstrate nested execution of decorator objects
 */
class ConcreteDecoratorC final : public DecoratorBase {
public:
    explicit ConcreteDecoratorC(std::unique_ptr<IComponent> component)
        : DecoratorBase{ std::move(component) }
    {}

    std::string operation() const override {
        return std::format("ConcreteDecoratorC {{ {} }}", DecoratorBase::operation());
    }
};

// ---------------------------------------------------------------------------

/**
 * The client code works only with objects using the Component interface.
 * This way it can stay independent of the concrete classes of components
 * it works with.
 */
static void clientCode(const IComponent& component) {
    // ...
    std::println("Result: {}", component.operation());
    // ...
}

static void test_conceptual_example_01() {

    /**
     * This way the client code can support both simple components ...
     */
    std::unique_ptr<IComponent> component{
        std::make_unique<ConcreteComponent>()
    };

    std::print("Client: I've got a simple component:");
    clientCode(*component);
    std::println();
}

// ---------------------------------------------------------------------------

static void test_conceptual_example_02() {

    /**
     * ...as well as decorated ones ...
     *
     * Note how decorators can wrap not only simple components
     * but the other decorators as well.
     */

    std::unique_ptr<IComponent> component{
        std::make_unique<ConcreteComponent>()
    };

    std::unique_ptr<IComponent> decorator1{
        std::make_unique<ConcreteDecoratorA>(std::move(component))
    };

    std::unique_ptr<IComponent> decorator2{
        std::make_unique<ConcreteDecoratorB>(std::move(decorator1))
    };

    std::println("Client: Decorated component:");
    clientCode(*decorator2);
    std::println();
}

// ---------------------------------------------------------------------------

/**
* Same as before - written in a more compact syntax:
* Nested usage of decorator objects
*/

static void test_conceptual_example_03() {

    std::unique_ptr<IComponent> component{
        std::make_unique<ConcreteComponent>()
    };

    std::unique_ptr<IComponent> decorator{
        std::make_unique<ConcreteDecoratorB>(
            std::make_unique<ConcreteDecoratorA>(std::move(component))
        )
    };

    std::println("Client: Same decorated component - written in a more compact syntax:");
    clientCode(*decorator);
    std::println();
}

// --------------------------------------------------------------

/**
 * One more Demonstration of nested use of decorator objects
 */

static void test_conceptual_example_04() {

    std::unique_ptr<IComponent> component{
        std::make_unique<ConcreteComponent>()
    };

    std::unique_ptr<IComponent> decorator{
        std::make_unique<ConcreteDecoratorA>(
            std::make_unique<ConcreteDecoratorB>(
                std::make_unique<ConcreteDecoratorC>(std::move(component))))
    };

    std::println("Client: Decorated component using three decorator objects:");
    clientCode(*decorator);
    std::println();
}

// --------------------------------------------------------------

/**
 * Demonstrate reverse Decoration
 */

static void test_conceptual_example_05() {

    std::unique_ptr<IComponent> component{
        std::make_unique<ConcreteComponent>()
    };

    std::unique_ptr<IComponent> decorator{
        std::make_unique<ConcreteDecoratorC>(
            std::make_unique<ConcreteDecoratorB>(
                std::make_unique<ConcreteDecoratorA>(std::move(component)))) 
    };

    std::println("Client: Reverse Decoration:");
    clientCode(*decorator);
    std::println();
}

// --------------------------------------------------------------

/**
 * ... and at the very end: changing decorators at runtime
 */

static void test_conceptual_example_06() {

    // component which is going to be decorated
    std::unique_ptr<IComponent> component{ std::make_unique<ConcreteComponent>() };

    // run-time dependent decorator
    std::unique_ptr<IComponent> decorator;

    constexpr bool useVariantA = true;  // <== change 'true' to 'false'

    if (useVariantA)
    {
        std::unique_ptr<IComponent> decorator1{ std::make_unique<ConcreteDecoratorA>(std::move(component)) };
        decorator = std::make_unique<ConcreteDecoratorB>(std::move(decorator1));
        std::println("Client: Now I've this decorated component (if):");
    }
    else {
        std::unique_ptr<IComponent> decorator1 {std::make_unique<ConcreteDecoratorB>(std::move(component))};
        decorator = std::make_unique<ConcreteDecoratorA>(std::move(decorator1));
        std::println("Client: Now I've that decorated component (else):");
    }

    clientCode(*decorator);
}

void test_conceptual_example()
{
    test_conceptual_example_01();
    test_conceptual_example_02();
    test_conceptual_example_03();
    test_conceptual_example_04();
    test_conceptual_example_05();
    test_conceptual_example_06();
}

// ===========================================================================
// End-of-File
// ===========================================================================
