// ===========================================================================
// OCP.cpp // Open Closed Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <numeric>

enum class Color { Red, Green, Black, Gray };

enum class Size { Small, Medium, Large };

struct Product
{
    std::string m_name;
    Color       m_color;
    Size        m_size;
};

template <typename T>
using Products = std::vector<std::shared_ptr<T>>;

namespace AntiConceptualExampleOCP {

    struct ProductFilter 
    {
        static Products<Product> byColor(const Products<Product>& products, Color color)
        {
            Products<Product> result{};
            for (const auto& product : products) {
                if (product->m_color == color) {
                    result.push_back(product);
                }
            }
            return result;
        }

        static Products<Product> bySize(const Products<Product>& products, Size size)
        {
            Products<Product> result{};
            for (const auto& product : products) {
                if (product->m_size == size) {
                    result.push_back(product);
                }
            }
            return result;
        }

        static Products<Product> bySizeAndColor(const Products<Product>& products, Size size, Color color)
        {
            Products<Product> result{};
            for (const auto& product : products) {
                if (product->m_size == size && product->m_color == color) {
                    result.push_back(product);
                }
            }
            return result;
        }
    };
}

namespace ConceptualExampleOCP {

    template <typename T>
    struct ISpecification {
        virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
    };

    template <typename T>
    class ColorSpecification : public ISpecification<T> 
    {
    private:
        Color m_color;
        
    public:
        ColorSpecification(Color color) : m_color{ color } {}

        virtual bool isSatisfied(const std::shared_ptr<T>& product) const override {
            return product->m_color == m_color; 
        }
    };

    template <typename T>
    class SizeSpecification : public ISpecification<T>
    {
    private:
        Size m_size;
        
    public:
        SizeSpecification(Size size) : m_size{ size } {}
        
        virtual bool isSatisfied(const std::shared_ptr<T>& product) const override {
            return product->m_size == m_size;
        }
    };

    template <typename T>
    struct IFilter 
    {
        virtual Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const = 0;
    };

    template <typename T>
    struct ProductFilter : public IFilter<T>
    {
        virtual Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const override
        {
            Products<T> result{};
            for (const auto& product : products) {
                if (spec.isSatisfied(product))
                    result.push_back(product);
            }
            return result;
        }
    };

    // combining logical specifications - with logical 'and'
    template <typename T>
    class AndSpecification : public ISpecification<T>
    {
    private:
        const ISpecification<T>& m_first;
        const ISpecification<T>& m_second;

    public:
        AndSpecification(const ISpecification<T>& first, const ISpecification<T>& second)
            : m_first{ first }, m_second{ second } {}

        virtual bool isSatisfied(const std::shared_ptr<Product>& product) const override {
            return m_first.isSatisfied(product) && m_second.isSatisfied(product);
        }
    };

    // combining logical specifications - with logical 'and' using operator notation
    template <typename T>
    AndSpecification<T> operator&& (const ISpecification<T>& first, const ISpecification<T>& second) {
        return AndSpecification<T>{ first, second };
    }

    // combining multiple logical specifications - with variadic templates
    template <typename T>
    class GenericSpecification : public ISpecification<T>
    {
    private:
        std::vector<std::shared_ptr<ISpecification<T>>> m_vec;

    public:
        template <typename ... TArgs>
        GenericSpecification(const TArgs& ... args)
        {
           m_vec = { args ... };
        }

        virtual bool isSatisfied(const std::shared_ptr<T>& product) const override {

            bool result = std::accumulate (
                std::begin(m_vec),
                std::end(m_vec),
                true,
                [product] (bool last, const auto& next) -> bool {
                    bool tmp = next->isSatisfied(product);
                    return last && tmp;
                }
            );

            return result;
        }
    };

    struct ProductEx
    {
        std::string m_name;
        Color       m_color;
        Size        m_size;
        double      m_price;
    };

    class PriceSpecification : public ISpecification<ProductEx>
    {
    private:
        double m_price;
        
    public:
        PriceSpecification(double price) : m_price{ price } {}

        virtual bool isSatisfied(const std::shared_ptr<ProductEx>& product) const override {
            return product->m_price == m_price;
        }
    };
}

void test_anti_conceptual_example_ocp ()
{
    using namespace AntiConceptualExampleOCP;

    Products<Product> products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Green, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    for (const auto& product : ProductFilter::byColor(products, Color::Green))
        std::cout << product->m_name << " is green" << std::endl;
    
    for (const auto& product : ProductFilter::bySizeAndColor(products, Size::Large, Color::Green))
        std::cout << product->m_name << " is green & large" << std::endl;
}

