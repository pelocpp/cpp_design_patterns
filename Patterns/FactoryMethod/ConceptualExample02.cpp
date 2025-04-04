// ===========================================================================
// ConceptualExample02.cpp // Factory Method // Real-World Example
// ===========================================================================

#include <string>
#include <memory>
#include <print>

namespace ConceptualExample02
{
    /**
     * Product Interface
     */
    struct HotDrink
    {
        virtual void prepare(int volume) = 0;
        virtual void drink() = 0;
        virtual std::string name() = 0;
    };

    /**
     * Concrete Products provide various implementations of the Product interface.
     */
    struct Tea : HotDrink
    {
        void prepare(int volume) override
        {
            std::print("Take tea bag, boil water, pour {} ml, add some lemon", volume);
        }

        void drink() override
        {
            std::print("Hmmm, what a delicious tea :)");
        }

        std::string name () override
        {
            return "Tea";
        }
    };

    struct Coffee : HotDrink
    {
        void prepare(int volume) override
        {
            std::print("Coffee {} ml, add some milk and sugar", volume);
        }

        void drink() override
        {
            std::print("Hmmm, what a delicious coffee :)");
        }

        std::string name() override
        {
            return "Coffee";
        }
    };

    /**
     * More hypothetical make_drink() function that would take the name of a drink
     * and make that drink. Given a discrete set of cases, this can look rather tedious:
     */
    static std::unique_ptr<HotDrink> make_drink(std::string type)
    {
        std::unique_ptr<HotDrink> drink;

        if (type == "tea")
        {
            drink = std::make_unique<Tea>();
            drink->prepare(200);
        }
        else
        {
            drink = std::make_unique<Coffee>();
            drink->prepare(50);
        }

        return drink;
    }

    /**
     * The FactoryBase class declares the factory method
     * that is supposed to return an object of a Product class.
     * The FactoryBase's subclasses usually provide the implementation of this method.
     */

    struct HotDrinkFactory
    {
        virtual std::unique_ptr<HotDrink> makeDrink() const = 0;
    };

    /**
     * Concrete HotDrinkFactory classes override the factory method 'makeDrink'
     * in order to change the resulting product's type.
     */

    struct CoffeeFactory : HotDrinkFactory
    {
        std::unique_ptr<HotDrink> makeDrink() const override
        {
            return std::make_unique<Coffee>();
        }
    };

    struct TeaFactory : HotDrinkFactory
    {
        std::unique_ptr<HotDrink> makeDrink() const override
        {
            return std::make_unique<Tea>();
        }
    };

    static void clientCode(const HotDrinkFactory& factory) {

        std::println("Client: Not aware of the concrete creator's class (HotDrinkFactory):");

        std::unique_ptr<HotDrink> beverage = factory.makeDrink();
        std::println("Created {}", beverage->name());
        beverage->drink();
    }
}

/**
 * The Application picks a factory's type
 * depending on the configuration or environment.
 */

void test_conceptual_example_02()
{
    using namespace ConceptualExample02;

    std::println("Example: Launched with CoffeeFactory:");

    CoffeeFactory coffeeFactory;
    clientCode(coffeeFactory);
    std::println();

    TeaFactory teaFactory;
    clientCode(teaFactory);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
