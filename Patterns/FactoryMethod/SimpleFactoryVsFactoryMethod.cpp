// ===========================================================================
// SimpleFactoryVsFactoryMethod.cpp // Factory Method
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace SimpleFactoryVsFactoryMethod {

    // interface declares the methods that all concrete products must implement
    class ITelevision {
    public:
        virtual ~ITelevision() {}
        virtual std::string createTelevision() const = 0;
    };

    // concrete Products provide various implementations of the ITelevision interface
    class LEDTelevision : public ITelevision {
    public:
        std::string createTelevision() const override {
            return "LED TV";
        }
    };

    class OledTelevision : public ITelevision {
    public:
        std::string createTelevision() const override {
            return "Oled TV";
        }
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

            createTelevision();
            int charge = shippingCharge();
            std::cout << "Shipping charge: " << charge << " Euro" << std::endl;
        }

    protected:
        virtual int shippingCharge() const = 0;
        virtual void createTelevision() = 0;
    };


    class LEDTVFactory : public AbstractFactory {

    public:
        void createTelevision() override  {
            std::cout << "Assembling LED tv" << std::endl;
        }

        int shippingCharge() const override {
            return 1000;
        }
    };

    class OledTVFactory : public AbstractFactory {
    public:
        void createTelevision() override {
            std::cout << "Assembling Oled tv" << std::endl;
        }

        int shippingCharge() const override {
            return 2000;
        }
    };


    void clientCode(const std::shared_ptr<AbstractFactory> factory) {
        factory->orderTV();
    }
}


// The Application picks a factory's type depending on the configuration or environment
void test_conceptual_example_03() {
    using namespace SimpleFactoryVsFactoryMethod;

    std::cout << "App: Launched with the LEDTVFactory.\n";
    std::shared_ptr<AbstractFactory> factory1 = std::make_shared<LEDTVFactory>();
    clientCode(factory1);
    std::cout << std::endl;
    std::cout << "App: Launched with the OledTVFactory.\n";
    std::shared_ptr<AbstractFactory> factory2 = std::make_shared<OledTVFactory>();
    clientCode(factory2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
