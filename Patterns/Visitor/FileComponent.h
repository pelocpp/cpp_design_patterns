// ===========================================================================
// FileComponent.h // Visitor Pattern
// ===========================================================================

#pragma once

#include <cstddef>

class IFileComponent
{
public:
    virtual ~IFileComponent() = default;

    virtual void display(std::size_t depth) const = 0;
};

// ===========================================================================
// End-of-File
// ===========================================================================
