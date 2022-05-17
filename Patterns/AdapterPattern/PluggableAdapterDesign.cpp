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

    class Beverage {
    public:
        virtual void getBeverage() = 0;
    };

    class CoffeeMaker : public Beverage {
    public:
        void brew() { 
            std::cout << "brewing coffee" << std::endl;
        }

        virtual void getBeverage() override {
            brew(); 
        }
    };

    // Interface already shipped & known to client
    void make_drink(Beverage& drink) {
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
    class Adapter : public Beverage
    {   
    private:
        std::function<void()> m_request;

    public:
        // c'tors
        Adapter(std::unique_ptr<CoffeeMaker>& cm);
        Adapter(std::unique_ptr<JuiceMaker>& jm);

        virtual void getBeverage() override { 
            m_request();
        }
    };

    Adapter::Adapter(std::unique_ptr<CoffeeMaker>& cm)
    {
        m_request = [&]() { cm->brew(); };
    }

    Adapter::Adapter(std::unique_ptr<JuiceMaker>& jm)
    {
        m_request = [&]() { jm->squeeze(); };
    }
}

// ===========================================================================

void test_pluggable_adapter_design()
{
    using namespace PluggableAdapterDesignApproach;

    std::unique_ptr<CoffeeMaker> cmp = std::make_unique<CoffeeMaker>();
    Adapter adp1(cmp);
    make_drink(adp1);

    std::unique_ptr<JuiceMaker> jmp = std::make_unique<JuiceMaker>();
    Adapter adp2(jmp);
    make_drink(adp2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
