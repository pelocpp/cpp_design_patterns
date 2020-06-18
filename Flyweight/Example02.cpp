// ===========================================================================
// XXX.xpp (TBD) // Flyweight Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

/**
 * Flyweight Design Pattern
 *
 * Intent: Lets you fit more objects into the available amount of RAM by sharing
 * common parts of state between multiple objects, instead of keeping all of the
 * data in each object.
 */

struct SharedState
{
    std::string m_brand;
    std::string m_model;
    std::string m_color;

    SharedState(
        const std::string& brand, 
        const std::string& model,
        const std::string& color)
        : m_brand(brand), m_model(model), m_color(color) {}

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss)
    {
        return os << "[ " << ss.m_brand << " , " << ss.m_model << " , " << ss.m_color << " ]";
    }
};

struct UniqueState
{
    std::string m_owner;
    std::string m_plates;

    UniqueState(const std::string& owner, const std::string& plates)
        : m_owner(owner), m_plates(plates)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.m_owner << " , " << us.m_plates << " ]";
    }
};

/**
 * The Flyweight stores a common portion of the state (also called intrinsic
 * state) that belongs to multiple real business entities. The Flyweight accepts
 * the rest of the state (extrinsic state, unique for each entity) via its
 * method parameters.
 */
class Flyweight
{
private:
    SharedState* shared_state_;

public:
    Flyweight(const SharedState* shared_state) : shared_state_(new SharedState(*shared_state))
    {
    }

    Flyweight(const Flyweight& other) : shared_state_(new SharedState(*other.shared_state_))
    {
    }

    ~Flyweight()
    {
        delete shared_state_;
    }

    SharedState* shared_state() const
    {
        return shared_state_;
    }

    void Operation(const UniqueState& unique_state) const
    {
        std::cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique (" << unique_state << ") state.\n";
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
    std::string GetKey(const SharedState& ss) const
    {
        return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState> share_states)
    {
        for (const SharedState& ss : share_states)
        {
            std::string key = this->GetKey(ss);
            m_flyweights.insert(std::make_pair<std::string, Flyweight>(std::move(key), Flyweight(&ss)));
        }
    }

    /**
     * Returns an existing Flyweight with a given state or creates a new one.
     */
    Flyweight GetFlyweight(const SharedState& shared_state)
    {
        std::string key = this->GetKey(shared_state);
        if (m_flyweights.find(key) == m_flyweights.end())
        {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            m_flyweights.insert(std::make_pair(key, Flyweight(&shared_state)));
        }
        else
        {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return m_flyweights.at(key);
    }

    void ListFlyweights() const
    {
        size_t count = m_flyweights.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (std::pair<std::string, Flyweight> pair : m_flyweights)
        {
            std::cout << pair.first << "\n";
        }
    }
};

// ...
void AddCarToPoliceDatabase(
    FlyweightFactory& factory, const std::string& plates, const std::string& owner,
    const std::string& brand, const std::string& model, const std::string& color)
{
    std::cout << "\nClient: Adding a car to database.\n";
    const Flyweight& flyweight = factory.GetFlyweight({ brand, model, color });
    // The client code either stores or calculates extrinsic state and passes it
    // to the flyweight's methods.
    flyweight.Operation({ plates, owner });
}

/**
 * The client code usually creates a bunch of pre-populated flyweights in the
 * initialization stage of the application.
 */

void example_01 ()
{
    FlyweightFactory factory (
        {
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"},
            {"Mercedes Benz", "C500", "red"},
            {"BMW", "M5", "red"}, 
            {"BMW", "X6", "white"}
        }
    );

    factory.ListFlyweights();

    AddCarToPoliceDatabase(
        factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "M5",
        "red");

    AddCarToPoliceDatabase(
        factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "X1",
        "red");

    factory.ListFlyweights();
}


// ===========================================================================
// End-of-File
// ===========================================================================
