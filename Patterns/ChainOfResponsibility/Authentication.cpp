// ===========================================================================
// Authentication.cpp // Chain of Responsibility
// ===========================================================================

#include <memory>
#include <print>
#include <string>
#include <utility>
#include <vector>

namespace chain_of_responsibility
{
    // the "request" travels through the chain
    struct Credentials
    {
        std::string user_name;
        std::string password;
    };

    class AuthHandler
    {
    public:
        virtual ~AuthHandler() = default;

        // takes ownership of the successor and returns a reference to it,
        // so calls can be chained: a->set_next(...).set_next(...)
        AuthHandler& setNext(std::unique_ptr<AuthHandler> next)
        {
            m_next = std::move(next);
            return *m_next;
        }

        // Template Method: the forwarding logic lives here, exactly once.
        [[nodiscard]] bool authenticate(const Credentials& credentials) const
        {
            if (!check(credentials)) {
                return false;
            }
            else {
                return m_next ? m_next->authenticate(credentials) : true;
            }
        }

    private:
        // each concrete handler implements only its own check.
        [[nodiscard]]
        virtual bool check(const Credentials& credentials) const = 0;

        std::unique_ptr<AuthHandler> m_next;
    };

    class UserNameHandler final : public AuthHandler
    {
    public:
        explicit UserNameHandler(std::string expected)
            : m_expected{ std::move(expected) }
        {}

    private:
        bool check(const Credentials& credentials) const override
        {
            const bool ok = credentials.user_name == m_expected;
            std::println("User name check {}", ok ? "succeeded" : "failed");
            return ok;
        }

        std::string m_expected;
    };

    class PasswordHandler final : public AuthHandler
    {
    public:
        explicit PasswordHandler(std::string expected) : m_expected{ std::move(expected) } {}

    private:
        bool check(const Credentials& credentials) const override
        {
            // Demo only: real code would compare password hashes, never plain text.
            const bool ok = credentials.password == m_expected;
            std::println("Password check {}", ok ? "succeeded" : "failed");
            return ok;
        }

        std::string m_expected;
    };
}

void test_authentication_example()
{
    using namespace chain_of_responsibility;

    auto chain = std::make_unique<UserNameHandler>("John");

    chain->setNext(std::make_unique<PasswordHandler>("12345678"));

    std::vector credentials {
        Credentials{ "John", "12345678" },
        Credentials{ "John", "wrong" },
        Credentials{ "Jane", "12345678" }
    };

    for (const auto& attempt : credentials) {
        /*const*/ bool ok = chain->authenticate(attempt);
        std::println("-> Authentication {}\n", ok ? "succeeded!" : "failed!");
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
