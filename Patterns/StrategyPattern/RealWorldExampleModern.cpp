// ===========================================================================
// RealWorldExampleModern.cpp // Strategy Pattern
// ===========================================================================

#include <functional>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace StrategyRealWorldExampleModern {

    // =======================================================================

    /**
     * Common Base Interface for all visual widgets.
     * This interface is not related directly to the Strategy Design Pattern.
     */

    class Shape
    {
    public:
        virtual ~Shape() = default;

        virtual void draw() const = 0;
    };

    // ===========================================================================

    /**
     * The Circle uses the DrawCircleStrategy interface to call the algorithm
     * defined by some DrawCircleStrategy support.
     */

    class Circle : public Shape
    {
    private:
        using DrawStrategy = std::function<void(const Circle&)>;

    public:
        explicit Circle(double radius, DrawStrategy drawer)
            : m_radius{ radius }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawCircleStrategy(DrawStrategy drawer)
        {
            m_drawer = std::move(drawer);
        }

        void draw() const override
        {
            m_drawer(*this);
        }

        double radius() const { return m_radius; }

    private:
        DrawStrategy m_drawer;
        double       m_radius;
    };

    class Rectangle : public Shape
    {
    private:
        using DrawStrategy = std::function<void(const Rectangle&)>;

    public:
        explicit Rectangle(double width, double height, DrawStrategy drawer)
            : m_width{ width }, m_height{ height }, m_drawer{ std::move(drawer) }
        {
        }

        void setDrawRectangleStrategy(DrawStrategy strategy)
        {
            m_drawer = std::move(strategy);
        }

        void draw() const override
        {
            m_drawer(*this);
        }

        double width() const { return m_width; }
        double height() const { return m_height; }

    private:
        DrawStrategy m_drawer;
        double       m_width;
        double       m_height;
    };

    // ===========================================================================

    /**
     * Concrete strategies implement the algorithm
     * while following the Base Strategy interface.
     * The interface makes them interchangeable in the clients (Visual Widgets).
     */

    class Win32CircleStrategy
    {
    public:
        explicit Win32CircleStrategy() {};

        void operator() (const Circle& circle) const {
            std::println("Drawing a Circle using the Win32 Framework");
        }

    private:
        /* Drawing related data members, e.g. colors, textures, ... */
    };

    class Win32RectangleStrategy
    {
    public:
        explicit Win32RectangleStrategy() {};

        void operator() (Rectangle const& rectangle) const {
            std::println("Drawing a Rectangle using the Rectangle Framework");
        }

    private:
        /* Drawing related data members, e.g. colors, textures, ... */
    };

    // ===========================================================================

    /**
     * The client code picks a concrete strategy and passes it to the context.
     * The client should be aware of the differences between strategies
     * in order to make the right choice.
     */

    static void clientCode(const std::vector<std::unique_ptr<Shape>>& shapes)
    {
        for (auto const& shape : shapes)
        {
            shape->draw();
        }
    }
}

void test_realworld_example_modern()
{
    using namespace StrategyRealWorldExampleModern;

    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes{};

    // creating strategy objects based upon the according Win32 drawing strategy
    Win32CircleStrategy strategy1;
    Win32RectangleStrategy strategy2;
    Win32CircleStrategy strategy3;

    // creating visual widgets using strategy objects
    std::unique_ptr<Circle> upc{ std::make_unique<Circle>(
        3.0, std::move(strategy1))
    };

    std::unique_ptr<Rectangle> upr{ std::make_unique<Rectangle>(
        4.0, 5.0, std::move(strategy2))
    };

    std::unique_ptr<Circle> upc2{ std::make_unique<Circle>(
        6.0, std::move(strategy3))
    };

    // filling container with visual widgets
    shapes.push_back(std::move(upc));
    shapes.push_back(std::move(upr));
    shapes.push_back(std::move(upc2));

    clientCode(shapes);
}

// ===========================================================================
// End-of-File
// ===========================================================================
