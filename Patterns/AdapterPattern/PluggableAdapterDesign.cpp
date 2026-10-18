// ===========================================================================
// PluggableAdapterDesign.cpp // Adapter Pattern 
// Pluggable Adapter Design Pattern using Modern C++
// ===========================================================================

#include <functional>
#include <iostream>
#include <utility>

namespace PluggableAdapterDesignApproach {

    // ---- Target interface: already shipped, known to the client ---------------
    class IBeverage {
    public:
        virtual ~IBeverage() = default;
        virtual void getBeverage() = 0;
    };

    static void makeDrink(IBeverage& drink) { drink.getBeverage(); }

    // ---- Adaptees: written independently, interfaces don't match --------------
    class CoffeeMaker {
    public:
        void brew() { std::cout << "brewing coffee\n"; }
    };

    class JuiceMaker {
    public:
        void squeeze() { std::cout << "making juice\n"; }
    };

    // ---- Pluggable adapter: the adaptation is injected as a callable ----------
    class BeverageAdapter final : public IBeverage {
    public:
        explicit BeverageAdapter(std::function<void()> request)
            : m_request{ std::move(request) } 
        {}

        void getBeverage() override { m_request(); }

    private:
        std::function<void()> m_request;
    };

    // ---- Compile-time alternative: adapter owns the adaptee by value ----------
    template <typename T>
    class JuiceAdapter final : public IBeverage {
    public:
        explicit JuiceAdapter(T maker) : m_maker{ std::move(maker) } {}

        void getBeverage() override { m_maker.squeeze(); }

    private:
        T m_maker;
    };

} // namespace PluggableAdapterDesignApproach

static void test_pluggable_adapter_design_01()
{
    using namespace PluggableAdapterDesignApproach;

    // Non-owning: the adaptee must outlive the adapter
    CoffeeMaker coffeeMaker;
    BeverageAdapter coffeeAdapter{ [&coffeeMaker] { coffeeMaker.brew(); } };
    makeDrink(coffeeAdapter);

    // Owning: the adaptee lives inside the lambda
    BeverageAdapter juiceAdapter{
        [juiceMaker = JuiceMaker{}]() mutable { 
            juiceMaker.squeeze();
        }
    };

    makeDrink(juiceAdapter);
}

static void test_pluggable_adapter_design_02()
{
    using namespace PluggableAdapterDesignApproach;

    JuiceAdapter adapter{ JuiceMaker{} };   // template argument deduced (C++17 CTAD)
    makeDrink(adapter);
}

void test_pluggable_adapter_design()
{
    test_pluggable_adapter_design_01();
    test_pluggable_adapter_design_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
