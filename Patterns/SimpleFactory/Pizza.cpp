// ===========================================================================
// Factory a.k.a. Simple Factory Pattern // Pizzas
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace PizzasExample {

    class IPizza
    {
    public:
        virtual void prepare() = 0;
        virtual void bake() = 0;
        virtual void cut() = 0;
        virtual void box() = 0;
    };

    // helper class, to prevent compiler errors
    class Pizza : public IPizza
    {
        virtual void prepare() override {};
        virtual void bake() override {};
        virtual void cut() override {};
        virtual void box() override {};
    };

    class CheesePizza : public Pizza {};
    class GreekPizza : public Pizza {};
    class PepperoniPizza : public Pizza {};
    class ClamPizza : public Pizza {};
    class VeggiePizza : public Pizza {};


    std::shared_ptr<IPizza> orderPizza()
    {
        std::shared_ptr<IPizza> pizza{ std::make_shared<Pizza>()};

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

    std::shared_ptr<IPizza> orderPizza(std::string type)
    {
        std::shared_ptr<IPizza> pizza{ nullptr };

        if (type == std::string{ "cheese" }) {
            pizza = std::make_shared<CheesePizza>();
        }
        else if (type == std::string{ "greek" }) {
            pizza = std::make_shared<GreekPizza>();
        }
        else if (type == std::string{ "pepperoni" }) {
            pizza = std::make_shared<PepperoniPizza>();
        }

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

    /*
    *   What if we have some new pizzas:  ClamPizza and VeggiePizza
    *   and dont's support anymore GreekPizza?
    */

    class PizzaFactory
    {
    public:
        static std::shared_ptr<IPizza> createPizza(std::string type) {

            std::shared_ptr<IPizza> pizza{ nullptr };

            if (type == std::string{ "cheese" }) {
                pizza = std::make_shared<CheesePizza>();
            }
            else if (type == std::string{ "pepperoni" }) {
                pizza = std::make_shared<PepperoniPizza>();
            }
            else if (type == std::string{ "clam" }) {
                pizza = std::make_shared<ClamPizza>();
            }
            else if (type == std::string{ "veggie" }) {
                pizza = std::make_shared<VeggiePizza>();
            }

            return pizza;
        }
    };

    std::shared_ptr<IPizza> orderPizzaEx(std::string type)
    {
        std::shared_ptr<IPizza> pizza = PizzaFactory::createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
}

void test_pizza_01()
{
    using namespace PizzasExample;
    std::shared_ptr<IPizza> pizza = orderPizzaEx("pepperoni");
}

// ===========================================================================
// End-of-File
// ===========================================================================
