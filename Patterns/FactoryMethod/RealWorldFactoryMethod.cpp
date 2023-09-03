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

    class AbstractTVFactory 
    {
    protected:
        virtual void manufactureTelevision() = 0;
        virtual std::unique_ptr<ITelevision> assembleTelevision() = 0;
        virtual float shippingCharge() const = 0;
        virtual float productionCharge() const = 0;

    public:
        virtual ~AbstractTVFactory() {};

        /**
         * Note that the FactoryBase's class primary responsibility is
         * not creating products. Usually, it contains some core business logic that
         * relies on concrete product objects, returned by the factory method. Subclasses can
         * indirectly change that business logic by overriding the factory method and
         * returning a different type of product from it.
         */

        virtual void orderTV() final {         // <= final method (!)

            manufactureTelevision();           // <= abstract method (!)
            float charge = shippingCharge();   // <= abstract method (!)

            std::cout << "Shipping charge: " << charge << " Euro" << std::endl;
        }

        virtual std::unique_ptr<ITelevision> orderTVExtended() final {       // <= final method (!)
            
            // Note: client receives 'ITelevision' pointer
            std::unique_ptr<ITelevision> up = assembleTelevision();          // <= abstract method (!)
            
            return up;                     
        }

        virtual float totalCharge() final {       // <= final method (!)

            float charge =
                shippingCharge() +                // <= abstract method (!)
                productionCharge();               // <= abstract method (!)

            return charge;
        }
    };


    class LEDTVFactory : public AbstractTVFactory {
    protected:
        virtual void manufactureTelevision() override  {
            std::unique_ptr<ITelevision> newTV = assembleTelevision();
            std::cout << "Manufacturing LED TV" << std::endl;
        }

        virtual std::unique_ptr<ITelevision> assembleTelevision() override {
            std::cout << "Assembling LED TV" << std::endl;
            return std::make_unique<LEDTelevision>();
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
        virtual void manufactureTelevision() override {
            std::cout << "Manufacturing Oled TV" << std::endl;
        }

        virtual std::unique_ptr<ITelevision> assembleTelevision() override {
            std::cout << "Assembling Oled TV" << std::endl;
            return std::make_unique<OledTelevision>();
        }

        virtual float shippingCharge() const override {
            return 2000.0F;
        }

        virtual float productionCharge() const override {
            return 2500.0F;
        }
    };

    void clientCode01(const std::shared_ptr<AbstractTVFactory> factory) {
        factory->orderTV();
    }

    void clientCode02(const std::shared_ptr<AbstractTVFactory> factory) {
        std::cout
            << "My new television receiver costs me "
            << factory->totalCharge()
            << std::endl;

        std::unique_ptr<ITelevision> tvPtr = factory->orderTVExtended();
        tvPtr->switchOn();

        std::cout 
            << "My new TV is a " 
            << tvPtr ->getManufacturer()
            << " device." 
            << std::endl;
    }
}

void test_real_world_example_televisions() {

    using namespace RealWorldFactoryMethod;

    std::cout << "Example launched with the LEDTVFactory." << std::endl;
    std::shared_ptr<AbstractTVFactory> factory1 = std::make_shared<LEDTVFactory>();
    clientCode01(factory1);
    std::cout << std::endl;
    clientCode02(factory1);
    std::cout << std::endl;

    std::cout << "Example launched with the OledTVFactory." << std::endl;;
    std::shared_ptr<AbstractTVFactory> factory2 = std::make_shared<OledTVFactory>();
    std::cout << std::endl;
    clientCode02(factory2);
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
