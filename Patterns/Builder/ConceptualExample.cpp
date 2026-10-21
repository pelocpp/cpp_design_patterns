// ===========================================================================
// ConceptualExample.cpp // Builder Pattern
// ===========================================================================

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

        void show() const {
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

        // ownership of the finished product moves to the caller
        virtual std::unique_ptr<Product> getProduct() = 0;
    };

    class Director
    {
    public:
        // the director only uses the builder, it does not own it
        void construct(Builder& builder)
        {
            builder.buildPartA();
            builder.buildPartB();
        }
    };

    class ConcreteBuilder : public Builder
    {
    private:
        std::unique_ptr<Product> m_product;

    public:
        ConcreteBuilder()
            : m_product{ std::make_unique<Product>() }
        {}

        void buildPartA() override {
            m_product->add("Part A");
        }

        void buildPartB() override {
            m_product->add("Part B");
        }

        std::unique_ptr<Product> getProduct() override {
            auto result = std::move(m_product);
            m_product = std::make_unique<Product>();   // builder can be reused
            return result;
        }
    };

    static void clientCode(Director& director)
    {
        std::unique_ptr<Builder> builder{ std::make_unique<ConcreteBuilder>() };

        director.construct(*builder);

        std::unique_ptr<Product> product{ builder->getProduct() };

        product->show();
    }
}

void test_conceptual_example()
{
    using namespace ConceptualExample_Builder_Pattern_Simple;

    Director director;
    clientCode(director);
}

// ===========================================================================
// End-of-File
// ===========================================================================
