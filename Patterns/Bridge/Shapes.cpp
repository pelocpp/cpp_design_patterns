// ===========================================================================
// Shapes.cpp // Bridge Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ShapesExample {

    /**
     *  Bridge implementor interface.
     */
    class IDrawAPI {
    public:
        virtual void drawCircle(int radius, int x, int y) = 0;
    };

    /**
     *  Create concrete bridge implementor classes implementing the IDrawAPI interface.
     */
    class RedCircleDrawer : public IDrawAPI {
    public:
        virtual void drawCircle(int radius, int x, int y) override
        {
            std::cout
                << "Drawing Circle[ color: red, radius: "
                << radius << ", x: " << x << ", " << y << "]" << std::endl;
        }
    };
    
    class GreenCircleDrawer : public IDrawAPI {
    public:
        virtual void drawCircle(int radius, int x, int y) override
        {
            std::cout 
                << "Drawing Circle[ color: green, radius: " 
                << radius << ", x: " << x << ", " << y << "]" << std::endl;
        }
    };

    /**
     *  Create an abstract class Shape using the IDrawAPI interface.
     */
    class Shape
    {
    protected:
        std::shared_ptr<IDrawAPI> m_drawAPI;

        Shape(std::shared_ptr<IDrawAPI> drawAPI)
        {
            m_drawAPI = drawAPI;
        }

    public:
        void setImplementor(std::shared_ptr<IDrawAPI> drawAPI)
        {
            m_drawAPI = drawAPI;
        }

        virtual void draw() = 0;
    };

    /**
     *  Create concrete class implementing the Shape interface.
     */
    class Circle : public Shape {
    private:
        int m_x;
        int m_y;
        int m_radius;

    public:
        Circle(int x, int y, int radius, std::shared_ptr<IDrawAPI> drawAPI)
            : m_x{ x }, m_y{ y }, m_radius{ radius }, Shape{ drawAPI } { }

        void draw()
        {
            m_drawAPI->drawCircle(m_radius, m_x, m_y);
        }
    };

    /**
     *  Use the Shape and IDrawAPI classes to draw different colored circles.
     */
    void clientCode01()
    {
        // two different bridge implementor classes
        std::shared_ptr<RedCircleDrawer> redCircleDrawer = 
            std::make_shared<RedCircleDrawer>();

        std::shared_ptr<GreenCircleDrawer> greenCircleDrawer = 
            std::make_shared<GreenCircleDrawer>();

        // single Circle object
        std::shared_ptr<Shape> circle = 
            std::make_shared<Circle>(100, 10, 20, redCircleDrawer);

        circle->draw();
        circle->setImplementor(greenCircleDrawer);
        circle->draw();
    }

    void clientCode02()
    {
        // two different bridge implementor classes
        std::shared_ptr<IDrawAPI> redCircleDrawer = 
            std::make_shared<RedCircleDrawer>();

        std::shared_ptr<IDrawAPI> greenCircleDrawer =
            std::make_shared<GreenCircleDrawer>();

        std::shared_ptr<Shape> redCircle = 
            std::make_shared<Circle>(100, 10, 20, redCircleDrawer);

        std::shared_ptr<Shape> greenCircle = 
            std::make_shared<Circle>(200, 30, 40, greenCircleDrawer);

        redCircle->draw();
        greenCircle->draw();
    }
}

void test_shapes_example() 
{
    using namespace ShapesExample;
    clientCode01();
    clientCode02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
