// ===========================================================================
// SizeVisitor.h // Visitor Pattern
// ===========================================================================

#pragma once

#include "FileSystemVisitor.h"

#include <cstddef>

class SizeVisitor : public FileSystemVisitor {
private:
    std::size_t m_totalSize{};

public:
    SizeVisitor() = default;
    virtual ~SizeVisitor() = default;

    void visit(File& file) override;
    void visit(Directory& directory) override;

    // getter
    [[nodiscard]] std::size_t totalSize() const noexcept;
};

// ===========================================================================
// End-of-File
// ===========================================================================
