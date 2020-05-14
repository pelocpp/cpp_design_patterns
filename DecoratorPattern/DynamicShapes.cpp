#include <iostream>
#include <string>
#include <sstream>
#include <memory>

// component
class Shape
{
public:
    virtual ~Shape() {}
    virtual std::string draw() const = 0;
};

// concrete ccomponent
class Circle : public Shape {
private:
    float m_radius; 

public:
    Circle() : m_radius{ 0.0 } {}
    explicit Circle(const float radius) : m_radius{ radius } {}

    void resize(float factor) { m_radius *= factor; }

    std::string draw() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << m_radius;
        return oss.str();
    }
};

// concrete component
class Square : public Shape
{
private:
    double m_side;

public:
    Square() : m_side{ 0.0 } {}

    explicit Square(double side) : m_side{ side } {}

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << m_side;
        return oss.str();
    }
};

// base decorator class
class Decorator : public Shape {
protected:
    std::shared_ptr<Shape> m_component;

public:
    Decorator(const std::shared_ptr<Shape>& component) 
      : m_component(component) {}

    // decorator delegates all work to the wrapped componen
    std::string draw() const override {
        return m_component->draw();
    }
};

// concrete decorator class 
class ColoredShape : public Decorator
{
private:
    std::string m_color;

public:
  // ColoredShape() {}

    ColoredShape(const std::shared_ptr<Shape>& shape, const std::string& color) 
        : Decorator(shape), m_color{ color } {}

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << Decorator::draw() << " has the color " << m_color;
        return oss.str();
    }
};

// another concrete decorator class 
class TransparentShape : public Decorator
{
private:
    uint8_t m_transparency;

public:
    TransparentShape(const std::shared_ptr<Shape>& shape, uint8_t transparency)
        : Decorator(shape), m_transparency{ transparency } {}

    std::string draw() const override
    {
        std::ostringstream oss;
        oss << Decorator::draw() << " has "
            << static_cast<uint8_t>(m_transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

void test_dynamic_decoration_01() {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(0.5f);
    std::shared_ptr<Shape> redCircle 
        = std::make_shared<ColoredShape>(circle, "red");
    std::cout << redCircle->draw() << std::endl;
    // "A circle of radius 0.5 has the color red"
}

void test_dynamic_decoration_02() {
    std::shared_ptr<Shape> square = std::make_shared<Square>(3.0);
    std::shared_ptr<Shape> transparentSquare
        = std::make_shared<TransparentShape>(square, static_cast<uint8_t>(85));
    std::cout << transparentSquare->draw() << std::endl;
    // "A square with side 3 has 33.3333 % transparency"
}

void test_dynamic_decoration_03() {
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(static_cast<float>(23));
    std::shared_ptr<Shape> greenCircle = std::make_shared<ColoredShape>(circle, "green");
    std::shared_ptr<Shape> greenTransparentCircle 
        = std::make_shared<TransparentShape>(greenCircle, static_cast<uint8_t>(64));
    std::cout << greenTransparentCircle->draw() << std::endl;
    // "A circle of radius 23 has the color has 25.098% transparency"
}