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

    //Directory dir1 ("Directory 1:");
    //Directory dir2 ("Directory 2:");
    //Directory dir3 ("Directory 3:");

    //File file1 ("File 1", 101);
    //File file2 ("File 2", 102);
    //File file3 ("File 3", 103);
    //File file4 ("File 4", 104);
    //File file5 ("File 5", 105);

    //dir1.addFileComponent(&file1);
    //dir1.addFileComponent(&file2);
    //dir1.addFileComponent(&dir2);
    //dir2.addFileComponent(&file3);
    //dir2.addFileComponent(&dir3);
    //dir3.addFileComponent(&file4);
    //dir3.addFileComponent(&file5);

    auto dir1 = std::make_unique<Directory>("Directory 1");
    auto dir2 = std::make_unique<Directory>("Directory 2");
    auto dir3 = std::make_unique<Directory>("Directory 3");

    auto file1 = std::make_unique<File>("File 1", 101);
    auto file2 = std::make_unique<File>("File 2", 102);
    auto file3 = std::make_unique<File>("File 3", 103);
    auto file4 = std::make_unique<File>("File 4", 104);
    auto file5 = std::make_unique<File>("File 5", 105);

    //dir1.addFileComponent(&file1);
//dir1.addFileComponent(&file2);
//dir1.addFileComponent(&dir2);
//dir2.addFileComponent(&file3);
//dir2.addFileComponent(&dir3);
//dir3.addFileComponent(&file4);
//dir3.addFileComponent(&file5);

    dir1->addFileComponent(std::move(file1));
    dir1->addFileComponent(std::move(file2));
    dir2->addFileComponent(std::move(file3));
    dir3->addFileComponent(std::move(file4));
    dir3->addFileComponent(std::move(file5));
    dir1->addFileComponent(std::move(dir2));
    dir2->addFileComponent(std::move(dir3));

    dir1->display(0);
}

// ===========================================================================
// End-of-File
// ===========================================================================
