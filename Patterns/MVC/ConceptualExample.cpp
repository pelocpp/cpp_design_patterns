// ===========================================================================
// ConceptualExample.cpp // MVC
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <memory>

namespace ConceptualExample {

    // interface observer
    struct IValveObserver
    {
        virtual ~IValveObserver() {}

        virtual void valveValueChanged(int) = 0;
    };

    // interface valve model
    struct IValveModel
    {
        // getter/setter
        virtual int getMinimum() = 0;
        virtual int getMaximum() = 0;

        // methods
        virtual void widenOpening() = 0;
        virtual void narrowOpening() = 0;

        // observer functionality
        virtual void attach(std::shared_ptr<IValveObserver>) = 0;
        virtual void detach(std::shared_ptr<IValveObserver>) = 0;
    };

    // implementation of model
    class ValveModelImpl : public IValveModel
    {
    private:
        // "openness" of the valve is limited (range 0 to 100)
        const int Minimum = 0;
        const int Maximum = 100;

        // valve state
        int m_value;

        // list of observers
        std::list<std::shared_ptr<IValveObserver>> m_observers;

    public:
        ValveModelImpl()
        {
            m_value = (getMaximum() - getMinimum()) / 2;
        }

        virtual int getMinimum() override
        {
            return Minimum;
        }

        virtual int getMaximum() override
        {
            return Maximum;
        }

        virtual void widenOpening() override
        {
            if (m_value < getMaximum()) {

                m_value++;
                onValveValueChanged(m_value);
            }
        }

        virtual void narrowOpening() override
        {
            if (m_value > getMinimum()) {

                m_value--;
                onValveValueChanged(m_value);
            }
        }

        // subscription management methods
        void attach(std::shared_ptr<IValveObserver> observer) override {
            m_observers.push_back(observer);
        }

        void detach(std::shared_ptr<IValveObserver> observer) override {
            m_observers.remove(observer);
        }

    private:
        void onValveValueChanged(int value)
        {
            for (std::shared_ptr<IValveObserver> observer : m_observers) {
                observer->valveValueChanged(value);
            }
        }
    };

    // implementation of a view
    class ValveViewLabel : public IValveObserver, public std::enable_shared_from_this<ValveViewLabel>
    {
    private:
        std::shared_ptr<IValveModel> m_model{};

    public:

        ValveViewLabel() {}

        void attach(std::shared_ptr<IValveModel> model) {
            m_model = model;
            m_model->attach(shared_from_this());
        }

        virtual void valveValueChanged(int value) override
        {
            std::cout << "Label: " << value << std::endl;
        }
    };

    // implementation of two controllers
    class OpenValveController
    {
    private:
        std::shared_ptr<IValveModel> m_model;

    public:
        OpenValveController(std::shared_ptr<IValveModel> model)
        {
            m_model = model;
        }

        void onClick()
        {
            m_model->widenOpening();
        }
    };

    class CloseValveController
    {
    private:
        std::shared_ptr<IValveModel> m_model;

    public:
        CloseValveController(std::shared_ptr<IValveModel> model)
        {
            m_model = model;
        }

        void onClick()
        {
            m_model->narrowOpening();
        }
    };

    static void clientCode()
    {
        // create model
        std::shared_ptr<IValveModel> model{ std::make_shared<ValveModelImpl>() };

        // create view (being connected to the model)
        std::shared_ptr<ValveViewLabel> labelView{
            std::make_shared<ValveViewLabel>() 
        };
        labelView->attach(model);

        // create controller (being connected to the model)
        std::shared_ptr<OpenValveController> openController{ 
            std::make_shared<OpenValveController>(model) 
        };

        // create second controller (being connected to the model)
        std::shared_ptr<CloseValveController> closeController{
            std::make_shared<CloseValveController>(model) 
        };

        // wait for input - message loop
        char ch{ '?' };
        std::cout << "Waiting for input ['+' == open / '-' == close / 'q' == quit]" << std::endl;
        while (ch != 'q') {

            std::cin >> ch;

            if (ch == '+') {
                openController->onClick();
            }
            else if (ch == '-') {
                closeController->onClick();
            }
            else if (ch == 'q') {
                break;
            }
        }
    }
}

void test_conceptual_example () {
    using namespace ConceptualExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
