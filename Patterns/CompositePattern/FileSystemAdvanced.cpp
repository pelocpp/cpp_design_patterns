// ===========================================================================
// FileSystemAdvanced.cpp // Advanced Filesystem Test // Composite Pattern
// ===========================================================================

#include "FileComponent.h"
#include "File.h"
#include "Directory.h"

#include <cstdint>
#include <filesystem>
#include <memory>
#include <print>
#include <string>

static void exploreDirectory(const std::filesystem::path& path, const std::unique_ptr<Directory>& dir) {

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {

        for (const auto& entry : std::filesystem::directory_iterator(path)) {

            const std::filesystem::path filename{ entry.path().filename() };

            if (std::filesystem::is_directory(entry.status())) {

                /*const*/ std::unique_ptr<IFileComponent> subDir{
                    std::make_unique<Directory>(filename.string())
                };
                
                dir->addFileComponent(std::move(subDir)); 
  
              //  exploreDirectory(entry, std::dynamic_pointer_cast<Directory> (subDir));
            }
            else if (std::filesystem::is_regular_file(entry.status())) {

                std::error_code err{ std::error_code{} };

                std::uintmax_t filesize = std::filesystem::file_size(entry, err);
                
                std::unique_ptr<IFileComponent> file =
                    std::make_unique<File>(filename.string(), static_cast<std::size_t>(filesize));
                
                dir->addFileComponent(std::move(file));
            }
        }
    }
}

// ===========================================================================

// directory with less files, no subdirectories
// 
// Absolute path:
// constexpr const char* path1 =
//    R"(C:\Development\GitHub_Cpp_Repositories\Cpp_Design_Patterns\Patterns\CompositePattern\Resources)";

constexpr const char* path1 = R"(..\..\Patterns\CompositePattern\Resources)";

// directory without many files and subdirectories
// Absolute path:
//constexpr const char* path2 =
//    R"(C:\Development\GitHub_Cpp_Repositories\Cpp_Design_Patterns\Patterns\CompositePattern\x64)";

constexpr const char* path2 = R"(..\..\Patterns\CompositePattern\x64)";

void test_filesystem_02_advanced() {

    std::string s { path2 };
    std::filesystem::path path { s };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", s);
    }
    else {
        std::unique_ptr<Directory> dir{ std::make_unique<Directory>(s) };
        exploreDirectory(path, dir);
        //dir->display(" ");
        dir->display(0);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
