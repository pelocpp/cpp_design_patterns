// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <algorithm>
#include <array>
#include <memory>
#include <print>
#include <string>
#include <string_view>

namespace ConceptualExampleChainOfResponsibility {

    class Request
    {
    private:
        std::size_t      m_type;
        std::string_view m_param;

    public:
        Request(std::size_t type, std::string_view param) noexcept
            : m_type{ type }, m_param{ param }
        {}

        std::size_t getType() const noexcept { return m_type; }
        std::string_view getParam() const noexcept { return m_param; }
    };

    enum class HandleResult
    {
        NotHandled,   // Not responsible
        Accepted,     // Processed
        Rejected      // Processed, but negative
    };

    class HandlerBase
    {
    private:
        std::unique_ptr<HandlerBase> m_successor{ nullptr };

    protected:
        virtual HandleResult handle(const Request& req) const noexcept = 0;

    public:
        HandlerBase() noexcept = default;

        virtual ~HandlerBase() = default;

        // Template Method Pattern: Centrally manages the control flow of the chain.

        // Chain of Responsibility: determines *who* handles.
        // Template Method:         determines *how* the chain is traversed.
        [[nodiscard]]
        HandleResult handleRequest(const Request& req) const noexcept {

            // own attempt
            if (auto result = handle(req); result != HandleResult::Rejected)
            {
                return result;
            }

            // no successor, quit
            if (!m_successor) {
                return HandleResult::NotHandled;
            }

            // chain, if a successor exists
            return m_successor->handleRequest(req);
        }

        HandlerBase& setSuccessor(std::unique_ptr<HandlerBase> successor) noexcept
        {
            m_successor = std::move(successor);
            return *m_successor;
        }
    };

    class ConcreteHandlerA : public HandlerBase
    {
    public:
        [[nodiscard]]
        HandleResult handle(const Request& req) const noexcept override
        {
            if (req.getType() < 10) {
                std::println("Concrete Handler A handles: {}", req.getParam());
                return HandleResult::Accepted;
            }

            return HandleResult::Rejected;  // That is not my responsibility
        }
    };

    class ConcreteHandlerB : public HandlerBase
    {
    public:
        [[nodiscard]]
        HandleResult  handle(const Request& req) const noexcept override
        {
            if (req.getType() >= 10 && req.getType() < 20) {
                std::println("Concrete Handler B handles: {}", req.getParam());
                return HandleResult::Accepted;
            }

            return HandleResult::Rejected;
        }
    };

    class ConcreteHandlerC : public HandlerBase
    {
    public:
        [[nodiscard]]
        HandleResult  handle(const Request& req) const noexcept override
        {
            if (req.getType() >= 20 && req.getType() < 30) {
                std::println("Concrete Handler C handles: {}", req.getParam());
                return HandleResult::Accepted;
            }

            return HandleResult::Rejected;
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
        HandleResult  handle(const Request& req) const noexcept override
        {
            std::println("Default Handler: Unhandled: {}", req.getParam());
            return HandleResult::Rejected;
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
            Request{  7, "Req. No.  7" },
            Request{ 25, "Req. No. 25" },
            Request{ 17, "Req. No. 17" },
            Request{ 21, "Req. No. 21" },
            Request{ 18, "Req. No. 18" },
            Request{  3, "Req. No. 03" },
            Request{ 19, "Req. No. 19" },
            Request{ 20, "Req. No. 20" }
        };

        for (const Request& request : requests) {
            auto result = handler.handleRequest(request);
            if (result == HandleResult::Rejected) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
        std::println();
    }

    static void clientCode_02(const HandlerBase& handler)
    {
        std::array requests =
        {
            Request{  7, "Req. No.  7" },
            Request{ 99, "Req. No. 99" },
            Request{ 20, "Req. No. 20" }
        };

        for (const Request& request : requests) {
            auto result = handler.handleRequest(request);
            if (result == HandleResult::Rejected) {
                std::println("  (Request type {} was not handled)", request.getType());
            }
        }
        std::println();
    }
}

void test_conceptual_example() {

    using namespace ConceptualExampleChainOfResponsibility;

    auto chain = std::make_unique<ConcreteHandlerA>();

    chain
        ->setSuccessor(std::make_unique<ConcreteHandlerB>())
        .setSuccessor(std::make_unique<ConcreteHandlerC>())
        .setSuccessor(std::make_unique<DefaultHandler>());

    clientCode_01(*chain);

    clientCode_02(*chain);
}

// ===========================================================================
// End-of-File
// ===========================================================================
