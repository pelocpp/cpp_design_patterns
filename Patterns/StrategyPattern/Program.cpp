// ===========================================================================
// Program.cpp - Strategy Pattern
// ===========================================================================

// function prototypes
extern void test_conceptual_example();
extern void test_conceptual_example_modern();

extern void test_realworld_example();
extern void test_realworld_example_modern();

extern void test_ecommerce_app();

extern void test_static_strategy_example();
extern void test_dynamic_strategy_example();

int main()
{
    test_conceptual_example();
    test_conceptual_example_modern();

    test_realworld_example();
    test_realworld_example_modern();
    
    test_ecommerce_app();
    
    test_dynamic_strategy_example();
    test_static_strategy_example();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
