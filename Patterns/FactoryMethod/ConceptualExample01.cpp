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
        virtual void operation() const = 0;
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

        void operation() const override {
            std::println("Working with ConcreteProduct A");
        }
    };

    class ConcreteProductB : public ProductBase 
    {
    public:
        std::string getName() const override {
            return "ConcreteProductB";
        }

        void operation() const override {
            std::println("Working with ConcreteProduct B");
        }
    };

    // =======================================================================

    /**
     * The FactoryBase class declares the factory method
     * that is supposed to return an object of a Product class.
     * The FactoryBase's subclasses usually provide the implementation of this method.
     */
    class FactoryBase {
    public:
        virtual ~FactoryBase() {};

        virtual std::unique_ptr<ProductBase> createProduct() const = 0;

        /**
         * Note:
         * The FactoryBase's class primary responsibility is *not* creating products.
         * Usually, it contains some core business logic that relies on Product objects,
         * returned by the factory method.
         * Subclasses can indirectly change that business logic by overriding 
         * the factory method and returning a different type of product from it.
         */
        std::string someOperation() const {

            // call the factory method to create a Product object.
            std::unique_ptr<ProductBase> product = createProduct();  // <= abstract method (!)

            // now, *use* the product:
            product->operation();
            std::string tmp{ product->getName() };

            std::string result{ "FactoryBase: This factory's code has just created a " + tmp };

            return result;
        }
    };

    /**
     * Concrete FactoryBase classes override the factory method
     * in order to change the resulting product's type.
     */
    class ConcreteFactoryA : public FactoryBase 
    {
        /**
         * Note that the signature of the method still uses the abstract product type,
         * even though the concrete product is actually returned from the method.
         * This way the FactoryBase can stay independent of concrete product classes.
         */
    public:
        std::unique_ptr<ProductBase> createProduct() const override {

            std::unique_ptr<ProductBase> product{ std::make_unique<ConcreteProductA>()};
            return product;
        }
    };

    class ConcreteFactoryB : public FactoryBase 
    {
    public:
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

    static void clientCode1(const FactoryBase& factory) {

        std::println("Client: Not aware of the concrete creator's class (FactoryBase):");

        std::unique_ptr<ProductBase> product = factory.createProduct();
        std::println("Created {}", product->getName());
    }

    static void clientCode2(const FactoryBase& factory) {

        std::println("Client: Not aware of the concrete creator's class (FactoryBase):");
        std::println("{}", factory.someOperation());
    }
}

/**
 * The Application picks a factory's type
 * depending on the configuration or environment.
 */
static void test_conceptual_example_01_a() {

    using namespace ConceptualExample01;

    std::println("Example: Launched with ConcreteFactory A:");
    ConcreteFactoryA factoryA;
    clientCode1(factoryA);
    std::println();

    std::println("Example: Launched with ConcreteFactory B:");
    ConcreteFactoryB factoryB;
    clientCode1(factoryB);
    std::println();
}

static void test_conceptual_example_01_b() {

    using namespace ConceptualExample01;

    std::println("Example: Launched with ConcreteFactory A:");
    ConcreteFactoryA factoryA;
    clientCode2(factoryA);
    std::println();

    std::println("Example: Launched with ConcreteFactory B:");
    ConcreteFactoryB factoryB;
    clientCode2(factoryB);
    std::println();
}

void test_conceptual_example_01()
{
    test_conceptual_example_01_a();
    test_conceptual_example_01_b();
}

// ===========================================================================
// End-of-File
// ===========================================================================
