#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include "FileComponent.h"
#include "File.h"
#include "DirectoryEx.h"

// TODO: Geht da auch const
void exploreDirectory(const std::filesystem::path& p, std::shared_ptr<DirectoryEx>& d) {
// void exploreDirectory(const std::filesystem::path& p, DirectoryEx& d) {

    if (std::filesystem::exists(p) && std::filesystem::is_directory(p)) {

        for (const auto& entry : std::filesystem::directory_iterator(p)) {

            const std::filesystem::path filename = entry.path().filename();
            if (std::filesystem::is_directory(entry.status())) {

                std::cout << "DIR: " <<  filename.string() << std::endl;

                std::shared_ptr<FileComponent> dir1 = std::make_shared<DirectoryEx>(filename.string());  //  TODO  DER CAST ?!?!?!?!

                d->addFileComponent(dir1);  //  TODO  DER CAST ?!?!?!?!

                std::shared_ptr<DirectoryEx> derived =  std::dynamic_pointer_cast<DirectoryEx> (dir1);

                exploreDirectory(filename, derived);

            }
            else if (std::filesystem::is_regular_file(entry.status())) {

               std::cout << "FILE: " << filename.string() << std::endl;

                std::error_code err = std::error_code{};
                uintmax_t filesize = std::filesystem::file_size(entry, err);
                std::shared_ptr<FileComponent> file = std::make_shared<File>(filename.string(), std::to_string(filesize));
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
    R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns)";

void test_filesystem_10() {

    std::string s = { path3 };
    std::filesystem::path path = { s };
   //  DirectoryEx dir(s);
    
    std::shared_ptr<DirectoryEx> dir = std::make_shared<DirectoryEx>(s);
    exploreDirectory(path, dir);

    std::cout << "=======================================================" << std::endl;

    dir->display(" ");
}