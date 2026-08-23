// ===========================================================================
// Directory.cpp
// ===========================================================================

#include "Directory.h"

#include <memory>
#include <print>
#include <string>
#include <vector>

// c'tor(s)
Directory::Directory(std::string name) : m_name{ std::move(name) } {}

// getter
const std::string& Directory::getName() const noexcept { return m_name; }

// public interface
void Directory::addFileComponent(std::unique_ptr<IFileComponent> component) {
    m_contents.push_back(std::move(component));
}

void Directory::display(std::size_t depth) const {

    std::print("{:>{}}", "", depth);
    std::println("{}", m_name);

    for (const auto& fileComponent : m_contents) {
        fileComponent->display(depth + 2);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
