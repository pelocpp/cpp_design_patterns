// ===========================================================================
// File.cpp // Visitor Pattern
// ===========================================================================

#include "File.h"

#include <cstddef>
#include <string>

// c'tor(s)
File::File(std::string name, std::size_t size)
    : m_name{ std::move(name) }, m_size{ size }
{}

// getter
[[nodiscard]]
const std::string& File::name() const noexcept { return m_name; }

[[nodiscard]]
std::size_t File::size() const noexcept { return m_size; }

// Visitor pattern
void File::accept(FileSystemVisitor& visitor)
{
    visitor.visit(*this);
}

// ===========================================================================
// End-of-File
// ===========================================================================
