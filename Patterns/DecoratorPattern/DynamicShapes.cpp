// ===========================================================================
// DynamicShapes.cpp // Decorator Pattern
// ===========================================================================

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace DynamicDecoration {

    // corresponds to 'component'
    class IShape
    {
    public:
        virtual ~IShape() = default;

        virtual std::string draw() const = 0;
    };

    // corresponds to 'concrete component'
    class Circle : public IShape {
    private:
        double m_radius;

    public:
        Circle() : m_radius{ 0.0 } {}

        explicit Circle(double radius) : m_radius{ radius } {}

        void resize(double factor) { m_radius *= factor; }

        std::string draw() const override {
            std::ostringstream oss;
            oss << "A circle of radius " << std::fixed << m_radius;
            return oss.str();
        }
    };

    // corresponds to 'concrete component'
    class Square : public IShape
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

    // ---------------------------------------------------------------------------

    // corresponds to 'base decorator class'
    class ShapeDecorator : public IShape {
    protected:
        std::shared_ptr<IShape> m_component;

    public:
        ShapeDecorator(const std::shared_ptr<IShape>& component)
            : m_component{ component }
        {}

        // base decorator class delegates all work to the wrapped component
        std::string draw() const override {

            return m_component->draw();
        }
    };

    // corresponds to 'concrete decorator class'
    class ColoredShapeDecorator : public ShapeDecorator
    {
    private:
        std::string m_color;

    public:
        ColoredShapeDecorator(const std::shared_ptr<IShape>& shape, const std::string& color)
            : ShapeDecorator{ shape }, m_color{ color }
        {}

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
        TransparentShapeDecorator(const std::shared_ptr<IShape>& shape, uint8_t transparency)
            : ShapeDecorator{ shape }, m_transparency{ transparency }
        {}

        virtual std::string draw() const override
        {
            std::ostringstream oss;
            oss << ShapeDecorator::draw() << " has "
                << (static_cast<double>(m_transparency) / 255.0) * 100.0
                << "% transparency";
            return oss.str();
        }
    };
}

static void test_real_world_example_01() {

    using namespace DynamicDecoration;

    std::shared_ptr<IShape> circle{
        std::make_shared<Circle>(0.5) 
    };

    std::cout << circle->draw() << std::endl;
    // "A circle of radius 0.5"
}

static void test_real_world_example_02() {

    using namespace DynamicDecoration;

    std::shared_ptr<IShape> circle{
        std::make_shared<Circle>(0.5)
    };

    std::shared_ptr<IShape> redCircle{
        std::make_shared<ColoredShapeDecorator>(circle, "red") 
    };

    std::cout << redCircle->draw() << std::endl;
    // "A circle of radius 0.500000 has color red"
}

static void test_real_world_example_03() {

    using namespace DynamicDecoration;

    std::shared_ptr<IShape> square{
        std::make_shared<Square>(3.0) 
    };

    std::shared_ptr<IShape> transparentSquare{
        std::make_shared<TransparentShapeDecorator>(square, static_cast<uint8_t>(85)) 
    };

    std::cout << transparentSquare->draw() << std::endl;
    // "A square with side 3 has 33.3333% transparency"
}

static void test_real_world_example_04() {

    using namespace DynamicDecoration;

    std::shared_ptr<IShape> circle{
        std::make_shared<Circle>(15.0) 
    };

    std::shared_ptr<IShape> greenCircle{
        std::make_shared<ColoredShapeDecorator>(circle, "green")
    };

    std::shared_ptr<IShape> greenTransparentCircle{
        std::make_shared<TransparentShapeDecorator>(greenCircle, static_cast<uint8_t>(50)) 
    };

    std::cout << greenTransparentCircle->draw() << std::endl;
    // "A circle of radius 15.000000 has color green has 19.6078% transparency"
}

void test_real_world_example()
{
    test_real_world_example_01();
    test_real_world_example_02();
    test_real_world_example_03();
    test_real_world_example_04();
}

// ===========================================================================
// End-of-File
// ===========================================================================
