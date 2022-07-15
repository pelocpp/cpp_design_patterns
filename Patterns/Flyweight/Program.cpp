// ===========================================================================
// Program.cpp // Flyweight Pattern
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
void test_conceptual_example();
void test_paint_brush();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_conceptual_example();
    test_paint_brush();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
