// ===========================================================================
// ConceptualExample01.cpp // Flyweight Pattern // First Simple Approach
// ===========================================================================

#include <cstddef>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>

// First simple approach of the flyweight pattern
namespace ConceptualExample01 {

    /**
     * Flyweight class
     */
    class Flyweight final
    {
    private:
        std::string m_sharedState;

    public:
        Flyweight(std::string_view sharedState)
            : m_sharedState{ sharedState }
        {}

        void operation(std::string_view uniqueState) const {

            std::println("Flyweight: Displaying shared ({}) and unique ({}) state.",
                m_sharedState, uniqueState);
        }
    };

    /**
     * Flyweight Factory
     */
    class FlyweightFactory final
    {
    private:
        // transparent hashing allows searching the map using `std::string_view` without copying.
        struct StringHash
        {
            using is_transparent = void; // enables heterogeneous lookups

            std::size_t operator()(std::string_view sv) const noexcept { 
                return std::hash<std::string_view>{}(sv);
            }
            
            std::size_t operator()(const std::string& s) const noexcept 
            {
                return std::hash<std::string>{}(s); 
            }
        };

        std::unordered_map<std::string, Flyweight, StringHash, std::equal_to<>> m_flyweights;

    public:
        // returns a const reference: The client does not own the flyweight
        [[nodiscard]]
        const Flyweight& getFlyweight(std::string_view sharedState)
        {
            // efficient lookup without `std::string` allocation (transparent hash/compare)
            if (auto it = m_flyweights.find(sharedState); it != m_flyweights.end()) {
                std::println("FlyweightFactory: reusing existing flyweight ({}).", sharedState);
                return it->second;
            }

            std::println("FlyweightFactory: creating new flyweight ({}).", sharedState);
            auto [it, inserted] = m_flyweights.emplace(
                std::string{ sharedState },   // allocation is okay/necessary here – only in the failure case
                Flyweight{ sharedState }
            );

            return it->second;
        }

        std::size_t flyweightCount() const noexcept { return m_flyweights.size(); }
    };

    /**
     * Client code
     */

    // passing the factory as a reference, states as `std::string_view`
    static void addFlyweight(FlyweightFactory& factory, std::string_view sharedState, std::string_view uniqueState) {

        const Flyweight& flyweight = factory.getFlyweight(sharedState);

        flyweight.operation(uniqueState);
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    FlyweightFactory factory;

    addFlyweight(factory, "SharedState1", "UniqueStateA");
    addFlyweight(factory, "SharedState1", "UniqueStateB");
    addFlyweight(factory, "SharedState2", "UniqueStateC");
    addFlyweight(factory, "SharedState2", "UniqueStateD");
}

// ===========================================================================
// End-of-File
// ===========================================================================
