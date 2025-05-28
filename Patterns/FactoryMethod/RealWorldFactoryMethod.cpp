// ===========================================================================
// RealWorldFactoryMethod.cpp // Factory Method
// ===========================================================================

#include <memory>
#include <print>
#include <string>

namespace RealWorldFactoryMethod {

    // interface declares the methods that all concrete products must implement
    class ITelevision
    {
    public:
        virtual ~ITelevision() {}

        virtual std::string getManufacturer() const = 0;
        virtual void switchOn() = 0;
        virtual void switchOff() = 0;
    };

    // concrete Products provide various implementations of the ITelevision interface
    class LEDTelevision : public ITelevision
    {
    public:
        std::string getManufacturer() const final {
            return "LED TV";
        }

        void switchOn() override {
            std::println("Switched on my LED TV");
        };

        void switchOff() override {
            std::println("Switched on my LED TV");
        };
    };

    class OledTelevision : public ITelevision
    {
    public:
        std::string getManufacturer() const final {
            return "Oled TV";
        }

        void switchOn() override {
            std::println("Switched on my OLED TV");
        };

        void switchOff() override {
            std::println("Switched off my OLED TV");
        };
    };

    // ---------------------------------------------------------------------------

    class AbstractTVFactory
    {
    /**
    * Note that the FactoryBase's class primary responsibility is not only creating products.
    * Usually, it contains some core business logic that relies on concrete product objects,
    * returned by the factory method.
    *
    * Subclasses can indirectly change that business logic by overriding the factory method and
    * returning a different type of product from it.
    */
         
    // Protected Interface: protected virtual methods
    // these methods have to be provided by concrete factory classes.
    // These methods are NOT seen by any client
    protected:
        virtual bool manufactureTelevision() = 0;                        // take order, create order number, create invoice
        virtual std::unique_ptr<ITelevision> assembleTelevision() = 0;   // produce concrete television device
        virtual float shippingCharge() const = 0;
        virtual float productionCharge() const = 0;

    public:
        virtual ~AbstractTVFactory() {}

        // Public Interface:
        // These methods are available for clients
        // Three so called "Factory Methods" do exist in this example

        std::unique_ptr<ITelevision> orderTV() {

            if (manufactureTelevision()) {                                   // <= abstract method (!)

                // Note: client receives 'ITelevision' pointer
                std::unique_ptr<ITelevision> tvup{ assembleTelevision() };   // <= abstract method (!)
                return tvup;
            }

            // concrete factory cannot produce this tv currently
            std::unique_ptr<ITelevision> empty{};
            return empty;
        }
        
        void getOrderInformation() {

            float costsOfShippingCharge{ shippingCharge() };        // <= abstract method (!)
            std::println("Shipping charge: {} Euro", costsOfShippingCharge);


            float costsOfProduction{ productionCharge() };          // <= abstract method (!)
            std::println("Production charge: {} Euro", costsOfProduction);
        }

        float totalCharge() {

            float total{
                shippingCharge() +            // <= abstract method (!)
                productionCharge()            // <= abstract method (!)
            };

            return total;
        }
    };

    class LEDTVFactory : public AbstractTVFactory
    {
    protected:
        bool manufactureTelevision() override {
            std::println("Manufacturing LED TV");
            return true;
        }

        std::unique_ptr<ITelevision> assembleTelevision() override {
            std::println("Assembling LED TV");
            return std::make_unique<LEDTelevision>();
        }

        float shippingCharge() const override {
            return 1000.0F;
        }

        float productionCharge() const override {
            return 1500.0F;
        }
    };

    class OledTVFactory : public AbstractTVFactory {
    protected:
        bool manufactureTelevision() override {
            std::println("Manufacturing Oled TV");
            return true;
        }

        std::unique_ptr<ITelevision> assembleTelevision() override {
            std::println("Assembling Oled TV");
            return std::make_unique<OledTelevision>();
        }

        float shippingCharge() const override {
            return 2000.0F;
        }

        float productionCharge() const override {
            return 2500.0F;
        }
    };

    static void clientCode(const std::shared_ptr<AbstractTVFactory>& factory) {

        factory->getOrderInformation();

        std::println("My new television receiver costs me {} ", factory->totalCharge());

        std::unique_ptr<ITelevision> tvPtr{ factory->orderTV() };

        if (tvPtr != nullptr) {

            tvPtr->switchOn();

            std::println("My new TV is a {} device.", tvPtr->getManufacturer());
        }
    }
}

void test_real_world_example_televisions() {

    using namespace RealWorldFactoryMethod;

    std::println("Example launched with the LEDTVFactory.");

    std::shared_ptr<AbstractTVFactory> ledFactory{
        std::make_shared<LEDTVFactory>()
    };

    clientCode(ledFactory);
    std::println();

    std::println("Example launched with the OledTVFactory.");

    std::shared_ptr<AbstractTVFactory> oledFactory{
        std::make_shared<OledTVFactory>()
    };

    std::println();
    clientCode(oledFactory);
}

// ===========================================================================
// End-of-File
// ===========================================================================
