// ===========================================================================
// StaticShapes.cpp // Decorator Pattern
// ===========================================================================

#include <concepts>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace StaticDecoration {

    class IShape
    {
    public:
        virtual ~IShape() {}

        virtual std::string draw() const = 0;
    };

    class Circle : public IShape
    {
    private:
        double m_radius;

    public:
        Circle() : m_radius{ 0.0 } {}

        Circle(double radius) : m_radius{ radius } {}

        void resize(double factor) { m_radius *= factor; }

        std::string draw() const override {
            std::ostringstream oss;
            oss << "A circle of radius " << std::setprecision(5) << m_radius;
            return oss.str();
        }
    };

    struct Square : public IShape
    {
    private:
        double m_side;

    public:
        Square() : m_side{ 0.0 } {}

        Square(double side) : m_side{ side } {}

        void setSide(double side) { m_side = side; }

        std::string draw() const override {
            std::ostringstream oss;
            oss << "A square with side " << m_side;
            return oss.str();
        }
    };

    struct Rectangle : public IShape
    {
    private:
        double m_width;
        double m_height;

    public:
        Rectangle() : m_width{ 0.0 }, m_height{ 0.0 } {}

        Rectangle(double width, double height) 
            : m_width{ width }, m_height{ height } {}

        void setWidth(double width) { m_width = width; }
        void setHeight(double height) { m_height = height; }

        std::string draw() const override {
            std::ostringstream oss;
            oss << "A Rectangle with width " << m_width << " and height " << m_height;
            return oss.str();
        }
    };

    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------

    // template argument must be derived from IShape
    template <typename T>
    concept ConceptIShapeObject = std::derived_from<T, IShape>;

    // ---------------------------------------------------------------------------

    template <typename T>
        requires ConceptIShapeObject<T>
    class ColoredShape : public T
    {
    private:
        std::string m_color;

    public:
        // c'tor
        template <typename ... TARGS>
        ColoredShape(const std::string& color, TARGS&& ...args) :
            T{ std::forward<TARGS>(args) ... }, m_color{ color } 
        {}

        void setColor(const std::string& color) { m_color = color; }

        std::string draw() const override {
            std::ostringstream oss;
            std::string s{ T::draw() };
            oss << s << " has color " << m_color;
            return oss.str();
        }
    };

    // ---------------------------------------------------------------------------

    template <typename T>
        requires ConceptIShapeObject<T>
    struct TransparentShape : public T
    {
    private:
        uint8_t m_transparency;

    public:
        // c'tor
        template<typename ... TARGS>
        TransparentShape(uint8_t transparency, TARGS&& ...args)
            : T{ std::forward<TARGS>(args)... }, m_transparency{ transparency } {}

        std::string draw() const override {
            std::ostringstream oss;
            std::string s{ T::draw() };
            oss << s << " has "
                << (static_cast<double>(m_transparency) / 255.0) * 100.0
                << "% transparency";
            return oss.str();
        }
    };
}

class NonConformantCircle {};

void test_static_decoration_01()
{
    using namespace StaticDecoration;

    Circle circle{ 3.0 };
    std::cout << circle.draw() << std::endl;

    Square square{ 20.0 };
    std::cout << square.draw() << std::endl;

    Rectangle rectangle{ 30.0, 40.0 };
    std::cout << rectangle.draw() << std::endl;

    // just testing 'concepts' constraints
    // ColoredShape<NonConformantCircle> whatCircle{};

    ColoredShape<Circle> greenCircle{ 
        std::string{ "green" }, 5.0 
    };
    std::cout << greenCircle.draw() << std::endl;

    TransparentShape<Square> transparentSquare{ 
        static_cast<uint8_t>(0), 0.0 
    };
    std::cout << transparentSquare.draw() << std::endl;

    ColoredShape<Rectangle> yellowRectangle{ 
        std::string{ "yellow" }, 50.0, 60.0
    };
    std::cout << yellowRectangle.draw() << std::endl;

    TransparentShape<ColoredShape<Square>> blueTransparentSquare{
        0, std::string{ "blue" }, 0.0
    };
    blueTransparentSquare.setColor("yellow");
    blueTransparentSquare.setSide(100);
    std::cout << blueTransparentSquare.draw() << std::endl;

    ColoredShape<TransparentShape<Square>> redOpaqueSquare{
        std::string{ "red" }, static_cast<uint8_t>(0), 255.0
    };
    redOpaqueSquare.setColor("red");
    redOpaqueSquare.setSide(300);
    std::cout << redOpaqueSquare.draw() << std::endl;

    TransparentShape<ColoredShape<Rectangle>> whiteNonTransparentRectangle{
        127, std::string{ "white" }, 70.0, 80.0,
    };
    std::cout << whiteNonTransparentRectangle.draw() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
