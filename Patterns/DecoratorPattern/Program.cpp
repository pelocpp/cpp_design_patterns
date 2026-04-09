// ===========================================================================
// Program.cpp // Decorator Pattern
// ===========================================================================

// function prototypes
extern void test_conceptual_example_01();
extern void test_conceptual_example_02();
extern void test_conceptual_example_03();

extern void test_dynamic_decoration_00();
extern void test_dynamic_decoration_01();
extern void test_dynamic_decoration_02();
extern void test_dynamic_decoration_03();

extern void test_static_decoration_01();

int main()
{
    // conceptual example
    test_conceptual_example_01();
    test_conceptual_example_02();
    test_conceptual_example_03();

    // real-world example (shapes)
    test_dynamic_decoration_00();
    test_dynamic_decoration_01();
    test_dynamic_decoration_02();
    test_dynamic_decoration_03();

    // same real-world example with templates
    test_static_decoration_01();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
