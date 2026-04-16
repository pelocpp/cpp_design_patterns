// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <print>

namespace ConceptualExampleChainOfResponsibility {

    class Request
    {
    private:
        std::size_t m_type;
        std::string m_param;

    public:
        Request(std::size_t type, const std::string& param) noexcept
            : m_type{ type }, m_param{ param } 
        {}

        std::size_t getType() const noexcept { return m_type; }
        std::string getParam() const noexcept { return m_param; }
    };

    class HandlerBase
    {
    protected:
        std::shared_ptr<HandlerBase> m_successor;

    public:
        HandlerBase() noexcept : m_successor{ nullptr } {}

        virtual ~HandlerBase() = default;

        virtual std::optional<bool> handleRequest(const Request&) const noexcept = 0;

        void setSuccessor(std::shared_ptr<HandlerBase> ptr) noexcept {
            m_successor = ptr;
        }

        std::shared_ptr<HandlerBase> getSuccessor() const noexcept {
            return m_successor;
        }
    };

    class ConcreteHandlerA : public HandlerBase
    {
    public:
        std::optional<bool> handleRequest(const Request& req) const noexcept override
        {
            if (req.getType() >= 0 && req.getType() < 10) {
                std::println("Concrete Handler A handles: {}", req.getParam());
                return true;
            }

            if (m_successor) {
                return m_successor->handleRequest(req);
            }

            return std::nullopt;
        }
    };

    class ConcreteHandlerB : public HandlerBase
    {
    public:
        std::optional<bool> handleRequest(const Request& req) const noexcept override
        {
            if (req.getType() >= 10 && req.getType() < 20) {
                std::println("Concrete Handler B handles: {}", req.getParam());
                return true;
            }

            if (m_successor) {
                return m_successor->handleRequest(req);
            }

            return std::nullopt;
        }
    };

    class ConcreteHandlerC : public HandlerBase
    {
    public:
        std::optional<bool> handleRequest(const Request& req) const noexcept override
        {
            if (req.getType() >= 20 && req.getType() < 30) {
                std::println("Concrete Handler C handles: {}", req.getParam());
                return true;
            }

            if (m_successor) {
                return m_successor->handleRequest(req);
            }

            return std::nullopt;
        }
    };

    /**
     * Default handler that catches unhandled requests.
     * Demonstrates the end of the chain.
     */
    class DefaultHandler : public HandlerBase
    {
    public:
        std::optional<bool> handleRequest(const Request& req) const noexcept override
        {
            std::println("Default Handler: Unhandled request type {}", req.getParam());
            return false;
        }
    };

    /**
     * The client code is usually suited to work with a single handler.
     * In most cases, it is not even aware that the handler is part of a chain.
     */
    static void clientCode_01(std::shared_ptr<HandlerBase> handler)
    {
        std::array requests =
        {
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
            auto result = handler->handleRequest(request);
            if (!result.has_value()) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
    }

    static void clientCode_02(std::shared_ptr<HandlerBase> handler)
    {
        std::array requests =
        {
            Request{ 7, std::string{ "Req. No.  7"} },
            Request{99, std::string{ "Req. No. 25"} },
            Request{20, std::string{ "Req. No. 20"} }
        };

        for (const Request& request : requests) {
            auto result = handler->handleRequest(request);
            if (!result.has_value()) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
    }
}

static void test_conceptual_example_01() {

    using namespace ConceptualExampleChainOfResponsibility;

    auto h1 { std::make_shared<ConcreteHandlerA>() };
    auto h2 { std::make_shared<ConcreteHandlerB>() };
    auto h3 { std::make_shared<ConcreteHandlerC>() };

    auto defaultHandler { std::make_shared<DefaultHandler>() };

    h1->setSuccessor(h2);
    h2->setSuccessor(h3);
    h3->setSuccessor(defaultHandler);

    clientCode_01(h1);
}

static void test_conceptual_example_02() {

    using namespace ConceptualExampleChainOfResponsibility;

    auto h1{ std::make_shared<ConcreteHandlerA>() };
    auto h2{ std::make_shared<ConcreteHandlerB>() };
    auto h3{ std::make_shared<ConcreteHandlerC>() };

    auto defaultHandler{ std::make_shared<DefaultHandler>() };

    h1->setSuccessor(h2);
    h2->setSuccessor(h3);
    h3->setSuccessor(defaultHandler);

    clientCode_02(h1);
}

void test_conceptual_example() {

    test_conceptual_example_01();
    test_conceptual_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
