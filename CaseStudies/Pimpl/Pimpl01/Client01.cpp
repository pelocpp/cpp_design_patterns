// ===========================================================================
// Client.cpp - No Pimpl Idiom
// ===========================================================================

#include <iostream>

#include "Control.h"

void pimpl_01()
{
    using namespace NoPimplVariant;

    Control ctrl;
    ctrl.resize(20, 30);
    ctrl.hide();
    ctrl.show();
}

void pimpl_01a()
{
    using namespace NoPimplVariant;

    Control ctrl;
    ctrl.resize(100, 20);
    ctrl.setText("sample control");
    ctrl.hide();

    Control c2 = ctrl; // copy: compiles
    c2.show();

    Control c3 = std::move(c2); // move: compiles
    c3.hide();
}

// ===========================================================================
// End-of-File
// ===========================================================================
