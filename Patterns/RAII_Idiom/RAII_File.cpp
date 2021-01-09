// =====================================================================================
// RAIIFile.cpp
// =====================================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "stdio.h"

class RAIIFile {
public:
    explicit RAIIFile(const std::string& name)
    {
        m_file = fopen(name.c_str(), "w");
    }

    ~RAIIFile()
    {
        fclose(m_file);
    }

    void write(const std::string& s)
    {
        const char* cp = s.c_str();
        fprintf(m_file, "%s", cp);
    }

private:
    FILE* m_file;
};

void test_file_example()
{
    RAIIFile file("example.txt");
    file.write("123\n");
    file.write("456\n");
}

// =====================================================================================
// End-of-File
// =====================================================================================
