// ===========================================================================
// ConceptualExample02.cpp // Factory Method
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample02 {

    /**
     * The Product interface declares the operations that all concrete products must
     * implement.
     */
    class ProductBase {
    public:
        virtual ~ProductBase() {}
        virtual std::string operation() const = 0;
    };

    /**
     * Concrete Products provide various implementations of the Product interface.
     */
    class ConcreteProduct1 : public ProductBase {
    public:
        std::string operation() const override {
            return "{ Result of the ConcreteProduct1 }";
        }
    };

    class ConcreteProduct2 : public ProductBase {
    public:
        std::string operation() const override {
            return "{ Result of the ConcreteProduct2 }";
        }
    };

    /**
     * The FactoryBase class declares the factory method that is supposed to return an
     * object of a Product class. The FactoryBase's subclasses usually provide the
     * implementation of this method.
     */
    class FactoryBase {
    public:
        virtual ~FactoryBase() {};
        virtual std::shared_ptr<ProductBase> factoryMethod() const = 0;

        /**
         * Note that the FactoryBase's class primary responsibility is
         * not creating products. Usually, it contains some core business logic that
         * relies on Product objects, returned by the factory method. Subclasses can
         * indirectly change that business logic by overriding the factory method and
         * returning a different type of product from it.
         */
        std::string someOperation() const {
            // call the factory method to create a Product object.
            std::shared_ptr<ProductBase> product = this->factoryMethod();  // <= abstract method (!)

            // now, use the product:
            std::string result1 = product->operation();
            std::string result2 = "FactoryBase: This factory's code has just created a " + result1;
            return result2;
        }
    };

    /**
     * Concrete FactoryBase classes override the factory method
     * in order to change the resulting product's type.
     */
    class ConcreteFactory1 : public FactoryBase {
        /**
         * Note that the signature of the method still uses the abstract product type,
         * even though the concrete product is actually returned from the method. This
         * way the FactoryBase can stay independent of concrete product classes.
         */
    public:
        std::shared_ptr<ProductBase> factoryMethod() const override {
            std::shared_ptr<ProductBase> product = std::make_shared<ConcreteProduct1>();
            return product;
        }
    };

    class ConcreteFactory2 : public FactoryBase {
    public:
        std::shared_ptr<ProductBase> factoryMethod() const override {
            std::shared_ptr<ProductBase> product = std::make_shared<ConcreteProduct2>();
            return product;
        }
    };

    /**
     * The client code works with an instance of a concrete FactoryBase, albeit through
     * its base interface. As long as the client keeps working with the FactoryBase
     * via the base interface, you can pass it any FactoryBase's subclass.
     */
    void clientCode(const std::shared_ptr<FactoryBase> factory) {

        std::cout
            << "Client (doesn't know the factory's concrete class type)" 
            << std::endl 
            << factory->someOperation() << std::endl;
    }
}

/**
 * The Application picks a factory's type
 * depending on the configuration or environment.
 */
void test_conceptual_example_02() {
    using namespace ConceptualExample02;

    std::cout << "Example launched with ConcreteFactory1:" << std::endl;
    std::shared_ptr<FactoryBase> factory1 = std::make_shared<ConcreteFactory1>();
    clientCode(factory1);
    std::cout << std::endl;

    std::cout << "Example launched with ConcreteFactory2:" << std::endl;
    std::shared_ptr<FactoryBase> factory2 = std::make_shared<ConcreteFactory2>();
    clientCode(factory2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
