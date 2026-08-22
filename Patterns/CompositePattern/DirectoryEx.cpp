// ===========================================================================
// DirectoryEx.cpp
// ===========================================================================

#include "DirectoryEx.h"

#include <memory>
#include <print>
#include <string>
#include <vector>

// c'tor(s)
DirectoryEx::DirectoryEx(const std::string& name) : m_name(name) {}

// getter
const std::string& DirectoryEx::getName() const { return m_name; }

// public interface
void DirectoryEx::addFileComponent(std::shared_ptr<IFileComponent> fc) {
    m_contents.push_back(std::move(fc));
}

void DirectoryEx::display(const std::string& indent) const {

    std::string s{ indent + indent };
    std::println("{}{}", s, m_name);

    for (const auto& fileComponent : m_contents) {
        fileComponent->display(s);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
