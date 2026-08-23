// ===========================================================================
// PrintVisitor.h // Visitor Pattern
// ===========================================================================

#pragma once

#include "FileSystemVisitor.h"

#include <cstddef>

class PrintVisitor : public FileSystemVisitor {
private:
    std::size_t m_depth{};

public:
    PrintVisitor() = default;
    virtual ~PrintVisitor() = default;

    void visit(File& file) override;
    void visit(Directory& directory) override;
};

// ===========================================================================
// End-of-File
// ===========================================================================
