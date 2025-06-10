// ===========================================================================
// ConceptualExample.cpp // MVC
// ===========================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
#include <list>
#include <memory>
#include <string>

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
        virtual void attach(const std::shared_ptr<IValveObserver>&) = 0;
        virtual void detach(const std::shared_ptr<IValveObserver>&) = 0;
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
        std::list<std::weak_ptr<IValveObserver>> m_observers;

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
        void attach(const std::shared_ptr<IValveObserver>& observer) override {
            m_observers.push_back(observer);
        }

        void detach(const std::shared_ptr<IValveObserver>& observer) override {  
            // https://stackoverflow.com/questions/10120623/removing-item-from-list-of-weak-ptrs
            m_observers.remove_if([&](std::weak_ptr<IValveObserver> wp) {
                return !observer.owner_before(wp) && !wp.owner_before(observer);
            });
        }

    private:
        void onValveValueChanged(int value)
        {
            for (std::weak_ptr<IValveObserver> observer : m_observers) {

                std::shared_ptr<IValveObserver> sp{ observer.lock() };
                if (sp != nullptr) {
                    sp->valveValueChanged(value);
                }
            }
        }
    };

    // implementation of a view
    class ValveViewLabel : public IValveObserver, public std::enable_shared_from_this<ValveViewLabel>
    {
    public:
        ValveViewLabel() {}

        void attach(std::shared_ptr<IValveModel> model) {
            model->attach(shared_from_this());
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

        model->detach(labelView);
    }
}

void test_conceptual_example () {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace ConceptualExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
