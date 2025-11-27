// ===========================================================================
// Client.cpp - Pimpl Idiom
// ===========================================================================

#include <iostream>

#include "Control.h"

void pimpl_02()
{
    using namespace PimplVariant;

    Control ctrl;
    ctrl.resize(10, 15);
    ctrl.hide();
    ctrl.show();
}

void pimpl_02a()
{
    using namespace PimplVariant;

    Control ctrl;
    ctrl.resize(100, 20);

    // Control c2 = ctrl; // doesn't compile: std::unique_ptr !!!
    // c2.show();

    // Control c3 = std::move(ctrl);  // doesn't compile

    // PimplVariant::Control::Control(const PimplVariant::Control &)":
    // (declared implicitly) cannot be referenced -- it is a deleted function
}

// ===========================================================================
// End-of-File
// ===========================================================================
