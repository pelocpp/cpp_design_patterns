// ===========================================================================
// ConceptualExample03.cpp // Factory Method / No Inheritance
// ===========================================================================

#include <string_view>
#include <memory>
#include <print>
#include <unordered_map>
#include <functional>

namespace ConceptualExample03
{
    // We describe the products still as an interface to allow for client-side polymorphism.
    class ProductBase
    {
    public:
        virtual ~ProductBase() = default;

        [[nodiscard]]
        virtual std::string_view getName() const = 0;
    };

    class ConcreteProductA : public ProductBase
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override { return "Product A"; }
    };

    class ConcreteProductB : public ProductBase
    {
    public:
        [[nodiscard]]
        std::string_view getName() const override { return "Product B"; }
    };

    // =======================================================================

    class FunctionalFactory
    {
    public:
        // We register function objects (lambdas) instead of factory classes.
        using CreatorMethod = std::function<std::unique_ptr<ProductBase>()>;

        void registerType(std::string_view typeName, CreatorMethod creator) {
            m_registry[std::string(typeName)] = std::move(creator);
        }

        [[nodiscard]]
        std::unique_ptr<ProductBase> createProduct(std::string_view typeName) const {
            auto it = m_registry.find(std::string(typeName));
            if (it != m_registry.end()) {
                return it->second(); // Calls the lambda
            }
            return nullptr;
        }

    private:
        std::unordered_map<std::string, CreatorMethod> m_registry;
    };
}

void test_conceptual_example_03()
{
    using namespace ConceptualExample03;

    FunctionalFactory factory;

    // registration takes place inline via lambda – no "FactoryA" class required!
    factory.registerType("A", []() { return std::make_unique<ConcreteProductA>(); });
    factory.registerType("B", []() { return std::make_unique<ConcreteProductB>(); });

    // client code simply uses the factory via ID/string.
    auto prod1 = factory.createProduct("A");
    auto prod2 = factory.createProduct("B");

    if (prod1) { 
        std::println("Created: {}", prod1->getName()); 
    }

    if (prod2) { 
        std::println("Created: {}", prod2->getName()); 
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
