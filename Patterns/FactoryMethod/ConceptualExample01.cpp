// ===========================================================================
// ConceptualExample01.cpp // Factory Method
// ===========================================================================

#include <string>
#include <memory>
#include <print>

namespace ConceptualExample01
{
    /**
     * Product Interface:
     * The Product Interface declares the operations
     * that all concrete products must implement.
     */
    class ProductBase
    {
    public:
        virtual ~ProductBase() {}

        virtual std::string getName() const = 0;
        virtual void anyOperation() = 0;
    };

    /**
     * Concrete Products provide various implementations of the Product interface.
     */
    class ConcreteProductA : public ProductBase 
    {
    public:
        std::string getName() const override {
            return "ConcreteProductA";
        }

        void anyOperation() override {
            std::println("Working with ConcreteProduct A");
        }
    };

    class ConcreteProductB : public ProductBase 
    {
    public:
        std::string getName() const override {
            return "ConcreteProductB";
        }

        void anyOperation() override {
            std::println("Working with ConcreteProduct B");
        }
    };

    // =======================================================================

    /**
     * The FactoryBase class declares the factory method
     * that is supposed to return an object of a Product class.
     * The FactoryBase's subclasses usually provide the implementation of this method.
     */
    class FactoryBase
    {
    public:
        FactoryBase() : m_numberOfProductsProduced{} {}

        virtual ~FactoryBase() {}       // always a virtual destructor

    private:
        virtual std::unique_ptr<ProductBase> createProduct() const = 0;

        /**
         * Note:
         * The FactoryBase's class primary responsibility is *not* creating products.
         * Usually, it contains some core business logic that relies on Product objects,
         * returned by the underlying factory method.
         * Subclasses can indirectly change that business logic by overriding 
         * the factory method and returning a different type of product from it.
         */
    public:
        std::unique_ptr<ProductBase> requestProduct() {

            // call the factory method to create a Product object.
            std::unique_ptr<ProductBase> product{ createProduct() };  // <= abstract method (!)

            // now, *use* the product:
            product->anyOperation();

            std::string name{ product->getName() };

            std::println("FactoryBase: This factory's code has just created a {}", name);

            // increment the number of products produced and return the new product
            ++m_numberOfProductsProduced;

            return product;
        }

        size_t getNumberOfProductsProduced() const {

            return m_numberOfProductsProduced;
        }

    private:
        size_t m_numberOfProductsProduced;
    };

    /**
     * Concrete FactoryBase classes override the factory method
     * in order to change the resulting product's type.
     */
    class ConcreteFactoryA final : public FactoryBase 
    {
        /**
         * Note that the signature of the method still uses the abstract product type,
         * even though the concrete product is actually returned from the method.
         * This way the FactoryBase can stay independent of concrete product classes:
         * ==> Compare with "Virtual Constructor" Pattern
         */
    private:
        std::unique_ptr<ProductBase> createProduct() const override {

            std::unique_ptr<ProductBase> product{ std::make_unique<ConcreteProductA>()};

            return product;
        }
    };

    class ConcreteFactoryB final : public FactoryBase
    {
    private:
        std::unique_ptr<ProductBase> createProduct() const override {

            std::unique_ptr<ProductBase> product{ std::make_unique<ConcreteProductB>() };

            return product;
        }
    };

    /**
     * The client code works with an instance of a concrete FactoryBase,
     * albeit through its base interface. 
     * As long as the client keeps working with the FactoryBase
     * via the base interface, you can pass it any FactoryBase's subclass.
     */

    static void clientCode(FactoryBase& factory) {

        std::println("Client: Not aware of the concrete creator's class (FactoryBase):");

        std::unique_ptr<ProductBase> product{ factory.requestProduct() };

        std::println("Created {}", product->getName());

        std::println("Total Products: {}", factory.getNumberOfProductsProduced());
    }
}

/**
 * The Application picks a factory's type
 * depending on the configuration or environment.
 */
void test_conceptual_example_01()
{
    using namespace ConceptualExample01;

    std::println("Example: Launched with ConcreteFactory A:");
    ConcreteFactoryA factoryA;
    clientCode(factoryA);
    std::println();

    std::println("Example: Launched with ConcreteFactory B:");
    ConcreteFactoryB factoryB;
    clientCode(factoryB);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
