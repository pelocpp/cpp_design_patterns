// ===========================================================================
// OCP.cpp // Open Closed Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product
{
    std::string  m_name;
    Color        m_color;
    Size         m_size;

    Product (std::string name, Color color, Size size) 
        : m_name{ name }, m_color{ color }, m_size{ size } {}
};

using Products = std::vector<std::shared_ptr<Product>>;

// Oder den hier: TODO
template <typename T>
using Items = std::vector<std::shared_ptr<T>>;

namespace AntiConceptualExampleOCP {

    struct ProductFilter 
    {
        static Products byColor(Products products, Color e_color)
        {
            Products result{};
            for (const auto& product : products) {
                if (product->m_color == e_color)
                    result.push_back(product);
            }
            return result;
        }

        static Products bySize(Products products, Size e_size)
        {
            Products result{};
            for (const auto& product : products) {
                if (product->m_size == e_size)
                    result.push_back(product);
            }
            return result;
        }

        static Products bySizeAndColor(Products products, Size e_size, Color e_color)
        {
            Products result{};
            for (const auto& product : products) {
                if (product->m_size == e_size && product->m_color == e_color)
                    result.push_back(product);
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
        Color e_color;
        ColorSpecification(Color e_color) : e_color(e_color) {}
        bool isSatisfied(const std::shared_ptr<Product>& product) const { return product->m_color == e_color; }
    };

    struct SizeSpecification : Specification<Product> 
    {
        Size e_size;
        SizeSpecification(Size e_size) : e_size(e_size) {}
        bool isSatisfied(const std::shared_ptr<Product>& product) const { return product->m_size == e_size; }
    };

    template <typename T>
    struct Filter 
    {
        virtual std::vector<std::shared_ptr<T>> filter(std::vector<std::shared_ptr<T>> products, const Specification<T>& spec) = 0;
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
        const Specification<T>& first;
        const Specification<T>& second;

        AndSpecification(const Specification<T>& first, const Specification<T>& second)
            : first{ first }, second{ second } {}

        bool isSatisfied(const std::shared_ptr<Product>& product) const {
            return first.isSatisfied(product) && second.isSatisfied(product);
        }
    };

    // logical 'And' specification using operator notation
    template <typename T>
    AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
        return { first, second };
    }
}

void test_anti_conceptual_example_ocp ()
{
    using namespace AntiConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Apple", Color::Green, Size::Small),
        std::make_shared<Product>("Tree", Color::Green, Size::Large),
        std::make_shared<Product>("House", Color::Blue, Size::Large)
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
        std::make_shared<Product>("Apple", Color::Green, Size::Small),
        std::make_shared<Product>("Tree", Color::Green, Size::Large),
        std::make_shared<Product>("House", Color::Blue, Size::Large)
    };

    ProductFilter productFilter;
    for (const auto& product : productFilter.filter(products, ColorSpecification(Color::Green))) {
        std::cout << product->m_name << " is green\n";
    }
}

