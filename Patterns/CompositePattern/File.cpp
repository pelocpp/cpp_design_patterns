// ===========================================================================
// File.cpp
// ===========================================================================

#include "File.h"

#include <print>
#include <string>

// c'tor(s)
File::File(const std::string& name, const std::string& data)
    : m_name{ name }, m_data{ data }
{}

// getter
const std::string& File::getName() const { return m_name; }
const std::string& File::getData() const { return m_data; }

// public interface
void File::display(const std::string& indent) const {

    std::string s{ indent + "  " };
    std::println("{}{} - data: {}", s, m_name, m_data);
}

// ===========================================================================
// End-of-File
// ===========================================================================
