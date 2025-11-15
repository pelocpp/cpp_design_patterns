// ===========================================================================
// Control.cpp - Pimpl Idiom with separate header file
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ControlPimpl.h"
#include "Control.h"

namespace PimplVariantWithSeparateHeaderFile {

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
