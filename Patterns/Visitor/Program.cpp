// ===========================================================================
// Program.cpp - Visitor Pattern
// ===========================================================================

// function prototypes
extern void test_conceptual_example_01();
extern void test_conceptual_example_02();

extern void test_motivation_example();
extern void test_onlineshop_example();
extern void test_bookstore_example();

extern void test_filesystem_example();
extern void test_filesystem_example_using_variant();

int main()
{
    test_conceptual_example_01();
    test_conceptual_example_02();

    test_motivation_example();
    test_bookstore_example();
    test_onlineshop_example();

    test_filesystem_example();
    test_filesystem_example_using_variant();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
