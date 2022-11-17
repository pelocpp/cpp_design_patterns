// ===========================================================================
// PluggableAdapterDesign.cpp // Adapter Pattern 
// Pluggable Adapter Design Pattern using Modern C++
// ===========================================================================

#include <iostream>
#include <string>
#include <functional>
#include <memory>

namespace PluggableAdapterDesignApproach {

    // =======================================================================
    // Legacy code

    class IBeverage
    {
    public:
        virtual void getBeverage() = 0;
    };

    class CoffeeMaker : public IBeverage
    {
    public:
        void brew() { 
            std::cout << "brewing coffee" << std::endl;
        }

        virtual void getBeverage() override {
            brew(); 
        }
    };

    // Interface already shipped & known to client
    void makeDrink(IBeverage& drink) {
        drink.getBeverage();             
    }

    // =======================================================================
    // New code (developed later)

    class JuiceMaker 
    {
    public:
        void squeeze() {
            std::cout << "making Juice" << std::endl;
        }
    };

    // making things compatible - using 'class adapter' strategy
    class Adapter : public IBeverage
    {   
    private:
        std::function<void()> m_request;

    public:
        // c'tors
        Adapter(std::unique_ptr<CoffeeMaker>& cm) 
            : m_request{ [&]() { cm->brew(); } } {}

        Adapter(std::unique_ptr<JuiceMaker>& jm) 
            : m_request{ [&]() { jm->squeeze(); } } {}

        virtual void getBeverage() override { 
            m_request();
        }
    };
}

// ===========================================================================

void test_pluggable_adapter_design()
{
    using namespace PluggableAdapterDesignApproach;

    std::unique_ptr<CoffeeMaker> cm = std::make_unique<CoffeeMaker>();
    Adapter adapter1(cm);
    makeDrink(adapter1);

    std::unique_ptr<JuiceMaker> jm = std::make_unique<JuiceMaker>();
    Adapter adapter2(jm);
    makeDrink(adapter2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
