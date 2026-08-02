// ===========================================================================
// Program.cpp - Prototype Pattern
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
extern void test_conceptual_example_new_delete();
extern void test_conceptual_example_unique_ptr();
extern void test_conceptual_example_02();

extern void test_prototype_pattern_chess_01();
extern void test_prototype_pattern_chess_02();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_conceptual_example_new_delete();
    test_conceptual_example_unique_ptr();
    //test_conceptual_example_02();

    //test_prototype_pattern_chess_01();
    //test_prototype_pattern_chess_02();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
