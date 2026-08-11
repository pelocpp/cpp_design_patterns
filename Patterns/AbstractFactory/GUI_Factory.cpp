// ===========================================================================
// GUI_Factory.cpp // Abstract Factory Pattern
// Example of a GUI Factory: Linux / Windows / macOS UI
// ===========================================================================

#include <map>
#include <memory>
#include <print>
#include <string>

// ===========================================================================
// Abstract Products
// ===========================================================================

/**
 * Each distinct product of a product family (UI Elements) should have a base interface.
 * All variants of this product (UI Element) must implement this interface.
 */
class AbstractButton {
public:
    virtual ~AbstractButton() = default;

    virtual std::string draw() const = 0;
};

class AbstractCheckbox {
public:
    virtual ~AbstractCheckbox() = default;

    virtual std::string draw() const = 0;
};

// ===========================================================================
// Concrete Products
// ===========================================================================

/**
 * Implementation of concrete UI Elements are created
 * by corresponding Concrete Factories.
 */
class LinuxButton final : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Linux Button";
    }
};

class WinButton final : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Windows Button";
    }
};

class MacButton final : public AbstractButton
{
public:
    std::string draw() const override {
        return "Drawing a Mac Button";
    }
};

// ===========================================================================

class LinuxCheckbox final : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Linux Checkbox";
    }
};

class WinCheckbox final : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Windows Checkbox";
    }
};

class MacCheckbox final : public AbstractCheckbox
{
public:
    std::string draw() const override {
        return "Drawing a Mac Checkbox";
    }
};

// ===========================================================================
// Abstract Factory
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
    virtual ~AbstractFactory() = default;

    [[nodiscard]]
    virtual std::unique_ptr<AbstractButton> createButton() const = 0;
    
    [[nodiscard]]
    virtual std::unique_ptr<AbstractCheckbox> createCheckbox() const = 0;
};

// ===========================================================================
// Concrete Factories
// ===========================================================================

/** 
 * Each Concrete Factory creates one complete product family. 
 */

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
    [[nodiscard]]
    std::unique_ptr<AbstractButton> createButton() const override {
        return std::make_unique<LinuxButton>();      // <== concrete button returned
    }

    [[nodiscard]]
    std::unique_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_unique<LinuxCheckbox>();    // <== concrete button returned
    }
};

class WindowsFactory : public AbstractFactory {
public:
    [[nodiscard]]
    std::unique_ptr<AbstractButton> createButton() const override {
        return std::make_unique<WinButton>();        // <== concrete button returned
    }

    [[nodiscard]]
    std::unique_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_unique<WinCheckbox>();      // <== concrete button returned
    }
};

class MacFactory : public AbstractFactory {
public:
    [[nodiscard]]
    std::unique_ptr<AbstractButton> createButton() const override {
        return std::make_unique<MacButton>();        // <== concrete button returned
    }

    [[nodiscard]]
    std::unique_ptr<AbstractCheckbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();      // <== concrete button returned
    }
};

// ===================================================================================

/**
 * The client code works with factories and products only through abstract types:
 * AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

// test function without 'clientCode' abstraction
static void test_gui_factory_example_01()
{
    MacFactory macFactory;

    auto macButton = macFactory.createButton();

    std::string result{ macButton->draw() };

    std::println("Draw: {}", result);
}

/**
 * The client works exclusively with the Abstract Factory
 * and Abstract Product interfaces.
 *
 * The concrete product types remain unknown to the client.
 */

// test functions with 'clientCode' abstraction
static void clientCode(const AbstractFactory& factory)
{
    auto btn = factory.createButton();
    std::string result{ btn->draw() };
    std::println("Draw: {}", result);

    auto cb = factory.createCheckbox();
    result = cb->draw();
    std::println("Draw: {}", result);
}

// test functions using 'clientCode' abstraction
static void test_gui_factory_example_02()
{
    std::println("Linux GUI:");
    LinuxFactory linuxFactory; 
    clientCode(linuxFactory); 
    
    std::println(); 

    std::println("Windows GUI:");
    WindowsFactory windowsFactory;
    clientCode(windowsFactory); 

    std::println();
    
    std::println("macOS GUI:");
    MacFactory macFactory;
    clientCode(macFactory);
}

void test_gui_factory()
{
    test_gui_factory_example_01();
    test_gui_factory_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
