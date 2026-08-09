// ===========================================================================
// ConceptualExample01.cpp // Factory Method
// ===========================================================================

#include <cstddef>
#include <memory>
#include <print>
#include <string>
#include <string_view>

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
        virtual ~ProductBase() = default;

        [[nodiscard]]
        virtual std::string_view getName() const = 0;
        
        virtual void anyOperation() const = 0;
    };

    /**
     * Concrete Products provide various implementations of the Product interface.
     */
    class ConcreteProductA final : public ProductBase 
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override {
            return "ConcreteProductA";
        }

        void anyOperation() const override {
            std::println("Working with ConcreteProduct A");
        }
    };

    class ConcreteProductB final : public ProductBase
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override {
            return "ConcreteProductB";
        }

        void anyOperation() const override {
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

        virtual ~FactoryBase() = default;

    protected:
        /**
         * Factory Method.
         *
         * Derived factories override this method to decide
         * which concrete Product is created.
         */
        [[nodiscard]]
        virtual std::unique_ptr<ProductBase> createProduct() = 0;

        /**
         * Note:
         * The FactoryBase's class primary responsibility is *not* creating products.
         * Usually, it contains some core business logic that relies on Product objects,
         * returned by the underlying factory method.
         */

    public:
        [[nodiscard]]
        std::unique_ptr<ProductBase> requestProduct() {

            // Factory Method:
            // Call the factory method to create a Product object.
            std::unique_ptr<ProductBase> product = createProduct();  // <= abstract method (!)

            // Core business logic:
            product->anyOperation();

            std::println("FactoryBase: This factory's code has just created a {}", product->getName());

            // Increment the number of products produced
            ++m_numberOfProductsProduced;

            // Return the new product
            return product;
        }

        [[nodiscard]]
        std::size_t getNumberOfProductsProduced() const noexcept {

            return m_numberOfProductsProduced;
        }

    private:
        std::size_t m_numberOfProductsProduced;
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
         * 
         * The example demonstrates that the factory method can return a polymorphic ownership type:
         * ==> Compare with "Virtual Constructor" Pattern!
         */
    private:
        [[nodiscard]]
        std::unique_ptr<ProductBase> createProduct() override {

            return std::make_unique<ConcreteProductA>();
        }
    };

    class ConcreteFactoryB final : public FactoryBase
    {
    private:
        [[nodiscard]]
        std::unique_ptr<ProductBase> createProduct() override {

            return std::make_unique<ConcreteProductB>();;
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

        auto product = factory.requestProduct();

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
