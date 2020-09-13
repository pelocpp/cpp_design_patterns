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
        virtual std::string createTelevision() const = 0;
        virtual void switchOn() = 0;
    };

    // concrete Products provide various implementations
    // of the ITelevision interface
    class LEDTelevision : public ITelevision {
    public:
        virtual std::string createTelevision() const override {
            return "LED TV";
        }

        virtual void switchOn() override {
            std::cout << "Switched on my LED TV" << std::endl;
        };
    };

    class OledTelevision : public ITelevision {
    public:
        virtual std::string createTelevision() const override {
            return "Oled TV";
        }

        virtual void switchOn() override {
            std::cout << "Switched on my OLED TV" << std::endl;
        };
    };

    class AbstractFactory {

    public:
        virtual ~AbstractFactory() {};

        /**
         * Note that the FactoryBase's class primary responsibility is
         * not creating products. Usually, it contains some core business logic that
         * relies on concrete product objects, returned by the factory method. Subclasses can
         * indirectly change that business logic by overriding the factory method and
         * returning a different type of product from it.
         */

        virtual void orderTV() final {

            createTelevision();                // <= abstract method (!)
            float charge = shippingCharge();   // <= abstract method (!)
            std::cout << "Shipping charge: " << charge << " Euro" << std::endl;
        }

        virtual float totalCharge() final {

            float charge =
                shippingCharge() +      // <= abstract method (!)
                productionCharge();     // <= abstract method (!)

            return charge;
        }

        virtual ITelevision* orderTVExtended() final {
            return createTelevisionExtended();
        }

    protected:
        virtual float shippingCharge() const = 0;
        virtual float productionCharge() const = 0;
        virtual void createTelevision() = 0;
        virtual ITelevision* createTelevisionExtended() = 0;
    };


    class LEDTVFactory : public AbstractFactory {

    public:
        virtual void createTelevision() override  {
            std::cout << "Assembling LED tv" << std::endl;
        }

        virtual ITelevision* createTelevisionExtended() override {
            return new LEDTelevision();
        }

        virtual float shippingCharge() const override {
            return 1000;
        }

        virtual float productionCharge() const override {
            return 1500;
        }
    };

    class OledTVFactory : public AbstractFactory {
    public:
        virtual void createTelevision() override {
            std::cout << "Assembling Oled tv" << std::endl;
        }

        virtual ITelevision* createTelevisionExtended() override {
            return new OledTelevision();
        }

        virtual float shippingCharge() const override {
            return 2000;
        }

        virtual float productionCharge() const override {
            return 2500;
        }
    };

    void clientCode01(const std::shared_ptr<AbstractFactory> factory) {
        factory->orderTV();
    }

    void clientCode02(const std::shared_ptr<AbstractFactory> factory) {
        std::cout
            << "Mein neuer Fernseher kostet mich "
            << factory->totalCharge()
            << std::endl;

        ITelevision* tvPtr = factory->orderTVExtended();
        tvPtr->switchOn();
    }
}

void test_conceptual_example_03() {
    using namespace RealWorldFactoryMethod;

    std::cout << "Example launched with the LEDTVFactory.\n";
    std::shared_ptr<AbstractFactory> factory1 = std::make_shared<LEDTVFactory>();
    clientCode01(factory1);
    clientCode02(factory1);

    std::cout << "Example launched with the OledTVFactory.\n";
    std::shared_ptr<AbstractFactory> factory2 = std::make_shared<OledTVFactory>();
    clientCode01(factory2);
    clientCode02(factory2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
