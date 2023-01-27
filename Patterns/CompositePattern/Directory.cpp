// ===========================================================================
// Directory.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

#include "FileComponent.h"
#include "Directory.h"

// c'tor(s)
Directory::Directory(const std::string& name) : m_name(name) {}

// getter
std::string Directory::getName() { return m_name; }

// public interface
void Directory::addFileComponent(IFileComponent* fc) {
    m_contents.push_back(fc);
}

void Directory::display(const std::string& indent) const {

    std::string s{ indent + indent };
    std::cout << s << m_name << std::endl;

    for (IFileComponent* fileComponent : m_contents) {
        fileComponent->display(s);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
