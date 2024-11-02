// ===========================================================================
// ConceptualExample01.cpp // Factory Method
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample01 {

    class ProductBase
    {
    public:
        virtual ~ProductBase() {}

        virtual void showInfo() const = 0;
    };

    class ConcreteProduct1 : public ProductBase {
    public:
        void showInfo() const override
        {
            std::cout << "{ Product1 }" << std::endl;
        }
    };

    class ConcreteProduct2 : public ProductBase {
    public:
        void showInfo() const override
        {
            std::cout << "{ Product2 }" << std::endl;
        }
    };

    class FactoryBase
    {
    public:
        virtual std::shared_ptr<ProductBase> FactoryMethod(int type) = 0;
    };

    class ConcreteFactory : public FactoryBase
    {
    public:
        std::shared_ptr<ProductBase> FactoryMethod(int type) override
        {
            std::shared_ptr<ProductBase> product;

            switch (type)
            {
            case 1:
                product = std::make_shared<ConcreteProduct1>();
                break;

            case 2:
                product = std::make_shared<ConcreteProduct2>();
                break;

            default:
                std::string msg = "Invalid Troduct Id: " + std::to_string(type);
                throw std::runtime_error(msg);
            }

            return product;
        }
    };
}

void test_conceptual_example_01 ()
{
    using namespace ConceptualExample01;

    std::shared_ptr<FactoryBase> factory{
        std::make_shared<ConcreteFactory>()
    };

    std::shared_ptr<ProductBase> product{ 
        factory->FactoryMethod(1) 
    };

    product->showInfo();
    product = factory->FactoryMethod(2);
    product->showInfo();
}

// ===========================================================================
// End-of-File
// ===========================================================================
