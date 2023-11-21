// ===========================================================================
// ConceptualExample.cpp // Flyweight Pattern (using smart pointer)
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// very simple example of flyweight pattern
namespace ConceptualExample {

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

        SharedState(const std::string& brand, const std::string& model, const std::string& color)
            : m_brand{ brand }, m_model{ model }, m_color{color } {}

        friend std::ostream& operator<<(std::ostream& os, const SharedState& ss);
    };

    std::ostream& operator<<(std::ostream& os, const SharedState& ss)
    {
        return os << "[ " << ss.m_brand << " , " << ss.m_model << " , " << ss.m_color << " ]";
    }

    class UniqueState
    {
    public:
        std::string m_owner;
        std::string m_plates;

        UniqueState(const std::string& owner, const std::string& plates)
            : m_owner{ owner }, m_plates{ plates }
        {}

        friend std::ostream& operator<<(std::ostream& os, const UniqueState& us);
    };

    std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.m_owner << " , " << us.m_plates << " ]";
    }

    /**
     * The Flyweight stores a common portion of the state (also called intrinsic
     * state) that belongs to multiple real business entities. The Flyweight accepts
     * the rest of the state (extrinsic state, unique for each entity) via its
     * method parameters.
     */
    class Flyweight
    {
    private:
        std::shared_ptr<SharedState> m_repeatingState;

    public:
        Flyweight(const SharedState& state)
        {
            m_repeatingState = std::make_shared<SharedState>(state);
        }

        ~Flyweight() {}

        std::shared_ptr<SharedState> getSharedState() const
        {
            return m_repeatingState;
        }

        void operation(const UniqueState& unique_state) const
        {
            std::cout
                << "Flyweight: Displaying shared ("
                << *m_repeatingState
                << ") and unique ("
                << unique_state
                << ") state."
                << std::endl;
        }
    };

    /**
     * The Flyweight Factory creates and manages the Flyweight objects. It ensures
     * that flyweights are shared correctly. When the client requests a flyweight,
     * the factory either returns an existing instance or creates a new one, if it
     * doesn't exist yet.
     */
    class FlyweightFactory
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<Flyweight>> m_flyweights;

        /**
         * Returns a Flyweight's string hash for a given state.
         */
        std::string getKey(const SharedState& ss) const
        {
            return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
        }

    public:
        FlyweightFactory(std::initializer_list<SharedState> share_states)
        {
            for (const SharedState& state : share_states)
            {
                std::string key = getKey(state);
                std::shared_ptr<Flyweight> flyweight = std::make_shared<Flyweight>(state);
                std::pair<std::string, std::shared_ptr<Flyweight>> pair = std::make_pair<>(key, flyweight);
                m_flyweights.insert(pair);
            }
        }

        /**
         * Returns an existing Flyweight with a given state or creates a new one.
         */
        std::shared_ptr<Flyweight> getFlyweight(const SharedState& sharedState)
        {
            std::string key = getKey(sharedState);
            if (m_flyweights.find(key) == m_flyweights.end())
            {
                std::cout << "FlyweightFactory: Can't find a flyweight, creating new one." << std::endl;
                std::shared_ptr<Flyweight> flyweight = std::make_shared<Flyweight>(sharedState);
                std::pair<std::string, std::shared_ptr<Flyweight>> pair = std::make_pair<>(key, flyweight);
                m_flyweights.insert(pair);
                // or
                // m_flyweights[key] = flyweight;
            }
            else
            {
                std::cout << "FlyweightFactory: Reusing existing flyweight." << std::endl;
            }

            return m_flyweights.at(key);
        }

        void listFlyweights() const
        {
            size_t count = m_flyweights.size();
            std::cout << "FlyweightFactory: " << count << " flyweights:" << std::endl;

            for (std::pair<std::string, std::shared_ptr<Flyweight>> pair : m_flyweights)
            {
                std::cout << pair.first << std::endl;
            }
        }
    };

    void addCarToDatabase(
        FlyweightFactory& factory,
        const std::string& owner,
        const std::string& plates, 
        const std::string& brand, 
        const std::string& model,
        const std::string& color)
    {
        std::cout << std::endl << "Client: Adding a car to database." << std::endl;
        std::shared_ptr<Flyweight> flyweight = factory.getFlyweight({ brand, model, color });
        
        // client code either stores or calculates extrinsic state
        // and passes it to the flyweight's methods.
        flyweight->operation({ owner, plates});
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample;

    /**
     * client code usually creates a bunch of pre-populated flyweights in the
     * initialization stage of the application.
     */

    FlyweightFactory factory {
        {
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"},
            {"Mercedes Benz", "C500", "red"},
            {"BMW", "M5", "red"},
            {"BMW", "X6", "white"}
        }
    };

    factory.listFlyweights();

    addCarToDatabase(
        factory,
        "James Doe",
        "CL234IR",
        "BMW",          
        "M5",       // <== this car variant always exists
        "red");

    addCarToDatabase(
        factory,
        "James Doe",
        "CL234IR",
        "BMW",
        "X1",       // <== this car variant doesn't exist
        "red");

    std::cout << std::endl;

    factory.listFlyweights();
}

// ===========================================================================
// End-of-File
// ===========================================================================
