// ===========================================================================
// LSP.cpp // Liskov's Substitution Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <cassert>

namespace LiskovSubstitutionPrinciple01
{
    struct Rectangle
    {
    protected:
        size_t m_width;
        size_t m_height;

    public:
        Rectangle(size_t width, size_t height)
            : m_width{ width }, m_height{ height } {}

        // getter / setter
        size_t getWidth() const { return m_width; }
        size_t getHeight() const { return m_height; }
        virtual void setWidth(size_t width) { m_width = width; }
        virtual void setHeight(size_t height) { m_height = height; }

        // public interface
        size_t area() const { return m_width * m_height; }
    };

    struct Square : public Rectangle
    {
        Square(size_t size) : Rectangle{ size, size } {}

        // getter / setter
        void setWidth(size_t width) override {
            m_width = m_height = width;
        }

        void setHeight(size_t height) override {
            m_height = m_width = height;
        }
    };

    static void process(Rectangle& r) {
        size_t w{ r.getWidth() };
        r.setHeight(10);
        //assert((w * 10) == r.area());  // fails for Square <-- !!!
    }

    static void process2(Rectangle& r) {
        size_t w{ r.getWidth() };
        r.setHeight(10);
        if (dynamic_cast<Square*>(&r) != nullptr)
            assert((r.getWidth() * r.getWidth()) == r.area());
        else
            assert((w * 10) == r.area());
    }
}

namespace LiskovSubstitutionPrinciple02
{
    struct IShape
    {
        virtual size_t area() const = 0;
    };

    struct Rectangle : public IShape
    {
    private:
        size_t m_width;
        size_t m_height;

    public:
        Rectangle(size_t width, size_t height)
            : m_width{ width }, m_height{ height } {}

        // getter / setter
        size_t getWidth() const { return m_width; }
        size_t getWeight() const { return m_height; }
        virtual void setWidth(size_t width) { m_width = width; }
        virtual void setHeight(size_t height) { m_height = height; }

        // public interface
        size_t area() const override { return m_width * m_height; }
    };

    struct Square : public IShape
    {
    private:
        size_t m_size;

    public:
        Square(size_t size) : m_size{ size } {}

        // getter / setter
        size_t getSize() const { return m_size; }
        void setSize(size_t size) { m_size = size; }

        // public interface
        size_t area() const override { return m_size * m_size; }
    };

    static void process(IShape& s)
    {
        // use polymorphic behaviour only, e.g. area()
    }
}

static void test_anti_conceptual_example_lsp()
{
    using namespace LiskovSubstitutionPrinciple01;

    Rectangle r{ 5, 5 };
    process(r);
    Square s{ 5 };
    process(s);
}

static void test_conceptual_example_lsp()
{
    using namespace LiskovSubstitutionPrinciple02;
}

void test_lsp()
{
    test_anti_conceptual_example_lsp();
    test_conceptual_example_lsp();
}

// ===========================================================================
// End-of-File
// ===========================================================================
