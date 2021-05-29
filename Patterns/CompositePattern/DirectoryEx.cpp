// ===========================================================================
// DirectoryEx.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "FileComponent.h"
#include "DirectoryEx.h"

// c'tor(s)
DirectoryEx::DirectoryEx(const std::string& name) : m_name(name) {}

// getter
std::string DirectoryEx::getName() { return m_name; }

// public interface
void DirectoryEx::addFileComponent(std::shared_ptr<FileComponent> fc) {
    m_contents.push_back(std::move(fc));
}

void DirectoryEx::display(const std::string& indent) const {

    std::string s{ indent + indent };
    std::cout << s << m_name << std::endl;

    for (const auto& fileComponent : m_contents) {
        fileComponent->display(s);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
