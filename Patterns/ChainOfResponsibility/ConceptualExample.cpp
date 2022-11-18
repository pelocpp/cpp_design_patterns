// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <array>

namespace ConceptualExampleChainOfResponsibility {

    class Request
    {
    private:
        int m_type;
        std::string m_param;

    public:
        Request(int type, const std::string& param) 
            : m_type{ type }, m_param{ param } {}

        int getType() const { return m_type; }
        std::string getParam() const { return m_param; }
    };

    class HandlerBase
    {
    protected:
        std::shared_ptr<HandlerBase> m_successor;

    public:
        HandlerBase() : m_successor{ nullptr } {}

        virtual ~HandlerBase() {}

        virtual void handleRequest(const Request&) const = 0;

        void setSuccessor(std::shared_ptr<HandlerBase> ptr) {
            m_successor = ptr;
        }
    };

    class ConcreteHandlerA : public HandlerBase
    {
    public:
        ConcreteHandlerA() = default;

        void handleRequest(const Request& req) const override
        {
            if (req.getType() >= 0 && req.getType() < 10) {
                std::cout << "Concrete Handler A handles: " << req.getParam() << std::endl;
            }
            else if (m_successor) {
                m_successor->handleRequest(req);
            }
        }
    };

    class ConcreteHandlerB : public HandlerBase
    {
    public:
        ConcreteHandlerB() = default;

        void handleRequest(const Request& req) const override
        {
            if (req.getType() >= 10 && req.getType() < 20) {
                std::cout << "Concrete Handler B handles: " << req.getParam() << std::endl;
            }
            else if (m_successor) {
                m_successor->handleRequest(req);
            }
        }
    };

    class ConcreteHandlerC : public HandlerBase
    {
    public:
        ConcreteHandlerC() = default;

        void handleRequest(const Request& req) const override
        {
            if (req.getType() >= 20 && req.getType() < 30) {
                std::cout << "Concrete Handler C handles: " << req.getParam() << std::endl;
            }
            else if (m_successor) {
                m_successor->handleRequest(req);
            }
        }
    };

    /**
     * The client code is usually suited to work with a single handler.
     * In most cases, it is not even aware that the handler is part of a chain.
     */
    void clientCode(std::shared_ptr<HandlerBase> handler)
    {
        std::array<Request, 8> requests = {
            Request{ 7, std::string{ "Req. No.  7"} },
            Request{25, std::string{ "Req. No. 25"} },
            Request{17, std::string{ "Req. No. 17"} },
            Request{21, std::string{ "Req. No. 21"} },
            Request{18, std::string{ "Req. No. 18"} },
            Request{ 3, std::string{ "Req. No. 03"} },
            Request{19, std::string{ "Req. No. 19"} },
            Request{20, std::string{ "Req. No. 20"} }
        };

        for (const Request& request : requests) {
            handler->handleRequest(request);
        }
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExampleChainOfResponsibility;

    std::shared_ptr<HandlerBase> h1 { std::make_shared<ConcreteHandlerA>() };
    std::shared_ptr<HandlerBase> h2 { std::make_shared<ConcreteHandlerB>() };
    std::shared_ptr<HandlerBase> h3 { std::make_shared<ConcreteHandlerC>() };

    h1->setSuccessor(h2);
    h2->setSuccessor(h3);

    std::array<Request, 8> requests = {
        Request{ 7, std::string{ "Req. No.  7"} },
        Request{25, std::string{ "Req. No. 25"} },
        Request{17, std::string{ "Req. No. 17"} },
        Request{21, std::string{ "Req. No. 21"} },
        Request{18, std::string{ "Req. No. 18"} },
        Request{ 3, std::string{ "Req. No. 03"} },
        Request{19, std::string{ "Req. No. 19"} },
        Request{20, std::string{ "Req. No. 20"} }
    };

    for (Request request : requests) {
        h1->handleRequest(request);
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExampleChainOfResponsibility;

    std::shared_ptr<HandlerBase> h1 { std::make_shared<ConcreteHandlerA>() };
    std::shared_ptr<HandlerBase> h2 { std::make_shared<ConcreteHandlerB>() };
    std::shared_ptr<HandlerBase> h3 { std::make_shared<ConcreteHandlerC>() };

    h1->setSuccessor(h2);
    h2->setSuccessor(h3);

    clientCode(h1);
}

// ===========================================================================
// End-of-File
// ===========================================================================
