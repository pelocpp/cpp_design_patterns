// ===========================================================================
// Directory.h
// ===========================================================================

#pragma once

#include "FileComponent.h"

#include <string>
#include <vector>

class Directory : public IFileComponent {
public:
    // c'tor(s)
    Directory() {}
    Directory(const std::string& name);

    // getter
    const std::string& getName() const;

    // public interface
    void addFileComponent(IFileComponent*);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<IFileComponent*> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
