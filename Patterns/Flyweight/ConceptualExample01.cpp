// ===========================================================================
// ConceptualExample01.cpp // Flyweight Pattern // First Simple Approach
// ===========================================================================

#include <memory>
#include <print>
#include <string>
#include <unordered_map>

// First simple approach of the flyweight pattern
namespace ConceptualExample01 {

    /**
     * Flyweight class
     */
    class Flyweight
    {
    private:
        std::string m_sharedState;

    public:
        Flyweight(const std::string& sharedState)
            : m_sharedState{ sharedState }
        {}

        void operation(const std::string& uniqueState) const {

            std::println("Flyweight: Displaying shared ({}) and unique ({}) state.",
                m_sharedState, uniqueState);
        }
    };

    /**
     * Flyweight Factory
     */
    class FlyweightFactory
    {
    private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> m_flyweights;

    public:
        std::shared_ptr<Flyweight> getFlyweight(const std::string& sharedState)
        {
            if (m_flyweights.find(sharedState) == m_flyweights.end()) {

                std::println("FlyweightFactory: Creating new flyweight ({}).", sharedState);

                std::shared_ptr<Flyweight> flyweight{ std::make_shared<Flyweight>(sharedState) };

                m_flyweights[sharedState] = flyweight;
            }
            else {
                std::println("FlyweightFactory: Reusing existing flyweight ({}).", sharedState);
            }

            return m_flyweights[sharedState];
        }
    };

    /**
     * Client code
     */
    static void addFlyweight(FlyweightFactory& factory, const std::string& sharedState, const std::string& uniqueState) {

        std::shared_ptr<Flyweight> flyweight{ factory.getFlyweight(sharedState) };

        flyweight->operation(uniqueState);
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    FlyweightFactory factory{};

    addFlyweight(factory, "SharedState1", "UniqueStateA");
    addFlyweight(factory, "SharedState1", "UniqueStateB");
    addFlyweight(factory, "SharedState2", "UniqueStateC");
    addFlyweight(factory, "SharedState2", "UniqueStateD");
}

// ===========================================================================
// End-of-File
// ===========================================================================