void test_conceptual_example_ocp_02()
{
    using namespace ConceptualExampleOCP;

    Products products
    {
        std::make_shared<Product>("Apple", Color::Green, Size::Small),
        std::make_shared<Product>("Tree", Color::Green, Size::Large),
        std::make_shared<Product>("House", Color::Blue, Size::Large)
    };

    auto green_things = ColorSpecification{ Color::Green };
    auto large_things = SizeSpecification{ Size::Large };

    ProductFilter productFilter;
    for (const auto& product : productFilter.filter(products, green_things && large_things)) {
        std::cout << product->m_name << " is green and large\n";
    }

    // combined specification
    AndSpecification<Product> spec = {
        SizeSpecification{ Size::Large },
        ColorSpecification{ Color::Blue }
    };

    // another specification - using overloaded operator
    AndSpecification<Product> anotherSpec = 
        SizeSpecification{Size::Medium } && ColorSpecification{Color::Green};

    std::shared_ptr<Product> largeHouse = std::make_shared<Product>("House", Color::Blue, Size::Large);
    std::shared_ptr<Product> smallHouse = std::make_shared<Product>("House", Color::Blue, Size::Small);
    std::shared_ptr<Product> greenHouse = std::make_shared<Product>("House", Color::Green, Size::Medium);

     bool result1 = spec.isSatisfied(largeHouse);
     std::cout << "Result: " << std::boolalpha << result1 << std::endl;

     bool result2 = spec.isSatisfied(smallHouse);
     std::cout << "Result: " << std::boolalpha << result2 << std::endl;

     bool result3 = anotherSpec.isSatisfied(greenHouse);
     std::cout << "Result: " << std::boolalpha << result3 << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================



//
//enum class Color { Red, Green, Blue };
//enum class Size { Small, Medium, Large };
//
//struct Product
//{
//    std::string  m_name;
//    Color        m_color;
//    Size         m_size;
//};
//
//using Products = std::vector<Product*>;
//
//namespace AntiConceptualExampleOCP {
//
//    struct ProductFilter
//    {
//        static Products byColor(Products products, Color e_color)
//        {
//            Products result;
//            for (const auto& product : products) {
//                if (product->m_color == e_color)
//                    result.push_back(product);
//            }
//            return result;
//        }
//
//        static Products bySize(Products products, Size e_size)
//        {
//            Products result;
//            for (const auto& product : products) {
//                if (product->m_size == e_size)
//                    result.push_back(product);
//            }
//            return result;
//        }
//
//        static Products bySizeAndColor(Products products, Size e_size, Color e_color)
//        {
//            Products result;
//            for (const auto& product : products) {
//                if (product->m_size == e_size && product->m_color == e_color)
//                    result.push_back(product);
//            }
//            return result;
//        }
//    };
//}
//
//namespace ConceptualExampleOCP {
//
//    template <typename T>
//    struct Specification {
//        virtual ~Specification() = default;
//        virtual bool isSatisfied(T* product) const = 0;
//    };
//
//    struct ColorSpecification : Specification<Product>
//    {
//        Color e_color;
//        ColorSpecification(Color e_color) : e_color(e_color) {}
//        bool isSatisfied(Product* product) const { return product->m_color == e_color; }
//    };
//
//    struct SizeSpecification : Specification<Product>
//    {
//        Size e_size;
//        SizeSpecification(Size e_size) : e_size(e_size) {}
//        bool isSatisfied(Product* product) const { return product->m_size == e_size; }
//    };
//
//    template <typename T>
//    struct Filter
//    {
//        virtual std::vector<T*> filter(std::vector<T*> products, const Specification<T>& spec) = 0;
//    };
//
//    struct ProductFilter : Filter<Product>
//    {
//        Products filter(Products products, const Specification<Product>& spec)
//        {
//            Products result;
//            for (auto& product : products) {
//                if (spec.isSatisfied(product))
//                    result.push_back(product);
//            }
//            return result;
//        }
//    };
//
//    // Logical 'And' Specification
//    template <typename T>
//    struct AndSpecification : Specification<T>
//    {
//        const Specification<T>& first;
//        const Specification<T>& second;
//
//        AndSpecification(const Specification<T>& first, const Specification<T>& second)
//            : first{ first }, second{ second } {}
//
//        bool isSatisfied(T* product) const {
//            return first.isSatisfied(product) && second.isSatisfied(product);
//        }
//    };
//
//    template <typename T>
//    AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
//        return { first, second };
//    }
//}
//
//void test_anti_conceptual_example_ocp()
//{
//    using namespace AntiConceptualExampleOCP;
//
//    const Products products
//    {
//        new Product{"Apple", Color::Green, Size::Small},
//        new Product{"Tree", Color::Green, Size::Large},
//        new Product{"House", Color::Blue, Size::Large},
//    };
//
//    for (const auto& product : ProductFilter::byColor(products, Color::Green))
//        std::cout << product->m_name << " is green" << std::endl;
//
//    for (const auto& product : ProductFilter::bySizeAndColor(products, Size::Large, Color::Green))
//        std::cout << product->m_name << " is green & large" << std::endl;
//}
//
//void test_conceptual_example_ocp_01()
//{
//    using namespace ConceptualExampleOCP;
//
//    const Products products
//    {
//        new Product{"Apple", Color::Green, Size::Small},
//        new Product{"Tree", Color::Green, Size::Large},
//        new Product{"House", Color::Blue, Size::Large},
//    };
//
//    ProductFilter productFilter;
//    for (const auto& product : productFilter.filter(products, ColorSpecification(Color::Green))) {
//        std::cout << product->m_name << " is green\n";
//    }
//}
//
//void test_conceptual_example_ocp_02()
//{
//    using namespace ConceptualExampleOCP;
//
//    const Products products
//    {
//        new Product{"Apple", Color::Green, Size::Small},
//        new Product{"Tree", Color::Green, Size::Large},
//        new Product{"House", Color::Blue, Size::Large},
//    };
//
//    auto green_things = ColorSpecification{ Color::Green };
//    auto large_things = SizeSpecification{ Size::Large };
//
//    ProductFilter productFilter;
//    for (const auto& product : productFilter.filter(products, green_things&& large_things)) {
//        std::cout << product->m_name << " is green and large\n";
//    }
//
//    // combined specification
//    AndSpecification<Product> spec =
//        SizeSpecification{ Size::Large } && ColorSpecification{ Color::Blue };
//
//    Product* largeHouse = new Product{ "House", Color::Blue, Size::Large };
//    Product* smallHouse = new Product{ "House", Color::Blue, Size::Small };
//
//    bool result1 = spec.isSatisfied(largeHouse);
//    std::cout << "Result: " << std::boolalpha << result1 << std::endl;
//
//    bool result2 = spec.isSatisfied(smallHouse);
//    std::cout << "Result: " << std::boolalpha << result2 << std::endl;
//}
//