void test_conceptual_example_ocp_01()
{
    using namespace ConceptualExampleOCP;

    Products<Product> products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Green, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    ProductFilter<Product> productFilter;

    ColorSpecification<Product> greenProducts {
        ColorSpecification<Product>{ Color::Green }
    };

    for (const auto& product : productFilter.filter(products, greenProducts)) {
        std::cout << product->m_name << " is green" << std::endl;
    }
}

void test_conceptual_example_ocp_02()
{
    using namespace ConceptualExampleOCP;

    Products<Product> products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Green, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    ProductFilter<Product> productFilter;

    ColorSpecification<Product> greenProducts {
        ColorSpecification<Product>{ Color::Green }
    };

    SizeSpecification largeProducts{
        SizeSpecification<Product>{ Size::Large }
    };

    for (const auto& product : productFilter.filter(products, greenProducts && largeProducts)) {
        std::cout << product->m_name << " is green and large" << std::endl;
    }
}

void test_conceptual_example_ocp_03()
{
    using namespace ConceptualExampleOCP;

    // combined specification
    AndSpecification<Product> specification {
        SizeSpecification<Product>{ Size::Small },
        ColorSpecification<Product>{ Color::Gray }
    };

    // another combined specification - using overloaded operator &&
    AndSpecification<Product> anotherSpecification {
        SizeSpecification<Product>{ Size::Medium } &&
        ColorSpecification<Product>{ Color::Red }
    };

    auto computer {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small) 
    };
    
    auto chair {
        std::make_shared<Product>("Chair", Color::Green, Size::Large)
    };
    
    auto headset {
         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    bool result{ specification.isSatisfied(computer) };
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = specification.isSatisfied(chair);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = anotherSpecification.isSatisfied(headset);
    std::cout << "Result: " << std::boolalpha << result << std::endl;
}

void test_conceptual_example_ocp_04()
{
    using namespace ConceptualExampleOCP;

    Products<Product> products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Green, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    // combined specification
    GenericSpecification<Product> specification {
        std::make_shared<SizeSpecification<Product>>(Size::Small) ,
        std::make_shared<ColorSpecification<Product>>(Color::Gray)
    };

    // another combined specification
    GenericSpecification<Product> anotherSpecification {
        std::make_shared<SizeSpecification<Product>>(Size::Medium) ,
        std::make_shared<ColorSpecification<Product>>(Color::Red)
    };

    auto computer{
        std::make_shared<Product>("Computer", Color::Gray, Size::Small)
    };

    auto chair { 
        std::make_shared<Product>("Chair", Color::Green, Size::Large) 
    };

    auto headset{ 
        std::make_shared<Product>("Headset", Color::Red, Size::Medium) 
    };

    bool result{ specification.isSatisfied(computer) };
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = specification.isSatisfied(chair);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = anotherSpecification.isSatisfied(headset);
    std::cout << "Result: " << std::boolalpha << result << std::endl;
}

void test_conceptual_example_ocp_05()
{
    using namespace ConceptualExampleOCP;

    Products<ProductEx> products
    {
        std::make_shared<ProductEx>("Computer", Color::Gray, Size::Small, 999.00),
        std::make_shared<ProductEx>("Chair", Color::Black, Size::Large, 79.00),
        std::make_shared<ProductEx>("Headset", Color::Red, Size::Medium, 19.99)
    };

    // combined specification
    GenericSpecification<ProductEx> specification{
        std::make_shared<SizeSpecification<ProductEx>>(Size::Small),
        std::make_shared<ColorSpecification<ProductEx>>(Color::Gray),
        std::make_shared<PriceSpecification>(12.00)
    };

    // another combined specification
    GenericSpecification<ProductEx> anotherSpecification{
        std::make_shared<SizeSpecification<ProductEx>>(Size::Medium),
        std::make_shared<ColorSpecification<ProductEx>>(Color::Red),
        std::make_shared<PriceSpecification>(19.99)
    };

    auto computer{
        std::make_shared<ProductEx>("Computer", Color::Gray, Size::Small, 999.00)
    };

    auto chair{
        std::make_shared<ProductEx>("Chair", Color::Green, Size::Large, 79.00)
    };

    auto headset{
        std::make_shared<ProductEx>("Headset", Color::Red, Size::Medium, 19.99)
    };

    bool result{ specification.isSatisfied(computer) };
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = specification.isSatisfied(chair);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = anotherSpecification.isSatisfied(headset);
    std::cout << "Result: " << std::boolalpha << result << std::endl;
}

void test_ocp()
{
    test_anti_conceptual_example_ocp();
    test_conceptual_example_ocp_01();
    test_conceptual_example_ocp_02();
    test_conceptual_example_ocp_03();
    test_conceptual_example_ocp_04();
    test_conceptual_example_ocp_05();
}

// ===========================================================================
// End-of-File
// ===========================================================================
