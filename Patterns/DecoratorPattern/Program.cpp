// ===========================================================================
// Program.cpp - Decorator Pattern
// ===========================================================================

// function prototypes
extern void test_conceptual_example();
extern void test_real_world_example();
extern void test_static_decoration();

int main()
{
    // conceptual example
    test_conceptual_example();

    // real-world example (shapes)
    test_real_world_example();

    // same real-world example with templates
    test_static_decoration();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
