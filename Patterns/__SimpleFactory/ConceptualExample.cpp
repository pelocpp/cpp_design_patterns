// ===========================================================================
// ConceptualExample.cpp // Factory a.k.a. Simple Factory
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ConceptualExample {

    class IShape
    {
    public:
        virtual ~IShape() {};
        virtual void draw() = 0;
    };

    class Rectangle : public IShape {
    public:
        Rectangle() = default;
        void draw() override
        {
            std::cout << "> Rectangle::draw()" << std::endl;
        }
    };

    class Square : public IShape {
    public:
        Square() = default;
        void draw() override
        {
            std::cout << "> Square::draw()" << std::endl;
        }
    };

    class Circle : public IShape {
    public:
        Circle() = default;
        void draw() override
        {
            std::cout << "> Circle ::draw()" << std::endl;
        }
    };

    class ShapeFactory
    {
        enum class StringCode {
            Rectangle,
            Square,
            Circle,
            None
        };

    public:
        std::shared_ptr<IShape> getShape(std::string shapeType)
        {
            enum class StringCode shape = stringToEnum(shapeType);

            switch (shape)
            {
            case StringCode::Rectangle:
                return std::make_shared<ConceptualExample::Rectangle>();
            case StringCode::Square:
                return std::make_shared<ConceptualExample::Square>();
            case StringCode::Circle:
                return std::make_shared<ConceptualExample::Circle>();
            case StringCode::None:
                return std::shared_ptr<IShape>();
            default:
                std::string msg = "Invalid type: " + shapeType;
                throw std::runtime_error{ msg };
            }
        }

    private:
        StringCode stringToEnum(const std::string& s) {
            if (s == "Rectangle") {
                return StringCode::Rectangle;
            }
            else if (s == "Square") {
                return StringCode::Square;
            }
            else if (s == "Circle") {
                return StringCode::Circle;
            }
            else {
                return StringCode::None;
            }
        }
    };

    void test_without_factory()
    {
        // using classes explicitely
        Rectangle* rect = new Rectangle{};
        rect->draw();
        Circle* circle = new Circle{};
        circle->draw();
        Square* square = new Square{};
        square->draw();
    }

    void test_with_factory()
    {
        // using classes indirectly with factory
        // (knowledge about explicit classes not necessary)
        ShapeFactory shapeFactory;

        std::shared_ptr<IShape> shape{};
        shape = shapeFactory.getShape("Circle");
        shape->draw();
        shape = shapeFactory.getShape("Rectangle");
        shape->draw();
        shape = shapeFactory.getShape("Square");
        shape->draw();
    }
}

void test_conceptual_example ()
{
    using namespace ConceptualExample;
    test_without_factory();
    test_with_factory();
}

// ===========================================================================
// End-of-File
// ===========================================================================
