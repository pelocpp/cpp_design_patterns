// ===========================================================================
// ConceptualExample.cpp - Adapter Pattern
// ===========================================================================

#include <algorithm>
#include <cassert>
#include <format>
#include <memory>
#include <print>
#include <string>

namespace ConceptualExample_Adapter_Pattern {

    /**
     * ITarget defines the domain-specific interface used by the client code
     */
    class ITarget
    {
    public:
        virtual ~ITarget() = default;

        [[nodiscard]]
        virtual std::string request() const = 0;
    };

    /**
     * Target implements ITarget - implementation usable by the client code
     */
    class Target final : public ITarget
    {
    public:
        [[nodiscard]]
        std::string request() const override
        {
            return "Target:  The target's default behavior.";
        }
    };

    /**
     * The Adaptee contains some useful behavior,
     * but its interface is incompatible with the existing client code.
     * The Adaptee needs some adaptation before the client code can use it.
     */
    class Adaptee
    {
    public:
        Adaptee() = default;

        [[nodiscard]]
        std::string specificRequest() const
        {
            constexpr std::string_view response{ ".eetpadA eht fo roivaheb laicepS" };

            return std::string{ response };
        }
    };

    /**
     * The Adapter translates the Target interface expected by the client
     * into calls to the Adaptee interface.
     */
    class Adapter final : public ITarget
    {
    private:
        std::unique_ptr<Adaptee> m_adaptee;

        /**
         * It's a personal design decision, whether `std::unique_ptr` is actually necessary,
         * or if a direct member (`Adaptee m_adaptee`) could make
         * the example even more modern and efficient. It depends, among other things,
         * on the size of the adaptee object:
         *
         * Adaptee m_adaptee;
         */
    public:
        explicit Adapter(std::unique_ptr<Adaptee> adaptee)
            : m_adaptee{ std::move(adaptee) }
        {
            assert(m_adaptee);
        }

        [[nodiscard]]
        std::string request() const override {

            std::string original{ m_adaptee->specificRequest() };

            std::reverse(original.begin(), original.end());

            return std::format("Adapter: (TRANSLATED) {}", original);
        }

        /**
         * The adapter does own a `std::unique_ptr` object,
         * therefore I make the adapter move-only.
         */

        Adapter(const Adapter&) = delete;
        Adapter& operator=(const Adapter&) = delete;

        Adapter(Adapter&&) noexcept = default;
        Adapter& operator=(Adapter&&) noexcept = default;
    };

    /**
     * The client code supports all classes that follow the Target interface.
     * Passed as a const reference, since the client does not need to own the object.
     */
    static void clientCode(const ITarget& target) {

        std::string response{ target.request() };

        std::println("{}", response);
    }

    static void test_conceptual_example_01() {

        auto adapter =
            std::make_unique<Adapter>(
                std::make_unique<Adaptee>()
            );

        clientCode(*adapter);
    }

    static void test_conceptual_example_02() {

        std::println("Client:  I can work fine with the Target object:");
        auto target = std::make_unique<Target>();
        clientCode(*target);

        auto adaptee = std::make_unique<Adaptee>();
        std::println("Client:  The Adaptee class has an incompatible interface:");
        std::string specificResponse = adaptee->specificRequest();
        std::println("Adaptee: {}", specificResponse);

        std::println("Client:  But I can work with the Adaptee via the Adapter:");
        auto adapter = std::make_unique<Adapter>(std::move(adaptee));
        clientCode(*adapter);
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample_Adapter_Pattern;

    test_conceptual_example_01();
    test_conceptual_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
