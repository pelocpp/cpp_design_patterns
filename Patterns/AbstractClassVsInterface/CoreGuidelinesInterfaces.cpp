// ===========================================================================
// CoreGuidelinesInterfaces.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

//#include <iostream>
//#include <string>

#include <cstddef>
#include <iterator>
#include <span>



//https://www.heise.de/blog/C-Core-Guidelines-Interfaces-I-3767608.html
//
//https://www.modernescpp.com/index.php/c-core-guidelines-interfaces/
//
//https://www.modernescpp.com/index.php/c-core-guidelines-interfaces-ii

#include <cmath>

namespace CoreGuidelinesInterfaces {

    // =======================================================================

    // Make interfaces precise
    static void core_guideline_precise_interface()
    {
        class IMath
        {
        public:
            virtual ~IMath() = default;

            virtual double round(double d) = 0;
        };

        class IMathImpl : public IMath
        {
        public:
            double round(double d) override
            {
                return (m_roundUp) ? std::ceil(d) : d;    // don't: "invisible" dependency
            }

        private:
            bool m_roundUp;
        };
    }

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

    // =======================================================================

    // Make interfaces precise
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

    // Make interfaces precise
    static void core_guideline_State_preconditions()
    {

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

    //template<typename TIter, typename TValue>
    //    requires std::input_iterator<TIter> && std::equality_comparable<TIter, TValue >>
    //    std::input_iterator<TIter> find(std::input_iterator<TIter> first, std::input_iterator<TIter> last, TValue v)
    //    {
    //        // ...
    //    }

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


    void copy_n(const int* source, int* dest, int count);     // copy from [p:p+n) to [q:q+n)

    void copy(std::span<const int> r, std::span<int> r2); // copy r to r2

    static void core_guideline_passing_arrays()
    {
        int numbers[10]{};
        int target[10]{};

        copy_n(numbers, target, 10);

        copy(std::span<int>{numbers}, std::span<int>{target});
    }

WEITER: Safe Implementierung mit copy  // Chat GPT ....

WEITER: Unsafe selbst programmieren ....
    
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
