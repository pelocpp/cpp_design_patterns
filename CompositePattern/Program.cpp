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

//HIER WEITER:
//https://github.com/achimoraites/DesignPatterns/blob/master/CompositePattern/FileSystem/src/ui/FileSystem.java

// function prototypes
void test_conceptual_example();
void test_filesystem_01();
void test_filesystem_10();

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_filesystem_10();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
