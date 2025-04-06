// ===========================================================================
// GUI Factory // Example 'Windows / Linux / Mac Buttons'
// ===========================================================================

#include <string>
#include <memory>
#include <map>
#include <print>

// ===========================================================================

/**
 * Each distinct product of a product family (UI Elements) should have a base interface.
 * All variants of this product (UI Element) must implement this interface.
 */
class AbstractButton {
public:
    virtual ~AbstractButton() {}

    virtual std::string draw() const = 0;
};

class AbstractCheckbox {
public:
    virtual ~AbstractCheckbox() {}

    virtual std::string draw() const = 0;
};

// ===========================================================================

/**
 * Implementation of concrete UI Elements are created
 * by corresponding Concrete Factories.
 */
class LinuxButton : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Linux Button";
    }
};

class WinButton : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Windows Button";
    }
};

class MacButton : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Mac Button";
    }
};

// ===========================================================================

class LinuxCheckbox : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Linux Checkbox";
    }
};

class WinCheckbox : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Windows Checkbox";
    }
};

class MacCheckbox : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Mac Checkbox";
    }
};

// ===========================================================================

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */

/**
 * Concrete UI Elements are created by corresponding Concrete Factories.
 * A common interface guarantees that resulting products are compatible.
 */
class AbstractFactory
{
public:
    virtual std::shared_ptr<AbstractButton> createButton() const = 0;
    virtual std::shared_ptr<AbstractCheckbox> createCheckbox() const = 0;
};

// ===================================================================================

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible.
 *
 * NOTE: Signatures of the Concrete Factory's methods return an abstract product,
 *       while inside the method a concrete product is instantiated.
 * 
 *       There a similarities with the "Virtual Constructor" Pattern
 *       a.k.a. "Prototype Pattern"
 */
class LinuxFactory : public AbstractFactory {
public:
    std::shared_ptr<AbstractButton> createButton() const override {
        return std::make_shared<LinuxButton>();      // <== concrete button returned
    }

    std::shared_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_shared<LinuxCheckbox>();    // <== concrete button returned
    }
};

class WindowsFactory : public AbstractFactory {
public:
    std::shared_ptr<AbstractButton> createButton() const override {
        return std::make_shared<WinButton>();        // <== concrete button returned
    }

    std::shared_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_shared<WinCheckbox>();      // <== concrete button returned
    }
};

class MacFactory : public AbstractFactory {
public:
    std::shared_ptr<AbstractButton> createButton() const override {
        return std::make_shared<MacButton>();        // <== concrete button returned
    }

    std::shared_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_shared<MacCheckbox>();      // <== concrete button returned
    }
};

// ===================================================================================

class GenericButtonFactory
{
public:

    GenericButtonFactory()
    {
        m_factories["Linux"] = std::make_shared<LinuxFactory>();
        m_factories["Win"] = std::make_shared<WindowsFactory>();
        m_factories["Mac"] = std::make_shared<MacFactory>();
    }

    const std::shared_ptr<AbstractButton> getButton(const std::string& name) {

        std::shared_ptr<AbstractFactory>& factory{ m_factories[name] };
        const std::shared_ptr<AbstractButton> button{ factory->createButton() };
        return button;
    }

    const std::shared_ptr<AbstractFactory> getFactory(const std::string& name) {

        return m_factories[name];
    }

private:
    std::map<std::string, std::shared_ptr<AbstractFactory>> m_factories;
};

// ===================================================================================

/**
 * The client code works with factories and products only through abstract types:
 * AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

// test functions without 'clientCode' abstraction
static void test_gui_factory_example_01()
{
    MacFactory macFactory{};
    const std::shared_ptr<AbstractButton> macButton{ macFactory.createButton() };
    std::string result{ macButton->draw() };
    std::println("Draw: {}", result);
}

static void test_gui_factory_example_02()
{
    GenericButtonFactory buttonFactory{};
    const std::shared_ptr<AbstractButton> bp{ buttonFactory.getButton("Mac") };
    std::string result = bp->draw();
    std::println("Draw: {}", result);
}

static void clientCode(const std::shared_ptr<AbstractFactory>& factory)
{
    const std::shared_ptr<AbstractButton>& btn{ factory->createButton() };
    std::string result{ btn->draw() };
    std::println("Draw: {}", result);

    const std::shared_ptr<AbstractCheckbox>& cb{ factory->createCheckbox() };
    result = cb->draw();
    std::println("Draw: {}", result);
}

// test functions using 'clientCode' abstraction
static void test_gui_factory_example_03()
{
    GenericButtonFactory buttonFactory{};

    const std::shared_ptr<AbstractFactory> f1{ buttonFactory.getFactory("Win") };
    clientCode(f1);

    const std::shared_ptr<AbstractFactory> f2 { buttonFactory.getFactory("Mac") };
    clientCode(f2);
}

void test_gui_factory()
{
    test_gui_factory_example_01();
    test_gui_factory_example_02();
    test_gui_factory_example_03();
}

// ===========================================================================
// End-of-File
// ===========================================================================
