// ===========================================================================
// Directory.cpp // Visitor Pattern
// ===========================================================================

#include "Directory.h"

#include <memory>
#include <print>
#include <string>
#include <vector>

// c'tor(s)
Directory::Directory(std::string name) : m_name{ std::move(name) } {}

// getter
const std::string& Directory::name() const noexcept { return m_name; }

const std::vector<std::unique_ptr<IFileComponent>>& Directory::children() const
{
    return m_contents;
}

// public interface
void Directory::addFileComponent(std::unique_ptr<IFileComponent> component) {
    m_contents.push_back(std::move(component));
}

// Visitor pattern
void Directory::accept(FileSystemVisitor& visitor)
{
    visitor.visit(*this);
}

// ===========================================================================
// End-of-File
// ===========================================================================
