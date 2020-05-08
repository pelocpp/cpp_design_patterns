#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "FileComponent.h"
#include "File.h"
#include "DirectoryEx.h"



// TODO: Geht da auch const
void exploreDirectory(const std::filesystem::path& p, std::unique_ptr<DirectoryEx>& d) {
// void exploreDirectory(const std::filesystem::path& p, DirectoryEx& d) {

    if (std::filesystem::exists(p) && std::filesystem::is_directory(p)) {

        for (const auto& entry : std::filesystem::directory_iterator(p)) {
            const std::filesystem::path filename = entry.path().filename();
            if (std::filesystem::is_directory(entry.status())) {

                std::cout << "DIR: " <<  filename.string() << std::endl;

                std::unique_ptr<DirectoryEx> dir1 = std::make_unique<DirectoryEx>(filename.string());
                std::unique_ptr<DirectoryEx> dir2 = std::make_unique<DirectoryEx>(filename.string());

                d->addFileComponent(  (std::unique_ptr<FileComponent>&) dir1);
                exploreDirectory(filename, dir2);
            }
            else if (std::filesystem::is_regular_file(entry.status())) {

               std::cout << "FILE: " << filename.string() << std::endl;

                std::error_code err = std::error_code{};
                uintmax_t filesize = std::filesystem::file_size(entry, err);
                std::unique_ptr<FileComponent> file = std::make_unique<File>(filename.string(), std::to_string(filesize));
                d->addFileComponent(file);
            }
        }
    }
}

// just 2 files
constexpr const char* path1 =
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_GeneralSnippets\GeneralSnippets\FileSystem)";

// directory without subdirectories
constexpr const char* path2 =
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\CompositePattern)";

// directory with subdirectories
constexpr const char* path3 =
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\CompositePattern)";

void test_filesystem_10() {

    std::string s = { path2 };
    std::filesystem::path path = { s };
   //  DirectoryEx dir(s);
    
    std::unique_ptr<DirectoryEx> dir = std::make_unique<DirectoryEx>(s);
    exploreDirectory(path, dir);

    std::cout << "=======================================================" << std::endl;

    dir->display(" ");
}