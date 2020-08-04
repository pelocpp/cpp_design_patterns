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
void test_conceptual_example_01();
void test_conceptual_example_02();

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_conceptual_example_01();
    test_conceptual_example_02();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
