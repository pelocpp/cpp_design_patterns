// ===========================================================================
// Program.cpp - Composite Pattern
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

// function prototypes
extern void test_conceptual_example_01();
extern void test_conceptual_example_02();

extern void test_shapes();

extern void test_filesystem_01_beginners();
extern void test_filesystem_02_advanced();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //test_filesystem_01_beginners();
    //test_filesystem_02_advanced();

    //test_shapes();

    //test_filesystem_01_beginners();
    test_filesystem_02_advanced();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
