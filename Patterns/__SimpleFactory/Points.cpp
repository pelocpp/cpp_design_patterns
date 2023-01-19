// ===========================================================================
// Points.cpp
// ===========================================================================

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>

namespace Factory01 {

    // 1.) bad or impossible usage

    struct Point {
        Point(double x, double y) { /*...*/ }        // Cartesian coordinates
        // ... Implementation

        // Not OK: Cannot overload with same type of arguments
        // 
        // Point(double a, double b){ /*...*/ }      // Polar coordinates
        // ... Implementation
    };
}

enum class PointType { cartesian, polar };

namespace Factory02 {

    // 2.) solution of 1.), but not recommendable

    class Point
    {
    public:
        Point(double a, double b, PointType type = PointType::cartesian)
        {
            if (type == PointType::cartesian) {
                m_x = a;
                m_y = b;
            }
            else {
                m_x = a * cos(b);
                m_y = a * sin(b);
            }
        }

    private:
        double m_x;
        double m_y;
    };
}

namespace Factory03 {

    // 3.) factory approach (within a single class)

    class Point
    {
    private:
        double    m_x;
        double    m_y;
        PointType m_type;

        // private constructor, so that object can't be created directly
        Point(const double x, const double y, PointType t) 
            : m_x{ x }, m_y{ y }, m_type{ t } {}

    public:
        static Point NewCartesian(double x, double y) {
            return { x, y, PointType::cartesian };
        }

        static Point NewPolar(double a, double b) {
            return { a * cos(b), a * sin(b), PointType::polar };
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            return os << "x: " << obj.m_x << " y: " << obj.m_y;
        }
    };

    void test()
    {
        // Point p{ 1, 2 };  // doesn't compile

        auto p = Point::NewPolar(5.0, M_PI / 4);
        std::cout << p << std::endl;  // x: 3.53553 y: 3.53553
    }
}

namespace Factory04 {

    // 4.) factory approach with distinct classes (using undesired friendships)

    class Point
    {
        friend class PointFactory;

    private:
        double    m_x;
        double    m_y;
        PointType m_type;

        // private constructor, so that object can't be created directly
        Point(const double x, const double y, PointType t)
            : m_x{ x }, m_y{ y }, m_type{ t } {}

    public:
        friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
            return os << "x: " << obj.m_x << " y: " << obj.m_y;
        }
    };

    class PointFactory
    {
    public:
        static Point NewCartesian(double x, double y) {
            return { x, y, PointType::cartesian };
        }

        static Point NewPolar(double a, double b) {
            return { a * cos(b), a * sin(b), PointType::polar };
        }
    };

    void test()
    {
        // Point p{ 1, 2 };  // doesn't compile

        auto p = PointFactory::NewPolar(5.0, M_PI / 4);
        std::cout << p << std::endl;  // x: 3.53553 y: 3.53553
    }
}

namespace Factory05 {

    // 5.) factory approach, so called 'inner factory'

    class Point
    {
    private:
        double m_x;
        double m_y;

        Point(double x, double y) : m_x(x), m_y(y) {}

    public:
        struct Factory
        {
            static Point NewCartesian(double x, double y) { 
                return { x,y };
            }

            static Point NewPolar(double r, double theta) { 
                return{ r * cos(theta), r * sin(theta) };
            }
        };
    };

    void test() {
        auto p = Point::Factory::NewCartesian(2, 3);
    }
}

void test_real_world_example_points()
{
    Factory03::test();
    Factory04::test();
    Factory05::test();
}

// ===========================================================================
// End-of-File
// ===========================================================================
