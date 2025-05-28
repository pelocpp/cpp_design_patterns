// ===========================================================================
// PaintBrush.cpp // Flyweight Pattern
// ===========================================================================

#include <iostream>
#include <unordered_map>
#include <memory>

namespace PaintBrushFlyweight {

    class Pen
    {
    public:
        ~Pen() {}

        virtual void setColor(std::string color) = 0;
        virtual void draw(std::string content) = 0;
        virtual void print() = 0;
    };

    enum class BrushSize { Thin, Medium, Thick };

    class ThickPen : public Pen
    {
    private:
        const BrushSize m_brushSize;  // intrinsic state - shareable
        std::string m_color;          // extrinsic state - supplied by client

    public:
        ThickPen() : m_brushSize{ BrushSize::Thick } {}

        void setColor(std::string color) override {
            m_color = color;
        }

        void draw(std::string content) override {
            std::cout 
                << "Drawing THICK content in color : " << m_color 
                << " - " << content << std::endl;
        }

        void print() override {
            std::cout << this << std::endl;
        }
    };

    class ThinPen : public Pen
    {
    private:
        const BrushSize m_brushSize;  // intrinsic state - shareable
        std::string m_color;          // extrinsic state - supplied by client

    public:
        ThinPen() : m_brushSize{ BrushSize::Thin } {}

        void setColor(std::string color) override {
            m_color = color;
        }

        void draw(std::string content) override {
            std::cout 
                << "Drawing THIN content in color : " << m_color 
                << " - " << content << std::endl;
        }

        void print() override {
            std::cout << this << std::endl;
        }
    };

    class PenFactory
    {
    private:
        static std::unordered_map<std::string, std::shared_ptr<Pen>> pensMap;

    public:
        static std::shared_ptr<Pen> getThickPen(std::string color)
        {
            std::string key{ color + "-THICK" };

            std::shared_ptr<Pen> pen{ pensMap[key] };

            if (pen != nullptr) {
                return pen;
            }
            else {
                pen = std::make_shared<ThickPen>();
                pen->setColor(color);
                pensMap[key] = pen;
            }

            return pen;
        }

        static std::shared_ptr<Pen> getThinPen(std::string color)
        {
            std::string key{ color + "-THIN" };

            std::shared_ptr<Pen> pen{ pensMap[key] };

            if (pen != nullptr) {
                return pen;
            }
            else {
                pen = std::make_shared<ThickPen>();
                pen->setColor(color);
                pensMap[key] = pen;
            }

            return pen;
        }
    };

    // out-of-class definition of static class member
    std::unordered_map<std::string, std::shared_ptr<Pen>> PenFactory::pensMap;
}

void test_paint_brush()
{
    using namespace PaintBrushFlyweight;

    std::shared_ptr<Pen> yellowThinPen1{ PenFactory::getThickPen("YELLOW") };  // creating new pen
    yellowThinPen1->draw("Hello World !!");

    std::shared_ptr<Pen> yellowThinPen2{ PenFactory::getThickPen("YELLOW") };  // pen is shared
    yellowThinPen2->draw("Hello World !!");

    std::shared_ptr<Pen> blueThinPen{ PenFactory::getThickPen("BLUE") };       // creating new pen
    blueThinPen->draw("Hello World !!");

    yellowThinPen1->print();
    yellowThinPen2->print();
    blueThinPen->print();
}

// ===========================================================================
// End-of-File
// ===========================================================================
