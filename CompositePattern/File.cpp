// ===========================================================================
// File.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "FileComponent.h"
#include "File.h"

File::File(const std::string& name, const std::string& data) : m_name(name), m_data(data) {}

// getter
std::string File::getName() { return m_name; }
std::string File::getData() { return m_data; }

void File::display(const std::string& indent) const {

    std::string s = indent + indent;
    std::cout << s << m_name << " - data: " << m_data << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
