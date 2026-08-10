// ===========================================================================
// ConceptualExample01.cpp // Simple Factory
// ===========================================================================

#include <memory>
#include <print>
#include <string_view>
#include <utility>

namespace SimpleFactoryExample
{
    // =======================================================================
    // Product
    // =======================================================================

    class ProductBase
    {
    public:
        virtual ~ProductBase() = default;

        [[nodiscard]]
        virtual std::string_view getName() const = 0;

        virtual void anyOperation() const = 0;
    };

    class ConcreteProductA final : public ProductBase
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override
        {
            return "ConcreteProductA";
        }

        void anyOperation() const override
        {
            std::println("Working with ConcreteProduct A");
        }
    };

    class ConcreteProductB final : public ProductBase
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override
        {
            return "ConcreteProductB";
        }

        void anyOperation() const override
        {
            std::println("Working with ConcreteProduct B");
        }
    };

    // =======================================================================
    // Simple Factory
    // =======================================================================

    enum class ProductType
    {
        Variant_A,
        Variant_B
    };

    class ProductFactory final
    {
    public:
        [[nodiscard]]
        static std::unique_ptr<ProductBase>
            createProduct(ProductType type)
        {
            switch (type)
            {
            case ProductType::Variant_A:
                return std::make_unique<ConcreteProductA>();

            case ProductType::Variant_B:
                return std::make_unique<ConcreteProductB>();
            }

            // Should be unreachable for a valid ProductType.
            std::unreachable();
        }
    };

    // =======================================================================
    // Client
    // =======================================================================

    static void clientCode(ProductType type)
    {
        auto product = ProductFactory::createProduct(type);

        product->anyOperation();

        std::println("Created {}", product->getName());
    }
}

void test_conceptual_example_01()
{
    using namespace SimpleFactoryExample;

    std::println("Simple Factory: Create A");
    clientCode(ProductType::Variant_A);

    std::println();

    std::println("Simple Factory: Create B");
    clientCode(ProductType::Variant_B);
}

// ===========================================================================
// End-of-File
// ===========================================================================
