// ===========================================================================
// VirtualConstructor_02.cpp // Factory Method // Virtual Constructor Idiom
// ===========================================================================

#include <iostream>
#include <string>

namespace VirtualConstructorIdiom_02 {

    // Product
    class Window {
    public:
        virtual Window* create() = 0;
        virtual Window* clone() = 0;

        virtual ~Window() {};
    };

    // Concrete Products 
    class DefaultWindow : public Window {
        DefaultWindow* create() override {
            std::cout << "Create DefaultWindow" << std::endl;
            return new DefaultWindow();
        }
        DefaultWindow* clone() override {
            std::cout << "Clone DefaultWindow" << std::endl;
            return new DefaultWindow(*this);
        }
    };

    class FancyWindow : public Window {
        FancyWindow* create() override {
            std::cout << "Create FancyWindow" << std::endl;
            return new FancyWindow();
        }
        FancyWindow* clone() override {
            std::cout << "Clone FancyWindow" << std::endl;
            return new FancyWindow(*this);
        }
    };

    // Concrete Creator or Client                             
    Window* createWindow(Window& oldWindow) {
        return oldWindow.create();
    }

    Window* cloneWindow(Window& oldWindow) {
        return oldWindow.clone();
    }
}

void test_virtual_constructor_idiom_02()
{
    using namespace VirtualConstructorIdiom_02;

    DefaultWindow defaultWindow;
    FancyWindow fancyWindow;

    Window* defaultWindow1 = createWindow(defaultWindow);
    Window* fancyWindow1 = createWindow(fancyWindow);

    Window* defaultWindow2 = cloneWindow(defaultWindow);
    Window* fancyWindow2 = cloneWindow(fancyWindow);

    delete defaultWindow1;
    delete fancyWindow1;
    delete defaultWindow2;
    delete fancyWindow2;
}

// ===========================================================================
// End-of-File
// ===========================================================================
