// ===========================================================================
// FileSystemBeginners.cpp // Simple Filesystem Test // Composite Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>



#include "FileComponent.h"
#include "File.h"
#include "Directory.h"

void test_filesystem_01_beginners() {

    auto root = std::make_unique<Directory>("Directory 1");
    auto dir2 = std::make_unique<Directory>("Directory 2");
    auto dir3 = std::make_unique<Directory>("Directory 3");

    auto file1 = std::make_unique<File>("File 1", 101);
    auto file2 = std::make_unique<File>("File 2", 102);
    auto file3 = std::make_unique<File>("File 3", 103);
    auto file4 = std::make_unique<File>("File 4", 104);
    auto file5 = std::make_unique<File>("File 5", 105);

    root->addFileComponent(std::move(file1));
    root->addFileComponent(std::move(file2));
    dir2->addFileComponent(std::move(file3));
    dir3->addFileComponent(std::move(file4));
    dir3->addFileComponent(std::move(file5));
    root->addFileComponent(std::move(dir2));
    root->addFileComponent(std::move(dir3));

    root->display(2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
