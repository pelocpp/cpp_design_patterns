// ===========================================================================
// ConceptualExample.cpp // Template Method
// ===========================================================================

#include <memory>
#include <print>


/**
 * The Abstract Class defines a template method that contains a skeleton of some
 * algorithm, composed of calls to (usually) abstract primitive operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */
class AbstractClass {

public:
    virtual ~AbstractClass() = default;

    /**
     * The template method defines the skeleton of an algorithm:
     */

    void TemplateMethod() const
    {
        BaseOperation1();             // may be overriden, but it's not mandatory

        if (RequiredOperations1()) {  // MUST be overriden

            BaseOperation2();         // may be overriden, but it's not mandatory
            Hook1();                  // may be overriden, but it's not mandatory
        }
        else
        {
            RequiredOperation2();     // MUST be overriden
            BaseOperation3();         // may be overriden, but it's not mandatory
            Hook2();                  // may be overriden, but it's not mandatory
        }
    }

    /**
     * These operations already have implementations.
     */
private:
    virtual void BaseOperation1() const {
        // std::cout << "AbstractClass says: I am doing the bulk of the work" << std::endl;
        std::println("AbstractClass says: I am doing the bulk of the work");
    }

    virtual void BaseOperation2() const {
        std::println("AbstractClass says: But I let subclasses override some operations");
    }

    virtual void BaseOperation3() const {
        std::println("AbstractClass says: But I am doing the bulk of the work anyway");
    }

    /**
     * These operations have to be implemented in subclasses.
     */
    virtual bool RequiredOperations1() const = 0;
    virtual bool RequiredOperation2() const = 0;

    /**
     * These are "hooks." Subclasses may override them, but it's not mandatory
     * since the hooks already have default (but empty) implementation.
     * Hooks provide additional extension points in some crucial places of the
     * algorithm.
     */
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

/**
 * Concrete classes have to implement all abstract operations of the base class.
 * They can also override some operations with a default implementation.
 */
class ConcreteClass1 final : public AbstractClass {
private:
    bool RequiredOperations1() const override {
        std::println("ConcreteClass1 says: Implemented Operation1");
        return false;
    }

    bool RequiredOperation2() const override {
        std::println("ConcreteClass1 says: Implemented Operation2");
        return false;
    }
};

/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class ConcreteClass2 final : public AbstractClass {
private:
    bool RequiredOperations1() const override {
        std::println("ConcreteClass2 says: Implemented Operation1");
        return true;
    }

    bool RequiredOperation2() const override {
        std::println("ConcreteClass2 says: Implemented Operation2");
        return true;
    }

    void BaseOperation1() const override {
        std::println("ConcreteClass2 says: Overridden BaseOperation1");
    }

    void Hook1() const override {
        std::println("ConcreteClass2 says: Overridden Hook1");
    }
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
static void clientCode(const AbstractClass& obj) {
    // ...
    obj.TemplateMethod();
    // ...
}

void test_conceptual_example() {
    std::println("Same client code can work with different subclasses (1):");
    auto concreteObject1 = std::make_unique<ConcreteClass1>();
    clientCode(*concreteObject1);
    std::println();

    std::println("Same client code can work with different subclasses (2):");
    auto concreteObject2 = std::make_unique<ConcreteClass1>();
    clientCode(*concreteObject2);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
