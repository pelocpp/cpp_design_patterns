// ===========================================================================
// ShoppingCart.cpp // Concrete Strategy Pattern
// ===========================================================================

#include <memory>
#include <print>
#include <string>

namespace ConceptualExample_ShoppingCart {

    class PricingStrategy {
    public:
        virtual ~PricingStrategy() = default;

        [[nodiscard]]
        virtual double price(double base) const = 0;
    };

    class NormalPrice : public PricingStrategy {
    public:
        [[nodiscard]]
        double price(double base) const override {
            return base;
        }
    };

    class BlackFridayPrice : public PricingStrategy {
    public:
        [[nodiscard]]
        double price(double base) const override {
            return base * 0.7;
        }
    };

    class ShoppingCart {
    private:
        const PricingStrategy& strategy;

    public:
        ShoppingCart(const PricingStrategy& strategy)
            : strategy(strategy)
        {}

        [[nodiscard]]
        double total(double base) const {
            return strategy.price(base);
        }
    };

    class Context
    {
        /**
         * The Context maintains a reference to one of the Strategy objects.
         * The Context does not know the concrete class of a strategy.
         * It should work with all strategies via the 'Strategy' interface.
         */

    private:
        std::unique_ptr<PricingStrategy> m_strategy;

    public:
        Context(std::unique_ptr<PricingStrategy> strategy)
            : m_strategy{ std::move(strategy) }
        {}

        ~Context() = default;

        void setStrategy(std::unique_ptr<PricingStrategy> strategy)
        {
            m_strategy = std::move(strategy);
        }

        /**
         * The Context delegates some work to the Strategy object instead of
         * implementing multiple versions of the algorithm on its own.
         */
        void doShopping()
        {
            double moneyAvailable = 100.0;
            std::println("moneyAvailable: {}", moneyAvailable);
            double moneyToSpend = m_strategy->price(moneyAvailable);
            std::println("moneyToSpend: {}", moneyToSpend);
        }
    };

    /**
     * The client code picks a concrete strategy and passes it to the context.
     * The client should be aware of the differences between strategies
     * in order to make the right choice.
     */

    static void clientCode01()
    {
        BlackFridayPrice blackFriday;

        ShoppingCart cart(blackFriday);

        std::println("{}", cart.total(100));   // 70
    }

    static void clientCode02()
    {
        std::println("Client: Strategy is set to 'Normal Prices':");

        Context context{ std::make_unique<NormalPrice>() };
        context.doShopping();
        std::println();

        std::println("Client: Strategy is set to 'Black Friday':");
        context.setStrategy(std::make_unique<BlackFridayPrice>());
        context.doShopping();
        std::println();
    }
}

void test_shopping_cart()
{
    using namespace ConceptualExample_ShoppingCart;

    clientCode01();
    clientCode02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
