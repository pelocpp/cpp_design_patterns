// ===========================================================================
// ConceptualExample01.cpp // Builder Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

namespace ConceptualExampleBuilder01 {

    class Product
    {
    private:
        std::list<std::string> m_parts;

    public:
        void add(std::string part)
        {
            m_parts.push_back(part);
        }

        void show()
        {
            std::cout << "Parts:";
            for (std::string part : m_parts)
                std::cout << "\t" << part;
        }
    };

    class Builder
    {
    public:
        virtual void buildPartA() = 0;
        virtual void buildPartB() = 0;
        virtual Product* getResult() = 0;
    };

    class Director
    {
    public:
        void construct(Builder* builder)
        {
            builder->buildPartA();
            builder->buildPartB();
        }
    };

    class ConcreteBuilder : public Builder
    {
    private:
        Product* _product = new Product();

    public:
        virtual void buildPartA() override
        {
            _product->add("Part A");
        }

        virtual void buildPartB() override
        {
            _product->add("Part B");
        }

        virtual Product* getResult() override
        {
            return _product;
        }
    };

    void clientCode(Director& director)
    {
        Builder* b1 = new ConcreteBuilder();

        director.construct(b1);
        auto p1 = b1->getResult();
        p1->show();
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
