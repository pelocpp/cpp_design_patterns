// ===========================================================================
// Directory.cpp
// ===========================================================================

#include "Directory.h"

#include <print>
#include <string>
#include <vector>

// c'tor(s)
Directory::Directory(const std::string& name) : m_name{ name } {}

// getter
const std::string& Directory::getName() const { return m_name; }

// public interface
void Directory::addFileComponent(IFileComponent* fc) {
    m_contents.push_back(fc);
}

void Directory::display(const std::string& indent) const {

    std::string s{ indent + indent };
    std::println("{}{}", s, m_name);

    for (IFileComponent* fileComponent : m_contents) {
        fileComponent->display(s);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
