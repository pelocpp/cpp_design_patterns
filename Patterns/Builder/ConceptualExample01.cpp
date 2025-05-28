// ===========================================================================
// ConceptualExample01.cpp // Builder Pattern
// ===========================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <memory>

namespace ConceptualExampleBuilder01 {

    class Product
    {
    private:
        std::list<std::string> m_parts;

    public:
        void add(const std::string& part) {
            m_parts.push_back(part);
        }

        void show() {
            std::cout << "Parts:" << std::endl;
            for (const auto& part : m_parts) {
                std::cout << std::setw(10) << part << std::endl;
            }
        }
    };

    class Builder
    {
    public:
        virtual ~Builder() {}

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

        virtual ~ConcreteBuilder() {}

        void buildPartA() override {
            m_product->add("Part A");
        }

        void buildPartB() override {
            m_product->add("Part B");
        }

        std::shared_ptr<Product> getProduct() override {
            return std::move(m_product);
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
    using namespace ConceptualExampleBuilder01;

    Director director;
    clientCode(director);
}

// ===========================================================================
// End-of-File
// ===========================================================================
