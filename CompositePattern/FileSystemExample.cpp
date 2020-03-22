// ===========================================================================
// Example.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

#include "FileComponent.h"
#include "File.h"
#include "Directory.h"

void test_filesystem () {

    Directory dir1 ("Directory 1:");
    Directory dir2 ("Directory 2:");
    Directory dir3 ("Directory 3:");

    File file1 ("File 1", "Data of file 1");
    File file2 ("File 2", "Data of file 2");
    File file3 ("File 3", "Data of file 3");
    File file4 ("File 4", "Data of file 4");
    File file5 ("File 5", "Data of file 5");

    dir1.addFileComponent(&file1);
    dir1.addFileComponent(&file2);
    dir1.addFileComponent(&dir2);
    dir2.addFileComponent(&file3);
    dir2.addFileComponent(&dir3);
    dir3.addFileComponent(&file4);
    dir3.addFileComponent(&file5);

    dir1.display(" ");
}

// ===========================================================================
// End-of-File
// ===========================================================================
