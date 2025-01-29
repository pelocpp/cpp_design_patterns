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
        virtual ~IShape() {}

        virtual void draw() = 0;
    };

    class Rectangle : public IShape 
    {
    public:
        Rectangle() {}

        void draw() override
        {
            std::cout << "> Rectangle::draw()" << std::endl;
        }
    };

    class Square : public IShape 
    {
    public:
        Square() {}

        void draw() override
        {
            std::cout << "> Square::draw()" << std::endl;
        }
    };

    class Circle : public IShape 
    {
    public:
        Circle() {}

        void draw() override
        {
            std::cout << "> Circle ::draw()" << std::endl;
        }
    };

    class ShapeFactory
    {
    public:
        enum class ShapeKind
        {
            Rectangle,
            Square,
            Circle,
            None
        };

        std::shared_ptr<IShape> getShape(ShapeKind shapeType)
        {
            std::shared_ptr<IShape> shapePtr;

            switch (shapeType)
            {
            case ShapeKind::Rectangle:
                shapePtr = std::make_shared<Rectangle>();
                break;

            case ShapeKind::Square:
                shapePtr = std::make_shared<Square>();
                break;

            case ShapeKind::Circle:
                shapePtr = std::make_shared<Circle>();
                break;

            default:
                std::string msg = "Invalid Shape Kind";
                throw std::runtime_error{ msg };
            }

            return shapePtr;
        }
    };

    static void test_without_factory()
    {
        // using classes explicitely
        //
        Rectangle* rect{ new Rectangle{} };
        rect->draw();

        Circle* circle{ new Circle{} };
        circle->draw();

        Square* square{ new Square{} };
        square->draw();
    }

    static void test_with_factory()
    {
        // using classes indirectly with factory
        // (knowledge about explicit classes not necessary)
        // 
        ShapeFactory shapeFactory;

        std::shared_ptr<IShape> shape{};

        shape = shapeFactory.getShape(ShapeFactory::ShapeKind::Circle);
        shape->draw();

        shape = shapeFactory.getShape(ShapeFactory::ShapeKind::Rectangle);
        shape->draw();

        shape = shapeFactory.getShape(ShapeFactory::ShapeKind::Square);
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
