// ===========================================================================
// Control.cpp - Pimpl Idiom with separate header file
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ControlPimpl.h"
#include "Control.h"

namespace PimplVariantWithSeparateHeaderFile {

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
}

// ===========================================================================
// End-of-File
// ===========================================================================
