// ===========================================================================
// DynamicShapes.cpp // Decorator Pattern
// ===========================================================================

#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <string>

namespace DynamicDecoration {

    // =======================================================================

    // corresponds to 'component'
    class IShape
    {
    public:
        virtual ~IShape() = default;

        [[nodiscard]]
        virtual std::string draw() const = 0;
    };

    // corresponds to 'concrete component'
    class Circle final : public IShape {
    private:
        double m_radius = 0.0;   // Default-Member-Initializer

    public:
        Circle() = default;

        explicit Circle(double radius) : m_radius{ radius } {}

        void resize(double factor) { m_radius *= factor; }

        [[nodiscard]]
        std::string draw() const override {
            return std::format("A circle of radius {:.2f}", m_radius);
        }
    };

    // corresponds to 'concrete component'
    class Square final : public IShape
    {
    private:
        double m_side = 0.0;   // Default-Member-Initializer;

    public:
        Square() = default;

        explicit Square(double side) : m_side{ side } {}

        [[nodiscard]]
        std::string draw() const override
        {
            return std::format("A square with side {:.2f}", m_side);
        }
    };

    // =======================================================================

    // corresponds to 'base decorator class'
    class ShapeDecorator : public IShape {
    private:
        std::unique_ptr<IShape> m_component;

    public:
        explicit ShapeDecorator(std::unique_ptr<IShape> component)
            : m_component{ std::move(component) }
        {}

        // base decorator class delegates all work to the wrapped component
        [[nodiscard]]
        std::string draw() const override {

            return m_component->draw();
        }
    };

    // corresponds to 'concrete decorator class'
    class ColoredShapeDecorator final : public ShapeDecorator
    {
    private:
        std::string m_color;

    public:
        ColoredShapeDecorator(std::unique_ptr<IShape> shape, std::string color)
            : ShapeDecorator{ std::move(shape) }, m_color{ std::move(color) }
        {}

        [[nodiscard]]
        std::string draw() const override
        {
            return std::format("{} has color {}", ShapeDecorator::draw(), m_color);
        }
    };

    // corresponds to another 'concrete decorator class' 
    class TransparentShapeDecorator final : public ShapeDecorator
    {
    private:
        std::uint8_t m_transparency;

    public:
        TransparentShapeDecorator(std::unique_ptr<IShape> shape, std::uint8_t transparency)
            : ShapeDecorator{ std::move(shape) }, m_transparency{ transparency }
        {}

        [[nodiscard]]
        std::string draw() const override
        {
            return std::format("{} has {:.2f}% transparency", 
                ShapeDecorator::draw(),
                (static_cast<double>(m_transparency) / 255.0) * 100.0);
        }
    };
}

// =======================================================================

namespace {

    void test_real_world_example_01() {

        using namespace DynamicDecoration;

        std::unique_ptr<IShape> circle{
            std::make_unique<Circle>(0.5)
        };

        std::println("{}", circle->draw());
        // "A circle of radius 0.50"
    }

    void test_real_world_example_02() {

        using namespace DynamicDecoration;

        std::unique_ptr<IShape> circle{
            std::make_unique<Circle>(0.5)
        };

        std::unique_ptr<IShape> redCircle{
            std::make_unique<ColoredShapeDecorator>(std::move(circle), "red")
        };

        std::println("{}", redCircle->draw());
        // "A circle of radius 0.50 has color red"
    }

    void test_real_world_example_03() {

        using namespace DynamicDecoration;

        std::unique_ptr<IShape> square{
            std::make_unique<Square>(3.0)
        };

        std::unique_ptr<IShape> transparentSquare{
            std::make_unique<TransparentShapeDecorator>(std::move(square), static_cast<std::uint8_t>(85))
        };

        std::println("{}", transparentSquare->draw());
        // "A square with side 3.00 has 33.33% transparency"
    }

    void test_real_world_example_04() {

        using namespace DynamicDecoration;

        std::unique_ptr<IShape> circle{
            std::make_unique<Circle>(15.0)
        };

        std::unique_ptr<IShape> greenCircle{
            std::make_unique<ColoredShapeDecorator>(std::move(circle), "green")
        };

        std::unique_ptr<IShape> greenTransparentCircle{
            std::make_unique<TransparentShapeDecorator>(std::move(greenCircle), static_cast<std::uint8_t>(50))
        };

        std::println("{}", greenTransparentCircle->draw());
        // "A circle of radius 15.00 has color green has 19.61% transparency"
    }
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
