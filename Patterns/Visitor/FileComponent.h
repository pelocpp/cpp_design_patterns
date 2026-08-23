// ===========================================================================
// FileComponent.h // Visitor Pattern
// ===========================================================================

#pragma once

#include "FileSystemElement.h"

class IFileComponent : public FileSystemElement
{
public:
    virtual ~IFileComponent() = default;
};

// ===========================================================================
// End-of-File
// ===========================================================================
