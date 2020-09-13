// ===========================================================================
// Factory a.k.a. Simple Factory Pattern // Mobile Phones
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace MobilePhonesExample {

    class IMobile
    {
    public:
        virtual void sendMessage() = 0;
    };

    class Samsung : public IMobile {
    public:

        void sendMessage() override
        {
            std::cout << "Samsung Selected" << std::endl;
        }
    };

    class IPhone : public IMobile {
    public:
        void sendMessage() override
        {
            std::cout << "IPhone Selected" << std::endl;
        }
    };

    void test_01()
    {
        std::shared_ptr<IMobile> mob1 = std::make_shared<Samsung>();
        mob1->sendMessage();

        std::shared_ptr<IMobile> mob2 = std::make_shared<IPhone>();
        mob2->sendMessage();
    }

    class MobileFactory {
    private:
        std::shared_ptr<IMobile> mobile = nullptr;

    public:
        MobileFactory() : mobile(nullptr) {}

        // getType method will return IMobile object creation  
        // according to the parameter passsed
        std::shared_ptr<IMobile> getType(std::string str) {

            if (str == std::string("Samsung"))
            {
                mobile = std::make_shared<Samsung>();
            }
            else if (str == std::string("iPhone")) {
                mobile = std::make_shared<IPhone>();
            }

            return mobile;
        }
    };
}

void test_mobile_phones_01()
{
    using namespace MobilePhonesExample;
    MobileFactory mobfactory;
    mobfactory.getType("Samsung")->sendMessage();
}

void test_mobile_phones_02()
{
    using namespace MobilePhonesExample;
    MobileFactory mobfactory;
    std::shared_ptr<IMobile> mobile = mobfactory.getType("Huawei");
    if (mobile == nullptr)
    {
        std::cout << "Wrong Type" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
