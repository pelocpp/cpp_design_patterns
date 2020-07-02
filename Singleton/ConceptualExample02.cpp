// ===========================================================================
// ConceptualExample02.cpp
// ===========================================================================

#include <iostream>
#include <thread>
#include <mutex>

namespace ConceptualExample02 {

    // It’s pretty easy to implement a sloppy Singleton.
    // You just need to hide constructorand implement a static creation method.

    /**
     * The Singleton class defines the `getInstance` method that serves as an
     * alternative to constructor and lets clients access the same instance of this
     * class over and over.
     */
    class Singleton
    {
        /**
         * The Singleton's constructor/destructor should always be private to
         * prevent direct construction/desctruction calls with the `new`/`delete`
         * operator.
         */
    private:
        static Singleton* m_pinstance;
        static std::mutex m_mutex;

    protected:
        Singleton(const std::string value) : m_value(value) {}
        ~Singleton() {}

        std::string m_value;

    public:
        /**
         * Singletons should not be cloneable.
         */
        Singleton(Singleton& other) = delete;

        /**
         * Singletons should not be assignable.
         */
        void operator=(const Singleton&) = delete;

        /**
         * This is the static method that controls the access to the singleton
         * instance. On the first run, it creates a singleton object and places it
         * into the static field. On subsequent runs, it returns the client existing
         * object stored in the static field.
         */

        static Singleton* getInstance(const std::string& value);

        /**
         * Finally, any singleton should define some business logic, which can be
         * executed on its instance.
         */
        void SomeBusinessLogic()
        {
            // ...
        }

        std::string value() const {
            return m_value;
        }
    };

    /**
     * Static methods should be defined outside the class.
     */

    Singleton* Singleton::m_pinstance{ nullptr };
    std::mutex Singleton::m_mutex;

    /**
     * The first time we call getInstance we will lock the storage location
     *      and then we make sure again that the variable is null and then we
     *      set the value. RU:
     */
    Singleton* Singleton::getInstance(const std::string& value)
    {
        if (m_pinstance == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_pinstance == nullptr)  // <=== NTOE: double-check of m_pinstance being nullptr
            {
                m_pinstance = new Singleton(value);
            }
        }

        return m_pinstance;
    }

    void threadFoo() {
        // Following code emulates slow initialization.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Singleton* singleton = Singleton::getInstance("FOO");
        std::cout << singleton->value() << "\n";
    }

    void threadBar() {
        // Following code emulates slow initialization.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Singleton* singleton = Singleton::getInstance("BAR");
        std::cout << singleton->value() << "\n";
    }
}

void test_singleton_02()
{
    using namespace ConceptualExample02;

    std::cout 
        << "Same value, then singleton was reused (!!!)\n" <<
        "Different values, then 2 singletons were created (???)\n\n" <<
        "RESULT:\n";

    std::thread t1(threadFoo);
    std::thread t2(threadBar);
    t1.join();
    t2.join();
}

// ===========================================================================
// End-of-File
// ===========================================================================
