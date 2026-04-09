// ===========================================================================
// CoreGuidelinesInterfaces.cpp // Abstract Classes vs Interfaces in C++
// ===========================================================================

//#include <iostream>
//#include <string>


https://www.heise.de/blog/C-Core-Guidelines-Interfaces-I-3767608.html

https://www.modernescpp.com/index.php/c-core-guidelines-interfaces/

https://www.modernescpp.com/index.php/c-core-guidelines-interfaces-ii

#include <cmath>

namespace CoreGuidelinesInterfaces {

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

    // Make interfaces precise
    static void core_guideline_State preconditions()
    {

    }

}

// ===========================================================================

void test_core_guidelines_interfaces()
{

}

// ===========================================================================
// End-of-File
// ===========================================================================
