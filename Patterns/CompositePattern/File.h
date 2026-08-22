// ===========================================================================
// File.h
// ===========================================================================

#pragma once

#include "FileComponent.h"

#include <cstddef>
#include <string>

class File final : public IFileComponent {
public:
    File();
    File(std::string name, std::size_t size);

    // getter
    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

    void display(std::size_t depth /*= 0*/) const override;

private:
    std::string m_name;
    std::size_t m_size;
};

// ===========================================================================
// End-of-File
// ===========================================================================
