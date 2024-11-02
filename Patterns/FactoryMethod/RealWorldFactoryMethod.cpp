// ===========================================================================
// RealWorldFactoryMethod.cpp // Factory Method
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

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

    // concrete Products provide various implementations
    // of the ITelevision interface
    class LEDTelevision : public ITelevision
    {
    public:
        virtual std::string getManufacturer() const final {
            return "LED TV";
        }

        virtual void switchOn() override {
            std::cout << "Switched on my LED TV" << std::endl;
        };

        virtual void switchOff() override {
            std::cout << "Switched off my LED TV" << std::endl;
        };
    };

    class OledTelevision : public ITelevision
    {
    public:
        virtual std::string getManufacturer() const final {
            return "Oled TV";
        }

        virtual void switchOn() override {
            std::cout << "Switched on my OLED TV" << std::endl;
        };

        virtual void switchOff() override {
            std::cout << "Switched off my OLED TV" << std::endl;
        };
    };

    // ---------------------------------------------------------------------------

    class AbstractTVFactory
    {
        // Protected Interface: protected virtual methods
        // these methods have to be provided by concrete factory classes.
        // These methods are NOT seen by any client

    protected:
        virtual bool manufactureTelevision() = 0;                        // take order, create order number, create invoice
        virtual std::unique_ptr<ITelevision> assembleTelevision() = 0;   // produce concrete television device
        virtual float shippingCharge() const = 0;
        virtual float productionCharge() const = 0;

    private:

    public:
        virtual ~AbstractTVFactory() {}

        /**
         * Note that the FactoryBase's class primary responsibility is
         * not creating products. Usually, it contains some core business logic that
         * relies on concrete product objects, returned by the factory method. Subclasses can
         * indirectly change that business logic by overriding the factory method and
         * returning a different type of product from it.
         */

        // Public Interface: public virtual methods (albeit final)
        // These methods are available for clients

        virtual void getOrderInformation() final {                  // <= final method (!)

            float costsOfShippingCharge{ shippingCharge() };        // <= abstract method (!)
            std::cout << "Shipping charge: " 
                << costsOfShippingCharge << " Euro" << std::endl;
            
            float costsOfProduction{ productionCharge() };          // <= abstract method (!)
            std::cout << "Production charge: " 
                << costsOfProduction << " Euro" << std::endl;
        }

        virtual std::unique_ptr<ITelevision> orderTV() final {               // <= final method (!)

            if (manufactureTelevision()) {

                // Note: client receives 'ITelevision' pointer
                std::unique_ptr<ITelevision> tvup{ assembleTelevision() };   // <= abstract method (!)
                return tvup;
            }

            // concrete factory cannot pruduce this tv currently
            std::unique_ptr<ITelevision> empty;
            return empty;

        }

        virtual float totalCharge() final {   // <= final method (!)

            float charge {
                shippingCharge() +            // <= abstract method (!)
                productionCharge()            // <= abstract method (!)
            };          

            return charge;
        }
    };


    class LEDTVFactory : public AbstractTVFactory {
    protected:
        virtual bool manufactureTelevision() override {
            std::cout << "Manufacturing LED TV" << std::endl;
            return true;
        }

        virtual std::unique_ptr<ITelevision> assembleTelevision() override {
            std::cout << "Assembling LED TV" << std::endl;
            std::unique_ptr<ITelevision> ledTV{ new LEDTelevision() };
            return ledTV;
        }

        virtual float shippingCharge() const override {
            return 1000.0F;
        }

        virtual float productionCharge() const override {
            return 1500.0F;
        }
    };

    class OledTVFactory : public AbstractTVFactory {
    protected:
        virtual bool manufactureTelevision() override {
            std::cout << "Manufacturing Oled TV" << std::endl;
            return true;
        }

        virtual std::unique_ptr<ITelevision> assembleTelevision() override {
            std::cout << "Assembling Oled TV" << std::endl;
            // return std::make_unique<OledTelevision>();
            std::unique_ptr<ITelevision> oledTV{ new OledTelevision() };
            return oledTV;
        }

        virtual float shippingCharge() const override {
            return 2000.0F;
        }

        virtual float productionCharge() const override {
            return 2500.0F;
        }
    };

    static void clientCode(const std::shared_ptr<AbstractTVFactory> factory) {

        factory->getOrderInformation();

        std::cout
            << "My new television receiver costs me "
            << factory->totalCharge()
            << std::endl;

        std::unique_ptr<ITelevision> tvPtr{ factory->orderTV() };

        tvPtr->switchOn();

        std::cout
            << "My new TV is a "
            << tvPtr->getManufacturer()
            << " device."
            << std::endl;
    }
}

void test_real_world_example_televisions() {

    using namespace RealWorldFactoryMethod;

    std::cout << "Example launched with the LEDTVFactory." << std::endl;
    std::shared_ptr<AbstractTVFactory> ledFactory{
        std::make_shared<LEDTVFactory>()
    };

    clientCode(ledFactory);
    std::cout << std::endl;

    std::cout << "Example launched with the OledTVFactory." << std::endl;
    std::shared_ptr<AbstractTVFactory> oledFactory{
        std::make_shared<OledTVFactory>()
    };

    std::cout << std::endl;
    clientCode(oledFactory);
}

// ===========================================================================
// End-of-File
// ===========================================================================
