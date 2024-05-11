// ===========================================================================
// ConceptualExample.cpp // Abstract Factory
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

/**
 * Each distinct product of a product family should have a base interface.
 * All variants of this product must implement this interface.
 */
class AbstractProductA {
public:
    virtual ~AbstractProductA() {}

    virtual std::string usefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductA1 : public AbstractProductA {
public:
    std::string usefulFunctionA() const override {
        return "The result of the product A1.";
    }
};

class ConcreteProductA2 : public AbstractProductA {
    std::string usefulFunctionA() const override {
        return "The result of the product A2.";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
class AbstractProductB {
    /**
     * Product B is able to do its own thing...
     */
public:
    virtual ~AbstractProductB() {}

    virtual std::string usefulFunctionB() const = 0;

    /**
     * ...but it also can collaborate with the ProductA.
     *
     * The Abstract Factory makes sure that all products it creates are of the
     * same variant and thus, compatible.
     */
    virtual std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductB1 : public AbstractProductB {
public:
    std::string usefulFunctionB() const override {
        return "The result of the product B1.";
    }

    /**
     * The variant, Product B1, is only able to work correctly with the variant,
     * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.usefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    std::string usefulFunctionB() const override {
        return "The result of the product B2.";
    }

    /**
     * The variant, Product B2, is only able to work correctly with the variant,
     * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.usefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory {
public:
    virtual std::shared_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::shared_ptr<AbstractProductB> createProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible.
 * 
 * NOTE: Signatures of the Concrete Factory's methods return an abstract product,
 *       while inside the method a concrete product is instantiated.
 */
class ConcreteFactory1 : public AbstractFactory {
public:
    std::shared_ptr<AbstractProductA> createProductA() const override {
        return std::make_shared<ConcreteProductA1>();  // <== concrete product returned
    }

    std::shared_ptr<AbstractProductB> createProductB() const override {
        return std::make_shared<ConcreteProductB1>();  // <== concrete product returned
    }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class ConcreteFactory2 : public AbstractFactory {
public:
    std::shared_ptr<AbstractProductA> createProductA() const override {
        return std::make_shared<ConcreteProductA2>();  // <== concrete product returned
    }
    std::shared_ptr<AbstractProductB> createProductB() const override {
        return std::make_shared<ConcreteProductB2>();  // <== concrete product returned
    }
};

/**
 * The client code works with factories and products only through abstract types:
 * AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

static void clientCode(const std::shared_ptr<AbstractFactory>& factory) {
    const std::shared_ptr<AbstractProductA> product_a = factory->createProductA();
    const std::shared_ptr<AbstractProductB> product_b = factory->createProductB();
    std::cout << product_b->usefulFunctionB() << std::endl;
    std::cout << product_b->anotherUsefulFunctionB(*product_a) << std::endl;
}

// function prototypes
void test_conceptual_example()
{
    std::cout << "Client: Testing client code with the first factory type:" << std::endl;;
    std::shared_ptr<ConcreteFactory1> f1 = std::make_shared<ConcreteFactory1>();
    clientCode(f1);
    std::cout << std::endl;

    std::cout << "Client: Testing the same client code with the second factory type:" << std::endl;;
    std::shared_ptr<ConcreteFactory2> f2 = std::make_shared<ConcreteFactory2>();
    clientCode(f2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
