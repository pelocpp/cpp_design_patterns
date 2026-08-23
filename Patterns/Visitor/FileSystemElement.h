// ===========================================================================
// FileSystemElement.h // Visitor Pattern
// ===========================================================================

#pragma once

#include "FileSystemVisitor.h"

class FileSystemElement {
public:
    virtual ~FileSystemElement() = default;

    virtual void accept(FileSystemVisitor& visitor) = 0;
};

// ===========================================================================
// End-of-File
// ===========================================================================
