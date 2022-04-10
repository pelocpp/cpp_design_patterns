// ===========================================================================
// OCP.cpp // Open Closed Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
#include <numeric>

enum class Color { Red, Green, Black, Gray };
enum class Size { Small, Medium, Large };

struct Product
{
    std::string m_name;
    Color       m_color;
    Size        m_size;
};

using Products = std::vector<std::shared_ptr<Product>>;

namespace AntiConceptualExampleOCP {

    struct ProductFilter 
    {
        static Products byColor(Products products, Color color)
        {
            Products result{};
            for (const auto& product : products) {
                if (product->m_color == color) {
                    result.push_back(product);
                }
            }
            return result;
        }

        static Products bySize(Products products, Size size)
        {
            Products result{};
            for (const auto& product : products) {
                if (product->m_size == size) {
                    result.push_back(product);
                }
            }
            return result;
        }

        static Products bySizeAndColor(Products products, Size size, Color color)
        {
            Products result{};
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
    struct Specification {
        virtual ~Specification() = default;
        virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
    };

    struct ColorSpecification : Specification<Product> 
    {
        Color m_color;
        ColorSpecification(Color color) : m_color(color) {}

        bool isSatisfied(const std::shared_ptr<Product>& product) const {
            return product->m_color == m_color; 
        }
    };

    struct SizeSpecification : Specification<Product> 
    {
        Size m_size;
        SizeSpecification(Size size) : m_size(size) {}
        
        bool isSatisfied(const std::shared_ptr<Product>& product) const {
            return product->m_size == m_size;
        }
    };

    template <typename T>
    using Items = std::vector<std::shared_ptr<T>>;

    template <typename T>
    struct Filter 
    {
        virtual Items<T> filter(Items<T> products, const Specification<T>& spec) = 0;
    };

    struct ProductFilter : Filter<Product>
    {
        Products filter(Products products, const Specification<Product>& spec)
        {
            Products result;
            for (auto& product : products) {
                if (spec.isSatisfied(product))
                    result.push_back(product);
            }
            return result;
        }
    };

    // logical 'And' specification
    template <typename T>
    struct AndSpecification : Specification<T> 
    {
        const Specification<T>& m_first;
        const Specification<T>& m_second;

        AndSpecification(const Specification<T>& first, const Specification<T>& second)
            : m_first{ first }, m_second{ second } {}

        bool isSatisfied(const std::shared_ptr<Product>& product) const {
            return m_first.isSatisfied(product) && m_second.isSatisfied(product);
        }
    };

    // logical 'And' specification using operator notation
    template <typename T>
    AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
        return { first, second };
    }

    // NEU !!!!!!!!!!!!!
    template <typename T>
    struct GenericSpecification : Specification<T>
    {
        std::initializer_list<Specification<T>> m_list;

       // bool m_result;

        //const Specification<T>& first;
        //const Specification<T>& second;

        template <typename ... TARGS>
        GenericSpecification(const Specification<TARGS>& ... args)
        { 
            m_list = { args ... };

            //const std::shared_ptr<Product>& product{};

            //m_result = (... && args.isSatisfied(product));
        }

        bool isSatisfied(const std::shared_ptr<Product>& product) const {
            // return first.isSatisfied(product) && second.isSatisfied(product);

           // bool result = (... && item.isSatisfied(product));

            bool result = std::accumulate(
                std::begin(m_list),
                std::end(m_list),
                true,
                [=](bool last, const auto& next) {
                    return  last && next.isSatisfied(product);
                }
            );

            return result;
        }
    };


}

void test_anti_conceptual_example_ocp ()
{
    using namespace AntiConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Black, Size::Large),
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

    Products products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Black, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    ProductFilter productFilter;
    ColorSpecification greenProducts = ColorSpecification{ Color::Green };

    for (const auto& product : productFilter.filter(products, greenProducts)) {
        std::cout << product->m_name << " is green" << std::endl;
    }
}

void test_conceptual_example_ocp_02()
{
    using namespace ConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Black, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    ProductFilter productFilter;
    ColorSpecification greenProducts = ColorSpecification{ Color::Green };
    SizeSpecification largeProducts = SizeSpecification{ Size::Large };

    for (const auto& product : productFilter.filter(products, greenProducts && largeProducts)) {
        std::cout << product->m_name << " is green and large" << std::endl;
    }
}

void test_conceptual_example_ocp_03()
{
    using namespace ConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Black, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    // combined specification
    AndSpecification<Product> specification = {
        SizeSpecification{ Size::Small },
        ColorSpecification{ Color::Gray }
    };

    // another combined specification - using overloaded operator &&
    AndSpecification<Product> anotherSpecification =
        SizeSpecification{ Size::Medium } && ColorSpecification{ Color::Red };

    auto computer = std::make_shared<Product>("Computer", Color::Gray, Size::Small);
    auto chair = std::make_shared<Product>("Chair", Color::Black, Size::Large);
    auto headset = std::make_shared<Product>("Headset", Color::Red, Size::Medium);

    bool result{};
    result = specification.isSatisfied(computer);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = specification.isSatisfied(chair);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    result = anotherSpecification.isSatisfied(headset);
    std::cout << "Result: " << std::boolalpha << result << std::endl;
}

// NEU !!!!!!!!!

void test_conceptual_example_ocp_10()
{
    using namespace ConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Computer", Color::Gray, Size::Small),
        std::make_shared<Product>("Chair", Color::Black, Size::Large),
        std::make_shared<Product>("Headset", Color::Red, Size::Medium)
    };

    // combined specification
    GenericSpecification<Product> specification {
        SizeSpecification{ Size::Small },
        ColorSpecification{ Color::Gray }
    };

    // another combined specification - using overloaded operator &&
    //AndSpecification<Product> anotherSpecification =
    //    SizeSpecification{ Size::Medium } && ColorSpecification{ Color::Red };

    auto computer = std::make_shared<Product>("Computer", Color::Gray, Size::Small);
    auto chair = std::make_shared<Product>("Chair", Color::Black, Size::Large);
    auto headset = std::make_shared<Product>("Headset", Color::Red, Size::Medium);

    bool result{};
    result = specification.isSatisfied(computer);
    std::cout << "Result: " << std::boolalpha << result << std::endl;

    //result = specification.isSatisfied(chair);
    //std::cout << "Result: " << std::boolalpha << result << std::endl;

    //result = anotherSpecification.isSatisfied(headset);
    //std::cout << "Result: " << std::boolalpha << result << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
