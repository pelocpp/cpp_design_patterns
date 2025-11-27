// ===========================================================================
// Client.cpp - Pimpl Idiom with Copy- & Move-Semantics
// ===========================================================================

#include <iostream>

#include "Control.h"

void pimpl_03()
{
    using namespace PimplVariantWithCopyMoveSemantics;

    Control ctrl;
    ctrl.resize(100, 20);
    ctrl.setText("sample control");
    ctrl.hide();

    Control c2 = ctrl; // copy: compiles !!!
    c2.show();

    Control c3 = std::move(ctrl);  // move: compiles !!!
    c3.hide();
}

// ===========================================================================
// End-of-File
// ===========================================================================
