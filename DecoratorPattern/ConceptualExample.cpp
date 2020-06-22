// ===========================================================================
// ConceptualExample.cpp // Decorator Pattern
// ===========================================================================

// https://refactoring.guru/design-patterns/decorator

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

/**
 * The base Component interface defines operations
 * that can be altered by decorators.
 */
class Component {
public:
    virtual ~Component() {}
    virtual std::string Operation() const = 0;
};

/**
 * Concrete Components provide default implementations of the operations.
 * There might be several variations of these classes.
 */
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};

/**
 * The base Decorator class follows the same interface as the other components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize it.
 */
class DecoratorBase : public Component {
protected:
   std::shared_ptr<Component> m_component;

public:
    DecoratorBase(const std::shared_ptr<Component>& component) : m_component(component) {}

    /**
     * The Decorator delegates all work to the wrapped component.
     */
    std::string Operation() const override {
        return m_component->Operation();
    }
};

/**
 * Concrete Decorators call the wrapped object and alter its result in some way.
 */
class ConcreteDecoratorA : public DecoratorBase {
    /**
     * Decorators may call parent implementation of the operation, instead of
     * calling the wrapped object directly. This approach simplifies extension of
     * decorator classes.
     */
public:
    ConcreteDecoratorA(const std::shared_ptr<Component>& component) : DecoratorBase(component) {}

    std::string Operation() const override {
        return "ConcreteDecoratorA(" + DecoratorBase::Operation() + ")";
    }
};

/**
 * Decorators can execute their behavior either before or after the call to a
 * wrapped object.
 */
class ConcreteDecoratorB : public DecoratorBase {
public:
    ConcreteDecoratorB(const std::shared_ptr<Component>& component) : DecoratorBase(component) {
    }

    std::string Operation() const override {
        return "ConcreteDecoratorB(" + DecoratorBase::Operation() + ")";
    }
};

/**
 * The client code works with all objects using the Component interface. This
 * way it can stay independent of the concrete classes of components it works
 * with.
 */
void clientCode(std::shared_ptr<Component> component) {
    // ...
    std::cout << "RESULT: " << component->Operation();
    // ...
}

void test_conceptual_example() {
    /**
     * This way the client code can support both simple components...
     */
    std::shared_ptr<Component> simple = std::make_shared<ConcreteComponent> ();
    std::cout << "Client: I've got a simple component:\n";
    clientCode(simple);
    std::cout << "\n\n";
    /**
     * ...as well as decorated ones.
     *
     * Note how decorators can wrap not only simple components but the other
     * decorators as well.
     */
    std::shared_ptr<Component> decorator1 = std::make_shared<ConcreteDecoratorA>(simple);
    std::shared_ptr<Component> decorator2 = std::make_shared<ConcreteDecoratorB>(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    clientCode(decorator2);
    std::cout << "\n";
}

// ===========================================================================
// End-of-File
// ===========================================================================
