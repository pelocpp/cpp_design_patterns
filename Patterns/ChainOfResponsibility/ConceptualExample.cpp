// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <array>

class Request
{
private:
    int m_type;
    std::string m_param;

public:
    explicit Request(int type, const std::string& param) : m_type(type), m_param(param) { }

    int getType() const { return m_type; }
    std::string getParam() const { return m_param; }
};

class Handler
{
protected:
    std::shared_ptr<Handler> m_successor;

public:
    Handler() : m_successor(nullptr) {}
    virtual ~Handler() {}

    virtual void handleRequest(const Request&) = 0;

    void setSuccessor(std::shared_ptr<Handler> ptr) {
        m_successor = ptr;
    }
};

class ConcreteHandlerA : public Handler
{
public:
    ConcreteHandlerA() = default;

    void handleRequest(const Request& req) override
    { 
        if (req.getType() >= 0 && req.getType() < 10) {
            std::cout << "Concrete Handler A handles: " << req.getParam() << std::endl;
        }
        else if(m_successor) {
            m_successor->handleRequest(req);
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    ConcreteHandlerB() = default;

    void handleRequest(const Request& req) override
    { 
        if(req.getType() >= 10 && req.getType() < 20) {
            std::cout << "Concrete Handler B handles: " << req.getParam() << std::endl;
        }
        else if(m_successor) {
            m_successor->handleRequest(req);
        }
    }
};

class ConcreteHandlerC : public Handler
{
public:
    ConcreteHandlerC() = default;

    void handleRequest(const Request& req) override
    { 
        if(req.getType() >= 20 && req.getType() < 30) {
            std::cout << "Concrete Handler C handles: " << req.getParam() << std::endl;
        }
        else if(m_successor) {
            m_successor->handleRequest(req);
        }
    }
};

void test_conceptual_example() {

    std::shared_ptr<Handler> h1 = std::make_shared<ConcreteHandlerA>();
    std::shared_ptr<Handler> h2 = std::make_shared<ConcreteHandlerB>();
    std::shared_ptr<Handler> h3 = std::make_shared<ConcreteHandlerC>();
    h1->setSuccessor(h2);
    h2->setSuccessor(h3);

    std::array<Request, 8> requests = {
        Request{ 7, std::string("Req. No.  7")},
        Request{25, std::string("Req. No. 25")},
        Request{17, std::string("Req. No. 17")}, 
        Request{21, std::string("Req. No. 21")}, 
        Request{18, std::string("Req. No. 18")}, 
        Request{ 3, std::string("Req. No. 03")},
        Request{19, std::string("Req. No. 19")}, 
        Request{20, std::string("Req. No. 20")}
    };

    for (Request request : requests) {
        h1->handleRequest(request);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================