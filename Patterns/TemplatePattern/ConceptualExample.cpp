// ===========================================================================
// ConceptualExample.cpp // Template Method
// ===========================================================================

#include <iostream>
#include <memory>

/**
 * The Abstract Class defines a template method that contains a skeleton of some
 * algorithm, composed of calls to (usually) abstract primitive operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */
class AbstractClass {
    /**
     * The template method defines the skeleton of an algorithm.
     */
public:
    void TemplateMethod() const {
        this->BaseOperation1();         // may be overriden, but it's not mandatory
        this->RequiredOperations1();    // MUST be overriden
        this->BaseOperation2();         // may be overriden, but it's not mandatory
        this->Hook1();                  // may be overriden, but it's not mandatory
        this->RequiredOperation2();     // MUST be overriden
        this->BaseOperation3();         // may be overriden, but it's not mandatory
        this->Hook2();                  // may be overriden, but it's not mandatory
    }

    /**
     * These operations already have implementations.
     */
protected:
    virtual void BaseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work" << std::endl;
    }

    virtual void BaseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations" << std::endl;
    }

    virtual void BaseOperation3() const {
        std::cout << "AbstractClass says: But I am doing the bulk of the work anyway" << std::endl;
    }

    /**
     * These operations have to be implemented in subclasses.
     */
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;

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
class ConcreteClass1 : public AbstractClass {
protected:
    virtual void RequiredOperations1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1" << std::endl;
    }
    virtual void RequiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2" << std::endl;
    }
};

/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class ConcreteClass2 : public AbstractClass {
protected:
    virtual void RequiredOperations1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1" << std::endl;
    }
    virtual void RequiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2" << std::endl;
    }
    virtual void BaseOperation1() const override {
        AbstractClass::BaseOperation1();
        std::cout << "ConcreteClass2 says: Overridden BaseOperation1" << std::endl;
    }
    virtual void Hook1() const override {
        std::cout << "ConcreteClass2 says: Overridden Hook1" << std::endl;
    }
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void clientCode(std::shared_ptr<AbstractClass> obj) {
    // ...
    obj->TemplateMethod();
    // ...
}

void test_conceptual_example() {
    std::cout << "Same client code can work with different subclasses (1):" << std::endl;
    std::shared_ptr<AbstractClass> concreteClass1 = std::make_shared<ConcreteClass1>();
    clientCode(concreteClass1);
    std::cout << std::endl;

    std::cout << "Same client code can work with different subclasses (2):" << std::endl;
    std::shared_ptr<AbstractClass> concreteClass2 = std::make_shared<ConcreteClass2>();
    clientCode(concreteClass2);
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
