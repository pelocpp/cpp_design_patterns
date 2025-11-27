// ===========================================================================
// Control.cpp - No Pimpl Idiom
// ===========================================================================

#include <iostream>

#include "Control.h"

namespace NoPimplVariant {

    // implementation of private methods
    void Control::draw()
    {
        std::cout
            << "no pimple control "
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

    // implementation of public interface
    Control::Control() : m_text(""), m_width(0), m_height(0), m_visible(true) {}

    void Control::setText(std::string text)
    {
        m_text = text;
        draw();
    }

    void Control::resize(const int width, const int height) {
        m_width = width;
        m_height = height;
        draw();
    }

    void Control::show()
    {
        m_visible = true;
        draw();
    }

    void Control::hide() {
        m_visible = false;
        draw();
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
