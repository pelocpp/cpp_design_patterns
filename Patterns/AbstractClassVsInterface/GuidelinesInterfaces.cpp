// ===========================================================================
// GuidelinesInterfaces.cpp // Recommendations for the design of interfaces
// ===========================================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <print>
#include <span>
#include <stdexcept>
#include <string>

namespace GuidelinesInterfaces {

    // =======================================================================
    // Make interfaces precise

    struct Point
    {
        int m_x;
        int m_y;
    };

    struct Size
    {
        int m_height;
        int m_width;
    };


    static void draw_rect(int, int, int, int) {}
    static void draw_rectangle(Point top_left, Point bottom_right) {}
    static void draw_rectangle(Point top_left, Size height_width) {}

    static void guideline_precise_interface()
    {
        // Bad design: what do these four parameters mean? Great opportunities for making mistakes
        // What do 10, 20 mean?
        Point p{};
        void draw_rect(int, int, int, int);
        draw_rect(p.m_x, p.m_y, 10, 20);

        // --------------------------------------------------

        // Better design:
        draw_rectangle(p, Point{ 10, 20 });  // two corners
        draw_rectangle(p, Size{ 10, 20 });   // one corner and one size specification
    }

    // =======================================================================
    // Preconditions

    // State preconditions (if any)
    static double sqrt(double x) {
        //Expects(x >= 0); /* ... */
        assert(x >= 0);  //  "x may not be negative"
        return 0.0;
    };

    static void guideline_state_preconditions()
    {
        sqrt(-1.0);
    }

    // =======================================================================
    // Virtual Base Class Destructor

    class Base
    {
    public:
        ~Base()  // <== add keyword 'virtual' in front of this line !!!
        {
            // do some important cleanup in class Base
            std::println("d'tor Base");
        }

        // some virtual methods
        virtual void doSomething() {}
    };

    class Derived : public Base
    {
    public:
        ~Derived()
        {
            // do some important cleanup in class Derived
            std::println("d'tor Derived");
        }
    };

    static void guideline_virtual_base_class_destructor()
    {
        Base* b = new Derived();
        // use b
        delete b; // here's the problem!
    }

    // =======================================================================
    // Non-Virtual Interface (NVI) Pattern

    class LoggerInterface {
    public:
        // 1. Virtual Destructor: Required for interfaces
        virtual ~LoggerInterface() = default;

        // 2. Public API (Non-virtual): This is where the pre/post conditions reside
        void log(const std::string& message)
        {
            // Pre-Condition: Message must not be empty
            assert(!message.empty() && "Log-Message must not be empty!");

            // Call the actual logic
            do_log(message);

            // Post-Condition (Example): Increment counter or check status
            std::println("[Audit: Log entry processed]");
        }

    protected:
        // 3. Private/Protected Implementation (Pure Virtual)
        // Derived classes only override this part.
        virtual void do_log(const std::string& message) = 0;
    };

    // A Concrete Implementation
    class ConsoleLogger : public LoggerInterface {
    protected:
        void do_log(const std::string& message) override
        {
            std::println("Console: {}", message);
        }
    };

    static void guideline_non_virtual_interface_pattern()
    {
        ConsoleLogger myLogger;

        LoggerInterface* interface = &myLogger;

        // The call goes through the base class:
        // Within the base class call, the overridden methods are dispatched
        interface->log("System gestartet");
        // interface->log(""); // Would trigger the assert
    }

    // =======================================================================
    // Use exceptions

    // Bad design: returns negative number if output fails.
    // The return value can be ignored by the caller.
    // Hint: Attribute [[nodiscard]] helps, but generates only a warning
    static int someImportantMethod()
    {
        // ...
        return -1;
    }

    // Good design:
    // Use exceptions to signal a failure to perform a required task.
    // The constructor of class std::thread throws std::system_error
    // if the thread could not be started.
    class thread
    {
        template <typename TFunc, typename ... TArgs>
        explicit thread(TFunc&& func, TArgs&&... args) {};
    };

    static void guideline_use_exceptions()
    {}

    // =======================================================================
    // Never transfer ownership by a raw pointer (T*)

    class X {};

    static X* compute(int args)
    {
        X* res = new X{};
        // ...
        return res;
    }

    static void guideline_transferring_ownership()
    {
        X* result = compute(123);
    }


    // =======================================================================
    // Do not pass an array as a single pointer

    static void copy_n(const int* from, int* to, int n)
    {
        for (int i = 0; i < n; ++i) {
            to[i] = from[i];
        }
    }

    static void copy(std::span<const int> from, std::span<int> to) {

        // Safety check: Are both spans the same size?
        if (from.size() != to.size()) {
            throw std::invalid_argument("Spans must be the same size!");
        }

        // efficient data copying
        std::copy(from.begin(), from.end(), to.begin());
    }

    static void guideline_passing_arrays()
    {
        int numbers[10]{};
        int target[10]{};

        copy_n(numbers, target, 10);

        copy(std::span<int>{numbers}, std::span<int>{target});
    }
}

// ===========================================================================

void test_guidelines_interfaces()
{
    using namespace GuidelinesInterfaces;

    //guideline_precise_interface();
    //guideline_state_preconditions();
    guideline_virtual_base_class_destructor();
    //guideline_non_virtual_interface_pattern();
    //guideline_use_exceptions();
    //guideline_transferring_ownership();
    //guideline_passing_arrays();
}

// ===========================================================================
// End-of-File
// ===========================================================================
