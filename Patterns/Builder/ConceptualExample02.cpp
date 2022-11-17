// ===========================================================================
// ConceptualExample02.cpp // Builder Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

/**
 * It makes sense to use the Builder pattern only when your products
 * are quite complex and require extensive configuration.
 *
 * Unlike in other creational patterns, different concrete builders can produce
 * unrelated products. In other words, results of various builders may not
 * always follow the same interface.
 */

class Product 
{
private:
    std::vector<std::string> m_parts;

public:
    void addPart(std::string part) {
        m_parts.push_back(part);
    }

    std::string operator()() {
        std::ostringstream oss;
        oss << "Product parts: ";
        for (size_t i = 0; i < m_parts.size(); i++) {
            if (m_parts[i] == m_parts.back()) {
                oss << m_parts[i];
            }
            else {
                oss << m_parts[i] << ", ";
            }
        }
        oss << std::endl;
        return oss.str();
    }
};

/**
 * The Builder interface specifies methods for creating
 * the different parts of Product objects.
 */
class Builder {
public:
    virtual ~Builder() {}

    virtual void createProducePartA() const = 0;
    virtual void createProducePartB() const = 0;
    virtual void createProducePartC() const = 0;

    virtual std::unique_ptr<Product> getProduct() = 0;
};

/**
 * The Concrete Builder classes follow the Builder interface and provide
 * specific implementations of the building steps. Your program may have several
 * variations of Builders, implemented differently.
 */
class ConcreteBuilder : public Builder {
private:
    std::unique_ptr<Product> m_product;

public:
    /**
     * A fresh builder instance should contain a blank product object,
     * which is used in further assembly.
     */
    ConcreteBuilder() {
        reset();
    }

    void reset() { 
        m_product = std::make_unique<Product>(); 
    }

    /**
     * All production steps work with the same product instance.
     */
    virtual void createProducePartA() const override {
        m_product->addPart(std::string("Part A1"));
    }

    virtual void createProducePartB() const override {
        m_product->addPart(std::string("Part B1"));
    }

    virtual void createProducePartC() const override {
        m_product->addPart(std::string("Part C1"));
    }

    /**
     * Concrete Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language).
     *
     * Usually, after returning the end result to the client, a builder instance
     * is expected to be ready to start producing another product. That's why
     * it's a usual practice to call the reset method at the end of the
     * 'getProduct' method body. However, this behavior is not mandatory, and
     * you can make your builders wait for an explicit reset call from the
     * client code before disposing of the previous result.
     */

     /**
      * Please be careful here with the memory ownership. Once you call
      * 'getProduct' the user of this function is responsable to release this
      * memory. Here could be a better option to use smart pointers to avoid
      * memory leaks, see below
      */

    std::unique_ptr<Product> getProduct() {
        std::unique_ptr<Product> result = std::move(m_product);
        reset();
        return result;
    }
};

/**
 * The Director is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing products according to a
 * specific order or configuration. Strictly speaking, the Director class is
 * optional, since the client can control builders directly.
 */
class Director {
private:
    std::shared_ptr<Builder> m_builder;

public:
    /**
     * The Director works with any builder instance that the client code passes
     * to it. This way, the client code may alter the final type of the newly
     * assembled product.
     */
    void setBuilder(std::shared_ptr<Builder> builder) {
        m_builder = builder;
    }

    /**
     * The Director can construct several product variations using the same
     * building steps.
     */

    void buildMinimalViableProduct() {
        m_builder->createProducePartA();
    }

    void buildFullFeaturedProduct() {
        m_builder->createProducePartA();
        m_builder->createProducePartB();
        m_builder->createProducePartC();
    }
};

/**
 * The client code creates a builder object, passes it to the director and then
 * initiates the construction process. The end result is retrieved from the
 * builder object.
 */
static void clientCode(Director& director)
{
    std::shared_ptr<ConcreteBuilder> builder = std::make_shared<ConcreteBuilder>();
    director.setBuilder(builder);
    std::cout << "Standard basic product:" << std::endl;
    director.buildMinimalViableProduct();
    std::unique_ptr<Product> product = builder->getProduct();
    std::cout << (*product)() << std::endl;

    std::cout << "Standard full featured product:" << std::endl;
    director.buildFullFeaturedProduct();
    product = builder->getProduct();
    std::cout << (*product)() << std::endl;

    // remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:" << std::endl;
    builder->createProducePartA();
    builder->createProducePartC();
    product = builder->getProduct();
    std::cout << (*product)() << std::endl;
}

// function prototypes
void test_conceptual_example_02()
{
    Director director;
    clientCode(director);
}

// ===========================================================================
// End-of-File
// ===========================================================================
