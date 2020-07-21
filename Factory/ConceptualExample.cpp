// ===========================================================================
// ConceptualExample.cpp // Factory a.k.a. Simple Factory
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

 //https://dzone.com/articles/factory-method-vs-simple-factory-1

 //https://medium.com/bitmountn/factory-vs-factory-method-vs-abstract-factory-c3adaeb5ac9a

namespace ConceptualExample {

    class Shape
    {
    public:
        virtual void draw() = 0;
    };

    class Rectangle : public Shape {
    public:
        void draw() override
        {
            std::cout << "> Rectangle::draw()" << std::endl;
        }
    };

    class Square : public Shape {
    public:
        void draw() override
        {
            std::cout << "> Square::draw()" << std::endl;
        }
    };

    class Circle : public Shape {
    public:
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
        std::shared_ptr<Shape> getShape(std::string shapeType)
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
                return std::shared_ptr<Shape>();
            default:
                std::string msg = "Invalid type: " + shapeType;
                throw std::runtime_error(msg);
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
}

void test_conceptual_example () {
    using namespace ConceptualExample;

    ShapeFactory shapeFactory;

    // get an object of type Circle and call its draw method
    std::shared_ptr<Shape> shape1 = shapeFactory.getShape("Circle");
    shape1->draw();

    // get an object of type Rectangle and call its draw method
    std::shared_ptr<Shape> shape2 = shapeFactory.getShape("Rectangle");
    shape2->draw();

    // get an object of type Square and call its draw method
    std::shared_ptr<Shape> shape3 = shapeFactory.getShape("Square");
    shape3->draw();
}

// ===========================================================================
// End-of-File
// ===========================================================================
