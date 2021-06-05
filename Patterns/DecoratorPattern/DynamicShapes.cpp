#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>

namespace DynamicDecoration {

    // corresponds to 'component'
    class Shape
    {
    public:
        virtual ~Shape() {}
        virtual std::string draw() const = 0;
    };

    // corresponds to 'concrete component'
    class Circle : public Shape {
    private:
        double m_radius;

    public:
        Circle() : m_radius{ 0.0 } {}
        explicit Circle(const double radius) : m_radius{ radius } {}

        void resize(float factor) { m_radius *= factor; }

        virtual std::string draw() const override {
            std::ostringstream oss;
            oss << "A circle of radius " << std::fixed << m_radius;
            return oss.str();
        }
    };

    // corresponds to 'concrete component'
    class Square : public Shape
    {
    private:
        double m_side;

    public:
        Square() : m_side{ 0.0 } {}

        explicit Square(double side) : m_side{ side } {}

        virtual std::string draw() const override
        {
            std::ostringstream oss;
            oss << "A square with side " << m_side;
            return oss.str();
        }
    };

    // corresponds to 'base decorator class'
    class ShapeDecorator : public Shape {
    protected:
        std::shared_ptr<Shape> m_component;

    public:
        ShapeDecorator(const std::shared_ptr<Shape>& component)
            : m_component{ component } {}

        // base decorator class delegates all work to the wrapped component
        virtual std::string draw() const override {
            return m_component->draw();
        }
    };

    // corresponds to 'concrete decorator class'
    class ColoredShapeDecorator : public ShapeDecorator
    {
    private:
        std::string m_color;

    public:
        ColoredShapeDecorator(const std::shared_ptr<Shape>& shape, const std::string& color)
            : ShapeDecorator{ shape }, m_color{ color } {}

        virtual std::string draw() const override
        {
            std::ostringstream oss;
            oss << ShapeDecorator::draw() << " has color " << m_color;
            return oss.str();
        }
    };

    // corresponds to another 'concrete decorator class' 
    class TransparentShapeDecorator : public ShapeDecorator
    {
    private:
        uint8_t m_transparency;

    public:
        TransparentShapeDecorator(const std::shared_ptr<Shape>& shape, uint8_t transparency)
            : ShapeDecorator{ shape }, m_transparency{ transparency } {}

        virtual std::string draw() const override
        {
            std::ostringstream oss;
            oss << ShapeDecorator::draw() << " has "
                << m_transparency / 255.f * 100.f
                << "% transparency";
            return oss.str();
        }
    };
}

void test_dynamic_decoration_00() {
    using namespace DynamicDecoration;

    std::shared_ptr<Shape> circle{ std::make_shared<Circle>(0.5f) };
    std::cout << circle->draw() << std::endl;
    // "A circle of radius 0.5"
}

void test_dynamic_decoration_01() {
    using namespace DynamicDecoration;

    std::shared_ptr<Shape> circle{
        std::make_shared<Circle>(0.5f)
    };
    std::shared_ptr<Shape> redCircle{
        std::make_shared<ColoredShapeDecorator>(circle, "red") 
    };
    std::cout << redCircle->draw() << std::endl;
    // "A circle of radius 0.5 has color red"
}

void test_dynamic_decoration_02() {
    using namespace DynamicDecoration;

    std::shared_ptr<Shape> square{
        std::make_shared<Square>(3.0) 
    };

    std::shared_ptr<Shape> transparentSquare{
        std::make_shared<TransparentShapeDecorator>(square, static_cast<uint8_t>(85)) 
    };

    std::cout << transparentSquare->draw() << std::endl;
    // "A square with side 3 has 33.3333 % transparency"
}

void test_dynamic_decoration_03() {
    using namespace DynamicDecoration;

    std::shared_ptr<Shape> circle{
        std::make_shared<Circle>(15.0) 
    };

    std::shared_ptr<Shape> greenCircle{ 
        std::make_shared<ColoredShapeDecorator>(circle, "green")
    };

    std::shared_ptr<Shape> greenTransparentCircle{
        std::make_shared<TransparentShapeDecorator>(greenCircle, static_cast<uint8_t>(50)) 
    };
    std::cout << greenTransparentCircle->draw() << std::endl;
    // "A circle of radius 15 has color green has 19.6078% transparency"
}
