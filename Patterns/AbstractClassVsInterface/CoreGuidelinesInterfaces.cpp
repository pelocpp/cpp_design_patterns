// ===========================================================================
// CoreGuidelinesInterfaces.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <span>
#include <stdexcept>


//https://www.heise.de/blog/C-Core-Guidelines-Interfaces-I-3767608.html
//
//https://www.modernescpp.com/index.php/c-core-guidelines-interfaces/
//
//https://www.modernescpp.com/index.php/c-core-guidelines-interfaces-ii

#include <cmath>
#include <cassert>

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

    static void core_guideline_precise_interface_02()
    {
        // Bad design: what do these four parameters mean? Great opportunities for making mistakes
        // What do 10, 20 mean?
        Point p{};
        void draw_rect(int, int, int, int);
        draw_rect(p.m_x, p.m_y, 10, 20);

        // --------------------------------------------------

        // Better design:
        void draw_rectangle(Point top_left, Point bottom_right);
        void draw_rectangle(Point top_left, Size height_width);

        draw_rectangle(p, Point{ 10, 20 });  // Two corners
        draw_rectangle(p, Size{ 10, 20 });   // One corner and one size specification
    }

    // =======================================================================

    // State preconditions (if any)
    static double sqrt(double x) {
        //Expects(x >= 0); /* ... */
        assert(x >= 0);  //  "x may not be negative"
        return 0.0;
    };

    static void core_guideline_state_preconditions()
    {
        sqrt(-1.0);
    }

    // =======================================================================

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

    static void core_guideline_use_exceptions()
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

    static void core_guideline_transferring_ownership()
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

    static void core_guideline_passing_arrays()
    {
        int numbers[10]{};
        int target[10]{};

        copy_n(numbers, target, 10);

        copy(std::span<int>{numbers}, std::span<int>{target});
    }
 
    // =======================================================================




    // =======================================================================

}

// ===========================================================================

void test_core_guidelines_interfaces()
{

}

// ===========================================================================
// End-of-File
// ===========================================================================
