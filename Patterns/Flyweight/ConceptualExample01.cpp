// ===========================================================================
// ConceptualExample01.cpp // Flyweight Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <unordered_map>

// very simple example of flyweight pattern
namespace ConceptualExample01 {

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
            : m_brand(brand), m_model(model), m_color(color)
        {
        }

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
            : m_owner(owner), m_plates(plates)
        {
        }

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
        SharedState* m_repeatingState;

    public:
        Flyweight(const SharedState* shared_state) : m_repeatingState(new SharedState(*shared_state))
        {
        }

        Flyweight(const Flyweight& other) : m_repeatingState(new SharedState(*other.m_repeatingState))
        {
        }

        ~Flyweight()
        {
            delete m_repeatingState;
        }

        SharedState* getSharedState() const
        {
            return m_repeatingState;
        }

        void operation(const UniqueState& unique_state) const
        {
            std::cout << "Flyweight: Displaying shared (" << *m_repeatingState << ") and unique (" << unique_state << ") state.\n";
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
        std::unordered_map<std::string, Flyweight> m_flyweights;

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
                std::string key = this->getKey(state);
                std::pair<std::string, Flyweight> pair = std::make_pair<>(key, Flyweight(&state));
                this->m_flyweights.insert(pair);
            }
        }

        /**
         * Returns an existing Flyweight with a given state or creates a new one.
         */
        Flyweight getFlyweight(const SharedState& shared_state)
        {
            std::string key = this->getKey(shared_state);
            if (this->m_flyweights.find(key) == this->m_flyweights.end())
            {
                std::cout << "FlyweightFactory: Can't find a flyweight, creating new one." << std::endl;
                std::pair<std::string, Flyweight> pair = std::make_pair<>(key, Flyweight(&shared_state));
                this->m_flyweights.insert(pair);
            }
            else
            {
                std::cout << "FlyweightFactory: Reusing existing flyweight." << std::endl;
            }

            return this->m_flyweights.at(key);
        }

        void listFlyweights() const
        {
            size_t count = this->m_flyweights.size();
            std::cout << "FlyweightFactory: " << count << " flyweights:" << std::endl;

            for (std::pair<std::string, Flyweight> pair : this->m_flyweights) 
            {
                std::cout << pair.first << std::endl;
            }
        }
    };

    void addCarToDatabase(
        FlyweightFactory& factory,
        const std::string& plates, const std::string& owner,
        const std::string& brand, const std::string& model, const std::string& color)
    {
        std::cout << std::endl << "Client: Adding a car to database." << std::endl;

        const Flyweight& flyweight = factory.getFlyweight({ brand, model, color });
        
        // The client code either stores or calculates extrinsic state
        // and passes it to the flyweight's methods.
        flyweight.operation({ plates, owner });
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample01;

    /**
     * The client code usually creates a bunch of pre-populated flyweights in the
     * initialization stage of the application.
     */

    FlyweightFactory* factory = new FlyweightFactory (
        {
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"},
            {"Mercedes Benz", "C500", "red"},
            {"BMW", "M5", "red"}, 
            {"BMW", "X6", "white"}
        }
    );

    factory->listFlyweights();

    addCarToDatabase(
        *factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "M5",
        "red");

    addCarToDatabase(
        *factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "X1",
        "red");

    std::cout << std::endl;

    factory->listFlyweights();
    delete factory;
}

// ===========================================================================
// End-of-File
// ===========================================================================
