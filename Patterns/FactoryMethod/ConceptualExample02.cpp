// ===========================================================================
// ConceptualExample02.cpp // Factory Method
// ===========================================================================

#include <algorithm>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

namespace ConceptualExample02
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
    class FactoryBase {
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

    class LeastBusyFactory final : public FactoryBase
    {
    public:
        // constructs an instance, taking ownership of the given factories.
        explicit LeastBusyFactory(std::vector<std::unique_ptr<FactoryBase>> factories) 
            : m_factories{ std::move(factories) }
        {
            if (m_factories.empty()) {
                throw std::runtime_error{ "No factories provided." };
            }
        }

    private:
        std::unique_ptr<ProductBase> createProduct() const override {

            auto compareProducedProducts = [] (const auto& factory1, const auto& factory2) {
                return factory1->getNumberOfProductsProduced() < factory2->getNumberOfProductsProduced(); 
            };

            auto leastBusyFactory { 
                std::min_element(
                    m_factories.begin(),
                    m_factories.end(),
                    compareProducedProducts
                )
            };

            return (*leastBusyFactory)->requestProduct();
        }

        std::vector<std::unique_ptr<FactoryBase>> m_factories;
    };

    /**
     * Concrete FactoryBase classes override the factory method
     * in order to change the resulting product's type.
     */
    class ConcreteFactoryA final : public FactoryBase 
    {
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
}

void test_conceptual_example_02()
{
    using namespace ConceptualExample02;

    std::vector<std::unique_ptr<FactoryBase>> factories;

    // create 2 factories: one of type 'A' and another 'B' factory:
    factories.push_back(std::make_unique<ConcreteFactoryA>());
    factories.push_back(std::make_unique<ConcreteFactoryB>());

    // to get more interesting results,
    // preorder some products from specific factories
    for (size_t i : { 0, 0, 0, 0, 0, 1 }) {
        factories[i]->requestProduct();
    }

    // create a factory that automatically selects the least busy
    // factory from a list of given factories.
    LeastBusyFactory leastBusyFactory{ std::move(factories) };

    std::println("Starting a new production sequence ...");

    // build 10 cars from the least busy factory.
    for (size_t i{}; i != 10; ++i) {
        auto product{ leastBusyFactory.requestProduct() };
        std::println("{}", product->getName());
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
