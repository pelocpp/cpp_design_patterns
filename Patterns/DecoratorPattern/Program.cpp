// ===========================================================================
// Program.cpp - Decorator Pattern
// ===========================================================================

// function prototypes
extern void test_conceptual_example();
extern void test_real_world_example();
extern void test_static_decoration();

int main()
{
    test_conceptual_example();
    test_real_world_example(); // using shapes
    test_static_decoration();  // same real-world example with templates
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
