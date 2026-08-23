// ===========================================================================
// SizeVisitor.cpp // Visitor Pattern
// ===========================================================================

#pragma once

#include "SizeVisitor.h"

#include "File.h"
#include "Directory.h"

void SizeVisitor::visit(File& file)
{
    m_totalSize += file.size();
}

void SizeVisitor::visit(Directory& directory)
{
    for (auto& child : directory.children())
    {
        child->accept(*this);
    }
}

[[nodiscard]]
std::size_t SizeVisitor::totalSize() const noexcept
{
    return m_totalSize;
}

// ===========================================================================
// End-of-File
// ===========================================================================
