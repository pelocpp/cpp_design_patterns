// ===========================================================================
// DirectoryEx.h
// ===========================================================================

#pragma once

#include "FileComponent.h"

#include <string>
#include <vector>
#include <memory>

class DirectoryEx : public IFileComponent
{
public:
    // c'tor(s), d'tor
    DirectoryEx() {}
    DirectoryEx(const std::string& name);
    ~DirectoryEx() {}

    // getter
    const std::string& getName() const;

    // public interface
    void addFileComponent(std::shared_ptr<IFileComponent>);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<std::shared_ptr<IFileComponent>> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
