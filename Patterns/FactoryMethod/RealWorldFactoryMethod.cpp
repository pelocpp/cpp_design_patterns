// ===========================================================================
// RealWorldFactoryMethod.cpp // Factory Method
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace RealWorldFactoryMethod {

    // interface declares the methods that all concrete products must implement
    class ITelevision {
    public:
        virtual ~ITelevision() {}
        virtual std::string getManufacturer() const = 0;
        virtual void switchOn() = 0;
        virtual void switchOff() = 0;
    };

    // concrete Products provide various implementations
    // of the ITelevision interface
    class LEDTelevision : public ITelevision {
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

    class OledTelevision : public ITelevision {
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

    class AbstractTVFactory {

    public:
        virtual ~AbstractTVFactory() {};

        /**
         * Note that the FactoryBase's class primary responsibility is
         * not creating products. Usually, it contains some core business logic that
         * relies on concrete product objects, returned by the factory method. Subclasses can
         * indirectly change that business logic by overriding the factory method and
         * returning a different type of product from it.
         */

        virtual void orderTV() final {

            manufactureTelevision();           // <= abstract method (!)
            float charge = shippingCharge();   // <= abstract method (!)

            std::cout << "Shipping charge: " << charge << " Euro" << std::endl;
        }

        virtual ITelevision* orderTVExtended() final {
            // client receives 'ITelevision' (e.g. 'Product') pointer
            return assembleTelevision();    // <= abstract method (!)
        }

        virtual float totalCharge() final {

            float charge =
                shippingCharge() +      // <= abstract method (!)
                productionCharge();     // <= abstract method (!)

            return charge;
        }

    protected:
        virtual void manufactureTelevision() = 0;
        virtual ITelevision* assembleTelevision() = 0;
        virtual float shippingCharge() const = 0;
        virtual float productionCharge() const = 0;
    };


    class LEDTVFactory : public AbstractTVFactory {
    protected:
        virtual void manufactureTelevision() override  {
            ITelevision* newTV = assembleTelevision();
            std::cout << "Manufacturing LED tv" << std::endl;
        }

        virtual ITelevision* assembleTelevision() override {
            std::cout << "Assembling LED tv" << std::endl;
            return new LEDTelevision();
        }

        virtual float shippingCharge() const override {
            return 1000;
        }

        virtual float productionCharge() const override {
            return 1500;
        }
    };

    class OledTVFactory : public AbstractTVFactory {
    protected:
        virtual void manufactureTelevision() override {
            std::cout << "Manufacturing Oled tv" << std::endl;
        }

        virtual ITelevision* assembleTelevision() override {
            std::cout << "Assembling Oled tv" << std::endl;
            return new OledTelevision();
        }

        virtual float shippingCharge() const override {
            return 2000;
        }

        virtual float productionCharge() const override {
            return 2500;
        }
    };

    void clientCode01(const std::shared_ptr<AbstractTVFactory> factory) {
        factory->orderTV();
    }

    void clientCode02(const std::shared_ptr<AbstractTVFactory> factory) {
        std::cout
            << "My new television receiver cost me "
            << factory->totalCharge()
            << std::endl;

        ITelevision* tvPtr = factory->orderTVExtended();
        tvPtr->switchOn();

        std::cout 
            << "My new TV is a " 
            << tvPtr ->getManufacturer()
            << " device." 
            << std::endl;
    }
}

void test_real_world_example() {

    using namespace RealWorldFactoryMethod;

    std::cout << "Example launched with the LEDTVFactory." << std::endl;
    std::shared_ptr<AbstractTVFactory> factory1 = std::make_shared<LEDTVFactory>();
    clientCode01(factory1);
    std::cout << std::endl;
    clientCode02(factory1);
    std::cout << std::endl;

    std::cout << "Example launched with the OledTVFactory." << std::endl;;
    std::shared_ptr<AbstractTVFactory> factory2 = std::make_shared<OledTVFactory>();
    clientCode01(factory2);
    std::cout << std::endl;
    clientCode02(factory2);
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
