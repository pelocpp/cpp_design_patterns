// =====================================================================================
// RAII_Ofstream.cpp
// =====================================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "stdio.h"

class RAIIFile {
public:
    explicit RAIIFile(FILE* file) : m_file(file) {}
    ~RAIIFile() { fclose (m_file); }

    void write(std::string s)
    {
        const char* cp = s.c_str();
        fprintf(m_file, "%s", cp);
    }

private:
    FILE* m_file;
};

void test_file_example()
{
    FILE* ptr = fopen("example.txt", "w");
    RAIIFile rfile(ptr);
    rfile.write("111\n");
    rfile.write("222\n");
}

// =====================================================================================
// End-of-File
// =====================================================================================
