// ===========================================================================
// PrintVisitor.cpp // Visitor Pattern
// ===========================================================================

#pragma once

#include "PrintVisitor.h"

#include "File.h"
#include "Directory.h"

#include <print>

void PrintVisitor::visit(File& file)
{
    std::print("{:>{}}", "", m_depth);
    std::println("File: {} ({} bytes)", file.name(), file.size());
}

void PrintVisitor::visit(Directory& directory)
{
    m_depth += 2;

    std::print("{:>{}}", "", m_depth);
    std::println("Directory: {}", directory.name());

    for (auto& child : directory.children())
    {
        child->accept(*this);
    }

    m_depth -= 2;
}

// ===========================================================================
// End-of-File
// ===========================================================================
