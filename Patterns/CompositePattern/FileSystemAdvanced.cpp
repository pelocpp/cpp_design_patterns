#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include "FileComponent.h"
#include "File.h"
#include "DirectoryEx.h"

void exploreDirectory(const std::filesystem::path& p, const std::shared_ptr<DirectoryEx>& dir) {

    if (std::filesystem::exists(p) && std::filesystem::is_directory(p)) {

        for (const auto& entry : std::filesystem::directory_iterator(p)) {

            const std::filesystem::path filename = entry.path().filename();

            if (std::filesystem::is_directory(entry.status())) {

                const std::shared_ptr<FileComponent> subDir =
                    std::make_shared<DirectoryEx>(filename.string());
                
                dir->addFileComponent(subDir); 
  
                exploreDirectory(entry, std::dynamic_pointer_cast<DirectoryEx> (subDir));
            }
            else if (std::filesystem::is_regular_file(entry.status())) {

                std::error_code err = std::error_code{};
                uintmax_t filesize = std::filesystem::file_size(entry, err);
                
                std::shared_ptr<FileComponent> file = 
                    std::make_shared<File>(filename.string(), std::to_string(filesize));
                
                dir->addFileComponent(file);
            }
        }
    }
}

// directory with just 2 files, no subdirectories
constexpr const char* path1 =
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_GeneralSnippets\GeneralSnippets\FileSystem)";

// directory without subdirectories
constexpr const char* path2 =
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\Patterns\CompositePattern)";

void test_filesystem_02() {

    std::string s = { path2 };
    std::filesystem::path path = { s };
    std::shared_ptr<DirectoryEx> dir = std::make_shared<DirectoryEx>(s);
    exploreDirectory(path, dir);
    dir->display(" ");
}