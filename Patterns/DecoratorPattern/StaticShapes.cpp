#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>

namespace StaticDecoration {

    class Shape
    {
    public:
        virtual ~Shape() {}
        virtual std::string draw() const = 0;
    };

    class Circle : public Shape
    {
    private:
        double m_radius;

    public:
        Circle() : m_radius{ 0.0 } {}

        Circle(double radius) : m_radius{ radius } {}

        void resize(double factor) { m_radius *= factor; }

        virtual std::string draw() const override {
            std::ostringstream oss;
            oss << "A circle of radius " << std::setprecision(5) << m_radius;
            return oss.str();
        }
    };

    struct Square : public Shape
    {
    private:
        double m_side;

    public:
        Square() : m_side{ 0.0 } {}

        Square(double side) : m_side{ side } {}

        void setSide(double side) { m_side = side; }

        virtual std::string draw() const override {
            std::ostringstream oss;
            oss << "A square with side " << m_side;
            return oss.str();
        }
    };

    struct Rectangle : public Shape
    {
    private:
        double m_width;
        double m_height;

    public:
        Rectangle() : m_width{ 0.0 }, m_height{ 0.0 } {}

        Rectangle(double width, double height) : m_width{ width }, m_height{ height } {}

        void setWidth(double width) { m_width = width; }
        void setHeight(double height) { m_height = height; }

        virtual std::string draw() const override {
            std::ostringstream oss;
            oss << "A Rectangle with width " << m_width << " and height " << m_height;
            return oss.str();
        }
    };

    template <typename T>
    class ColoredShape : public T
    {
        static_assert (
            std::is_base_of<Shape, T>::value,
            "Template argument must be a Shape");

    private:
        std::string m_color;

    public:
        void setColor(const std::string& color) { m_color = color; }

        template <typename ...Args>
        ColoredShape(const std::string& color, Args ...args)
            : T{ std::forward<Args>(args)... }, m_color{ color } {}

        virtual std::string draw() const override {
            std::ostringstream oss;
            std::string s{ T::draw() };
            oss << s << " has color " << m_color;
            return oss.str();
        }
    };

    template <typename T>
    struct TransparentShape : public T
    {
        static_assert (
            std::is_base_of<Shape, T>::value,
            "Template argument must be a Shape");

    private:
        uint8_t m_transparency;

    public:
        template<typename ...Args>
        TransparentShape(uint8_t transparency, Args ...args)
            : T{ std::forward<Args>(args)... }, m_transparency{ transparency } {}

        virtual std::string draw() const override {
            std::ostringstream oss;
            std::string s{ T::draw() };
            oss << s << " has "
                << (static_cast<double>(m_transparency) / 255.0) * 100.0
                << "% transparency";
            return oss.str();
        }
    };
}

void test_static_decoration_01()
{
    using namespace StaticDecoration;

    Circle circle{ 3.0 };
    std::cout << circle.draw() << std::endl;

    Square square{ 20.0 };
    std::cout << square.draw() << std::endl;

    Rectangle rectangle{ 30.0, 40.0 };
    std::cout << rectangle.draw() << std::endl;

    ColoredShape<Circle> greenCircle{ std::string{ "green" }, 5.0 };
    std::cout << greenCircle.draw() << std::endl;

    TransparentShape<Square> transparentSquare(static_cast<uint8_t>(0), 0.0);
    std::cout << transparentSquare.draw() << std::endl;

    ColoredShape<Rectangle> yellowRectangle{ std::string{ " yellow" }, 50.0, 60.0 };
    std::cout << yellowRectangle.draw() << std::endl;

    TransparentShape<ColoredShape<Square>> blueTransparentSquare{ 0, "blue", 0.0 };
    blueTransparentSquare.setColor("yellow");
    blueTransparentSquare.setSide(100);
    std::cout << blueTransparentSquare.draw() << std::endl;

    ColoredShape<TransparentShape<Square>> redOpaqueSquare{"red",  0, 255.0 };
    redOpaqueSquare.setColor("red");
    redOpaqueSquare.setSide(300);
    std::cout << redOpaqueSquare.draw() << std::endl;

    TransparentShape<ColoredShape<Rectangle>> whiteNonTransparentRectangle{ 127, "white", 70.0, 80.0, };
    std::cout << whiteNonTransparentRectangle.draw() << std::endl;
}
