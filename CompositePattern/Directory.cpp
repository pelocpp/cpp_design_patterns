// ===========================================================================
// Directory.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

#include "FileComponent.h"
#include "Directory.h"

// c'tors
Directory::Directory(const std::string& name) : m_name(name) {}

// getter
std::string Directory::getName() { return m_name; }

void Directory::addFileComponent(FileComponent* fc) {
    //if (!contents.contains(fc)) {
    //    contents.add(fc);
    //}

    m_contents.push_back(fc);
}

void Directory::display(const std::string& indent) const {

    std::string s = indent + indent;
    std::cout << s << m_name << std::endl;

    for (FileComponent* fileComponent : m_contents) {
        fileComponent->display(s);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
