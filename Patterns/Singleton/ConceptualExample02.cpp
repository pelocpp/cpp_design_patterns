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
        static Singleton* m_instance;
        static std::mutex m_mutex;

    protected:
        Singleton(const std::string value) : m_value{ value } {}
        ~Singleton() {}

        std::string m_value;

    public:
        /**
         * Singletons should not be cloneable nor assignable nor moveable!
         */

        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) noexcept = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) noexcept = delete;

        /**
         * This is the static method that controls the access to the singleton
         * instance. On the first run, it creates a singleton object and places it
         * into the static field. On subsequent runs, it returns the client existing
         * object stored in the static field.
         */

        static Singleton* getInstance(const std::string& value);
        static Singleton* getInstanceEx(const std::string& value);

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

    Singleton* Singleton::m_instance{ nullptr };
    std::mutex Singleton::m_mutex{};

    /**
     * Static methods should be defined outside the class.
     */

    // simple implementation
    Singleton* Singleton::getInstance(const std::string& value)
    {
        if (m_instance == nullptr) {
            m_instance = new Singleton{ value };
        }

        return m_instance;
    }

    /**
     * The first time we call getInstanceEx we will lock the storage location
     * and then we make sure again that the variable is null and then we
     * set the value.
     */
    Singleton* Singleton::getInstanceEx(const std::string& value)
    {
        if (m_instance == nullptr)
        {
            std::lock_guard<std::mutex> lock{ m_mutex };
            if (m_instance == nullptr)  // <=== NOTE: double-check of m_instance being nullptr
            {
                m_instance = new Singleton{ value };
            }
        }

        return m_instance;
    }
}

void test_singleton_03()
{
    using namespace ConceptualExample02;

    Singleton* singleton1 { Singleton::getInstance("foo") };
    Singleton* singleton2 { Singleton::getInstance("bar") };

    std::cout << std::boolalpha << (singleton1 == singleton2) << std::endl;

    Singleton* singleton3 { Singleton::getInstanceEx("bar") };
    Singleton* singleton4 { Singleton::getInstanceEx("bar") };

    std::cout << std::boolalpha << (singleton3 == singleton4) << std::endl;

    std::cout << singleton1->value() << std::endl;
    std::cout << singleton2->value() << std::endl;
    std::cout << singleton3->value() << std::endl;
    std::cout << singleton4->value() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
