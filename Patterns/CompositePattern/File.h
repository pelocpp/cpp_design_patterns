// ===========================================================================
// File.h
// ===========================================================================

#pragma once

#include "FileComponent.h"

#include <string>

class File : public IFileComponent {
public:
    File() {}
    File(const std::string& name, const std::string& data);
    ~File() {}

    // getter
    const std::string& getName() const;
    const std::string& getData() const;

    void display(const std::string&) const override;

private:
    std::string m_name;
    std::string m_data;
};

// ===========================================================================
// End-of-File
// ===========================================================================
