// ===========================================================================
// ConceptualExample02.cpp - Flyweight Pattern
// ===========================================================================

#include <cstddef>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>

// Another example of the flyweight pattern
namespace ConceptualExample02 {

    /**
    * Flyweight Design Pattern
    *
    * Intent: Lets you fit more objects into the available amount of RAM by sharing
    * common parts of state between multiple objects, instead of keeping all of the
    * data in each object.
    */

    class SharedState
    {
    public:
        std::string m_brand;
        std::string m_model;
        std::string m_color;

        SharedState(std::string brand, std::string model, std::string color)
            : m_brand{ std::move(brand) }, m_model{ std::move(model) }, m_color{ std::move(color) }
        {}
    };

    class UniqueState
    {
    public:
        std::string m_owner;
        std::string m_plates;

        UniqueState(std::string owner, std::string plates)
            : m_owner{ std::move(owner) }, m_plates{ std::move(plates) }
        {}
    };
}

namespace std
{
    using namespace ConceptualExample02;

    template<>
    struct formatter<SharedState>
    {
        // parse the format string for this type
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin(); // should return position of '}' (hopefully)
        }

        // format by always writing its value:
        auto format(const SharedState& obj, std::format_context& ctx) const {
            return std::format_to(ctx.out(), "{}-{}-{}", obj.m_brand, obj.m_model, obj.m_color);
        }
    };

    template<>
    struct formatter<UniqueState>
    {
        // parse the format string for this type
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin(); // should return position of '}' (hopefully)
        }

        // format by always writing its value:
        auto format(const UniqueState& obj, std::format_context& ctx) const {
            return std::format_to(ctx.out(), "{}-{}", obj.m_owner, obj.m_plates);
        }
    };
}

namespace ConceptualExample02 {
    /**
     * The Flyweight stores a common portion of the state (also called intrinsic
     * state) that belongs to multiple real business entities. The Flyweight accepts
     * the rest of the state (extrinsic state, unique for each entity) via its
     * method parameters.
     */
    class Flyweight // contains shared State + unique state via method parameters
    {
    private:
        SharedState m_sharedState;

    public:
        explicit Flyweight(SharedState state) : m_sharedState{ std::move(state) } {}

        const SharedState& getSharedState() const noexcept {
            return m_sharedState;
        }

        void operation(const UniqueState& uniqueState) const
        {
            std::print("Flyweight: Displaying shared [{}, {}, {}] and unique [{}, {}] state.\n",
                m_sharedState.m_brand, m_sharedState.m_model, m_sharedState.m_color,
                uniqueState.m_owner, uniqueState.m_plates);
        }
    };
}

namespace ConceptualExample02 {

    /**
     * The Flyweight Factory creates and manages the Flyweight objects. It ensures
     * that flyweights are shared correctly. When the client requests a flyweight,
     * the factory either returns an existing instance or creates a new one, if it
     * doesn't exist yet.
     */
    class FlyweightFactory
    {
    private:
        std::unordered_map<std::string, Flyweight> m_flyweights;

        // generates the key as a string for comparisons
        static std::string getKey(const SharedState& ss) {
            return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
        }

    public:
        FlyweightFactory(std::initializer_list<SharedState> share_states) {
            for (const auto& state : share_states) {
                auto key = getKey(state);
                m_flyweights.try_emplace(std::move(key), state);
            }
        }

        /**
         * Returns an existing Flyweight with a given state or creates a new one (using a const reference)
         */

        const Flyweight& getFlyweight(const SharedState& sharedState) {

            auto key = getKey(sharedState);

            auto [it, inserted] = m_flyweights.try_emplace(key, sharedState);

            if (inserted) {
                std::println(
                    "FlyweightFactory: creating new flyweight ({}).",
                    sharedState);
            }
            else {
                std::println(
                    "FlyweightFactory: reusing existing flyweight ({}).",
                    sharedState);
            }

            return it->second;
        }

        std::size_t flyweightCount() const noexcept { return m_flyweights.size(); }

        void listFlyweights() const {
            std::println("FlyweightFactory: {} flyweights:", m_flyweights.size());
            for (const auto& [key, _] : m_flyweights) { // C++ 17 Structured Binding
                std::println("{}", key);
            }
        }
    };

    static void addCarToDatabase(
        FlyweightFactory& factory,
        const std::string& owner,
        const std::string& plates,
        const std::string& brand,
        const std::string& model,
        const std::string& color)
    {
        std::println();
        std::println("Client: Adding a car to database.");

        SharedState sharedState{ brand, model, color };

        const Flyweight& flyweight = factory.getFlyweight(sharedState);

        // client code passes unique state to the Flyweight's methods

        UniqueState uniqueState{ owner, plates };

        flyweight.operation(uniqueState);
    }

    static void addCarToDatabase(
        FlyweightFactory& factory,
        const SharedState& sharedState,
        const UniqueState& uniqueState)
    {
        std::println();
        std::println("Client: Adding a car to database.");

        const Flyweight& flyweight = factory.getFlyweight(sharedState);

        // client code passes unique state to the Flyweight's methods
        flyweight.operation(uniqueState);
    }
}

static void test_conceptual_example_02_a() {

    using namespace ConceptualExample02;

    /**
     * client code usually creates a bunch of pre-populated flyweights
     * in the initialization stage of the application.
     */

    FlyweightFactory factory
    {
        /* std::initializer_list of SharedState-objects
        */
        { "Chevrolet", "Camaro2018", "pink" },
        { "Mercedes Benz", "C300", "black" },
        { "Mercedes Benz", "C500", "red" },
        { "BMW", "M5", "red" },
        { "BMW", "X6", "white" }
    };

    factory.listFlyweights();

    SharedState sharedState{ "BMW", "M5", "red" };              // <== this car variant always exists
    UniqueState uniqueState{ "James Doe", "CL234IR" };

    addCarToDatabase(
        factory,
        sharedState,
        uniqueState
    );

    SharedState anotherSharedState{ "BMW", "X1", "red" };       // <== this car variant doesn't exist
    UniqueState anotherUniqueState{ "Henri Miller", "WA234AR" };

    addCarToDatabase(
        factory,
        anotherSharedState,
        anotherUniqueState
    );

    std::println();

    factory.listFlyweights();
}

static void test_conceptual_example_02_b() {

    using namespace ConceptualExample02;

    /**
     * client code usually creates a bunch of pre-populated flyweights
     * in the initialization stage of the application.
     */

    FlyweightFactory factory
    {
        /* std::initializer_list of Shared State objects
        */
        { "Chevrolet", "Camaro2018", "pink" },
        { "Mercedes Benz", "C300", "black" },
        { "Mercedes Benz", "C500", "red" },
        { "BMW", "M5", "red" },
        { "BMW", "X6", "white" }
    };

    factory.listFlyweights();

    addCarToDatabase(
        factory,
        "James Doe",
        "CL234IR",
        "BMW",
        "M5",         // <== this car variant always exists
        "red");

    addCarToDatabase(
        factory,
        "Henri Miller",
        "WA234AR",
        "BMW",
        "X1",         // <== this car variant doesn't exist
        "red");

    std::println();

    factory.listFlyweights();
}

void test_conceptual_example_02()
{
    test_conceptual_example_02_a();
    test_conceptual_example_02_b();
}

// ===========================================================================
// End-of-File
// ===========================================================================
