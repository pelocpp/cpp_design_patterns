// ===========================================================================
// Control.cpp - Pimpl Idiom with Copy- & Move-Semantics
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "Control.h"

namespace PimplVariantWithCopyMoveSemantics {

    // ===========================================================================
    // declaration of pimpl class

    class ControlPimpl {
    private:
        std::string m_text;
        int m_width;
        int m_height;
        bool m_visible;

        void draw();

    public:
        ControlPimpl() : m_text(""), m_width(0), m_height(0), m_visible(true) {}

        void setText(std::string text);
        void resize(const int width, const int height);
        void show();
        void hide();
    };

    // ================================================================
    // definition of pimpl class methods

    void ControlPimpl::draw()
    {
        std::cout
            << "control "
            << std::endl
            << " visible: "
            << std::boolalpha
            << m_visible
            << std::noboolalpha
            << std::endl
            << " size: "
            << m_width
            << ", "
            << m_height
            << std::endl
            << " text: "
            << m_text
            << std::endl;
    }

    void ControlPimpl::setText(std::string text)
    {
        m_text = text;
        draw();
    }

    void ControlPimpl::resize(const int width, const int height) {
        m_width = width;
        m_height = height;
        draw();
    }

    void ControlPimpl::show()
    {
        m_visible = true;
        draw();
    }

    void ControlPimpl::hide() {
        m_visible = false;
        draw();
    }

    // ===========================================================
    // main class methods

    // default c'tor
    Control::Control() : m_pimpl(std::make_unique<ControlPimpl>()) {}

    Control::~Control() = default;  // due to 'can't delete an incomplete type'

    // move semantics - using default behaviour
    Control::Control(Control&&) noexcept = default; 
    Control& Control::operator=(Control&&) noexcept = default;

    // copy semantics - using (automatically generated) public copy constructor of ControlPimpl 
    Control::Control(const Control& op) : m_pimpl{ new ControlPimpl(*op.m_pimpl) } {}

    Control& Control::operator=(const Control& op) {
        if (this != &op) {
            m_pimpl = std::unique_ptr<ControlPimpl>(new ControlPimpl(*op.m_pimpl));
        }
        return *this;
    }

    // remaining member functions
    void Control::setText(std::string text)
    {
        m_pimpl->setText(text);
    }

    void Control::resize(const int width, const int height)
    {
        m_pimpl->resize(width, height);
    }

    void Control::show()
    {
        m_pimpl->show();
    }

    void Control::hide() {
        m_pimpl->hide();
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
