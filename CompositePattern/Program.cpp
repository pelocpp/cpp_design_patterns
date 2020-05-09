// ===========================================================================
// Program.cpp
// ===========================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
#include <string>
#include <memory>

// function prototypes
void test_conceptual_example();
void test_filesystem_01();
void test_filesystem_02();

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_conceptual_example();
    // test_filesystem_01();
    // test_filesystem_02();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
