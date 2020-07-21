#include <iostream>
#include <string>
#include <sstream>
#include <memory>

class Shape
{
public:
    virtual ~Shape() {}
    virtual std::string draw() const = 0;
};

class Circle : Shape
{
private:
    float m_radius;

public:
    explicit Circle() : m_radius{ 0.0 } {}
    explicit Circle(const float radius) : m_radius{ radius } {}

    void resize(float factor) { m_radius *= factor; }

    std::string draw() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << m_radius;
        return oss.str();
    }
};

struct Square : Shape
{
private:
    float m_side;

public:
    explicit Square() : m_side{ 0.0 } {}
    explicit Square(const float side) : m_side{ side } {}

    void setSide(float side) { m_side = side; }

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << m_side;
        return oss.str();
    }
};

// note: class, not typename
template <typename T> 
class ColoredShape2 : public T
{
    static_assert (
        std::is_base_of<Shape, T>::value,
        "Template argument must be a Shape");

private:
    std::string m_color;

public:
    void setColor(const std::string& color) { m_color = color; }

    template <typename...Args>
    ColoredShape2(const std::string& color, Args ...args)
        : T(std::forward<Args>(args)...), m_color{ color }
    {
    }

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << T::draw() << " has the color " << m_color;
        return oss.str();
    }
};

template <typename T> 
struct TransparentShape2 : public T
{
private:
    uint8_t transparency;

public:
    template<typename...Args>
    TransparentShape2(const uint8_t transparency, Args ...args)
        : T(std::forward<Args>(args)...), transparency{ transparency }
    {
    }

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << T::draw() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

void test_static_decoration_01()
{
    // won't work without a default constructor
    ColoredShape2<Circle> green_circle{ "green", static_cast<float>(5) };
    std::cout << green_circle.draw() << std::endl;

    TransparentShape2<ColoredShape2<Square>> blue_invisible_square{ 0, "blue", static_cast<float>(10) };
    blue_invisible_square.setColor("blue");
    blue_invisible_square.setSide(321);
    std::cout << blue_invisible_square.draw() << std::endl;
}
