// ===========================================================================
// ConceptualExample01.cpp // Builder Pattern
// ===========================================================================

#include <iomanip>
#include <list>
#include <memory>
#include <print>
#include <string>

namespace ConceptualExample_Builder_Pattern_Simple {

    class Product
    {
    private:
        std::list<std::string> m_parts;

    public:
        void add(const std::string& part) {
            m_parts.push_back(part);
        }

        void show() {
            std::println("Parts:");
            for (const auto& part : m_parts) {
                std::println("{:>10}", part);
            }
        }
    };

    class Builder
    {
    public:
        virtual ~Builder() = default;

        virtual void buildPartA() = 0;
        virtual void buildPartB() = 0;
        virtual std::shared_ptr<Product> getProduct() = 0;
    };

    class Director
    {
    public:
        void construct(std::shared_ptr<Builder>& builder) 
        {
            builder->buildPartA();
            builder->buildPartB();
        }
    };

    class ConcreteBuilder : public Builder
    {
    private:
        std::shared_ptr<Product> m_product;

    public:
        ConcreteBuilder()
            : m_product{ std::make_shared<Product>() }
        {}

        virtual ~ConcreteBuilder() = default;

        void buildPartA() override {
            m_product->add("Part A");
        }

        void buildPartB() override {
            m_product->add("Part B");
        }

        std::shared_ptr<Product> getProduct() override {
            return m_product;
        }
    };

    static void clientCode(Director& director)
    {
        // 'Product' is created through the builder - here: ConcreteBuilder
        std::shared_ptr<Builder> builder{ std::make_shared<ConcreteBuilder>() };

        // the builder is handed over to the director - including the product
        director.construct(builder);
        
        std::shared_ptr<Product> product{ builder->getProduct() };
        
        product->show();
    }
}

// function prototypes
void test_conceptual_example_01()
{
    using namespace ConceptualExample_Builder_Pattern_Simple;

    Director director;
    clientCode(director);
}

// ===========================================================================
// End-of-File
// ===========================================================================
