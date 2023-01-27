// ===========================================================================
// PersonBuilderExample.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

void test_person_builder_example_01()
{
    Person p{ Person::create("Jack")
        .lives("Great Britain")
        .at("17 Sloane Street")
        .with_postcode("SW1X 9NU")
        .in("London")
        .works("Information Technology")
        .with("Software Manufactur")
        .as_a("Consultant")
    };

    std::cout << p << std::endl;
}

void test_person_builder_example_02()
{
    PersonBuilder builder{ Person::create("Jack")
        .lives("Great Britain")
        .at("17 Sloane Street")
        .with_postcode("SW1X 9NU")
        .in("London")
        .works("Information Technology")
        .with("Software Manufactur")
        .as_a("Consultant")
    };

    Person p{ builder };

    std::cout << p << std::endl;
}

void test_person_builder_example()
{
    test_person_builder_example_01();
    test_person_builder_example_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
