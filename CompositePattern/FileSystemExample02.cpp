// ===========================================================================
// Filesystem Test
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <filesystem>

// http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html

// https://github.com/achimoraites/DesignPatterns/blob/master/CompositePattern/FileSystem/src/ui/FileSystem.java

typedef std::vector<std::string> stringvec;

struct path_leaf_string
{
    std::string operator()(const std::filesystem::directory_entry& entry) const
    {
        // return entry.path().leaf().string();
        return entry.path().string();
    }
};

void read_directory(const std::string& name, stringvec& v)
{
    std::filesystem::path p(name);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_leaf_string());
}

void test_filesystem_02()
{
    stringvec v;
    read_directory(".", v);
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"));
}

void test_filesystem() {

    //Directory dir1("Directory 1:");
    //Directory dir2("Directory 2:");
    //Directory dir3("Directory 3:");

    //File file1("File 1", "Data of file 1");
    //File file2("File 2", "Data of file 2");
    //File file3("File 3", "Data of file 3");
    //File file4("File 4", "Data of file 4");
    //File file5("File 5", "Data of file 5");

    //dir1.addFileComponent(&file1);
    //dir1.addFileComponent(&file2);
    //dir1.addFileComponent(&dir2);
    //dir2.addFileComponent(&file3);
    //dir2.addFileComponent(&dir3);
    //dir3.addFileComponent(&file4);
    //dir3.addFileComponent(&file5);

    //dir1.display(" ");
}

// ===========================================================================
// End-of-File
// ===========================================================================
