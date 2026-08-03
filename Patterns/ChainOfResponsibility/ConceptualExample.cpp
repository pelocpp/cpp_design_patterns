// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <algorithm>
#include <array>
#include <memory>
#include <optional>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExampleChainOfResponsibility {

    class Request
    {
    private:
        std::size_t m_type;
        std::string m_param;

    public:
        Request(std::size_t type, std::string param) noexcept
            : m_type{ type }, m_param{ std::move(param) } 
        {}

        std::size_t getType() const noexcept { return m_type; }
        std::string_view getParam() const noexcept { return m_param; }
    };

    class HandlerBase
    {
    private:
        std::unique_ptr<HandlerBase> m_successor{ nullptr };

    protected:
        virtual std::optional<bool> handle(const Request& req) const noexcept = 0;

    public:
        HandlerBase() noexcept = default;

        // Template Method Pattern: Centrally manages the control flow of the chain.
        [[nodiscard]]
        std::optional<bool> handleRequest(const Request& req) const noexcept {

            // 1.) Own attempt
            if (auto result = handle(req); result.has_value()) {
                return result;
            }

            // 2.) Chaining, if a successor exists
            if (m_successor) {
                return m_successor->handleRequest(req);
            }

            return std::nullopt;
        }

        // returns the old successor (standard C++ interface design)
        std::unique_ptr<HandlerBase> setSuccessor(std::unique_ptr<HandlerBase> next) noexcept {
            std::swap(m_successor, next);
            return next;
        }
    };

    class ConcreteHandlerA : public HandlerBase
    {
    public:
        [[nodiscard]]
        std::optional<bool> handle(const Request& req) const noexcept override
        {
            if (req.getType() < 10) {
                std::println("Concrete Handler A handles: {}", req.getParam());
                return true;
            }

            return std::nullopt;  // That is not my responsibility
        }
    };

    class ConcreteHandlerB : public HandlerBase
    {
    public:
        [[nodiscard]]
        std::optional<bool> handle(const Request& req) const noexcept override
        {
            if (req.getType() >= 10 && req.getType() < 20) {
                std::println("Concrete Handler B handles: {}", req.getParam());
                return true;
            }

            return std::nullopt;
        }
    };

    class ConcreteHandlerC : public HandlerBase
    {
    public:
        [[nodiscard]]
        std::optional<bool> handle(const Request& req) const noexcept override
        {
            if (req.getType() >= 20 && req.getType() < 30) {
                std::println("Concrete Handler C handles: {}", req.getParam());
                return true;
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
        [[nodiscard]]
        std::optional<bool> handle(const Request& req) const noexcept override
        {
            std::println("Default Handler: Unhandled request type {}", req.getParam());
            return false;
        }
    };

    /**
     * The client code is usually suited to work with a single handler.
     * In most cases, it is not even aware that the handler is part of a chain.
     */
    static void clientCode_01(const HandlerBase& handler)
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
            auto result = handler.handleRequest(request);
            if (!result.has_value()) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
        std::println();
    }

    static void clientCode_02(const HandlerBase& handler)
    {
        std::array requests =
        {
            Request{ 7, std::string{ "Req. No.  7"} },
            Request{99, std::string{ "Req. No. 99"} },
            Request{20, std::string{ "Req. No. 20"} }
        };

        for (const Request& request : requests) {
            auto result = handler.handleRequest(request);
            if (!result.has_value()) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
        std::println();
    }
}

void test_conceptual_example() {

    using namespace ConceptualExampleChainOfResponsibility;

    auto chain          = std::make_unique<ConcreteHandlerA>();
    auto handler2       = std::make_unique<ConcreteHandlerB>();
    auto handler3       = std::make_unique<ConcreteHandlerC>();
    auto defaultHandler = std::make_unique<DefaultHandler>();

    // building the chain from back to front using unique_ptr (very safe)
    handler3->setSuccessor(std::move(defaultHandler));
    handler2->setSuccessor(std::move(handler3));
    chain->setSuccessor(std::move(handler2));

    clientCode_01(*chain);

    clientCode_02(*chain);
}

// ===========================================================================
// End-of-File
// ===========================================================================
