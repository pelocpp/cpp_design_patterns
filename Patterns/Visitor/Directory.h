// ===========================================================================
// Directory.h // Visitor Pattern
// ===========================================================================

#pragma once

#include "FileComponent.h"
#include "FileSystemElement.h"
#include "FileSystemVisitor.h"

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

class Directory final : public IFileComponent {
public:
    // c'tor
    Directory() = default;
    Directory(std::string name);

    // getter
    [[nodiscard]]
    const std::string& name() const noexcept;
    const std::vector<std::unique_ptr<IFileComponent>>& children() const;

    // public interface
    void addFileComponent(std::unique_ptr<IFileComponent> component);

    // visitor pattern interface
    void accept(FileSystemVisitor& visitor) override;

private:
    std::string m_name;
    std::vector<std::unique_ptr<IFileComponent>> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
