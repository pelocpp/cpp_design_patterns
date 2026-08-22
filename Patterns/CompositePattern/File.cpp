// ===========================================================================
// File.cpp
// ===========================================================================

#include "File.h"

#include <cstddef>
#include <print>
#include <string>

// c'tor(s)
File::File() : m_size{} {}

File::File(std::string name, std::size_t size)
    : m_name{ std::move(name) }, m_size{ size }
{}

// getter
[[nodiscard]]
const std::string& File::name() const noexcept { return m_name; }

[[nodiscard]]
std::size_t File::size() const noexcept { return m_size; }

// public interface
void File::display(std::size_t depth) const /*override*/ {

    //std::string s{ indent + "  " };
    //std::println("{}{} - Size: {}", s, m_name, m_size);

    std::print("{:{}}", "", depth * 2);
    std::println("{} - Size: {}", m_name, m_size);
}

// ===========================================================================
// End-of-File
// ===========================================================================
