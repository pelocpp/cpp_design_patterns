// ===========================================================================
// Directory.h
// ===========================================================================

#pragma once

#include "FileComponent.h"

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

class Directory final : public IFileComponent
{
public:
    // c'tor
    Directory(std::string name);

    // getter
    [[nodiscard]]
    const std::string& getName() const noexcept;

    // public interface
    void addFileComponent(std::unique_ptr<IFileComponent> component);
    void display(std::size_t depth/* = 0*/) const override;

private:
    std::string m_name;
    std::vector<std::unique_ptr<IFileComponent>> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
