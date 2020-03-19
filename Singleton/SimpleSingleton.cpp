// ===========================================================================
// SimpleSingleton.cpp
// ===========================================================================

// https://refactoring.guru/design-patterns/singleton/cpp/example#example-0

#include <iostream>
#include <thread>
#include <sstream>

/**
 * The SimpleSingleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class SimpleSingleton
{

    /**
     * The SimpleSingleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    SimpleSingleton(const std::string value) : m_value(value)
    {
    }

    static SimpleSingleton* m_singleton;

    std::string m_value;

public:

    /**
     * Singletons should not be cloneable.
     */
    SimpleSingleton(SimpleSingleton& other) = delete;

    /**
     * Singletons should not be assignable.
     */
    void operator=(const SimpleSingleton&) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static SimpleSingleton* getInstance(const std::string& value);
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */
    void someBusinessLogic()
    {
        // ...
    }

    std::string value() const {
        return m_value;
    }
};

SimpleSingleton* SimpleSingleton::m_singleton = nullptr;;

/**
 * Static methods should be defined outside the class.
 */
SimpleSingleton* SimpleSingleton::getInstance(const std::string& value)
{
    /**
     * This is a safer way to create an instance. instance = new SimpleSingleton is
     * dangerouus in case two instance threads wants to access at the same time
     */

  // std::cout << "> getInstance" << std::endl;

    if (m_singleton == nullptr) {

        std::thread::id tid = std::this_thread::get_id();
        std::ostringstream ss;
        ss << tid;
        std::string s = ss.str();
        std::cout << "getInstance from " << s<< std::endl;
         
        m_singleton = new SimpleSingleton(value);
    }

    return m_singleton;
}

void ThreadFooSimple() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    SimpleSingleton* singleton = SimpleSingleton::getInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBarSimple() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    SimpleSingleton* singleton = SimpleSingleton::getInstance("BAR");
    std::cout << singleton->value() << "\n";
}

void test_simple_singleton()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
        "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
        "RESULT:\n";
    std::thread t1(ThreadFooSimple);
    std::thread t2(ThreadBarSimple);
    t1.join();
    t2.join();
}

// ===========================================================================
// End-of-File
// ===========================================================================
