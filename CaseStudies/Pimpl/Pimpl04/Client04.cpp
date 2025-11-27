// ===========================================================================
// Client.cpp - Pimpl Idiom with separate header file
// ===========================================================================

#include <iostream>

#include "Control.h"

void pimpl_04()
{
    using namespace PimplVariantWithSeparateHeaderFile;

    Control ctrl;
    ctrl.resize(50, 70);
    ctrl.setText("another sample control");
    ctrl.hide();

    Control c2 = ctrl; // copy: compiles !!!
    c2.show();

    Control c3 = std::move(ctrl);  // move: compiles !!!
    c3.hide();
}

// ===========================================================================
// End-of-File
// ===========================================================================
