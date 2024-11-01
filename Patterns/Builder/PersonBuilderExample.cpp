// ===========================================================================
// PersonBuilderExample.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

static void test_person_builder_example_01()
{
    // detailed notation

    PersonBuilder builder{ Person::create("Jack") };

    builder
        .lives("Great Britain")
        .at("17 Sloane Street")
        .with_postcode("SW1X 9NU")
        .in("London")
        .works("Information Technology")
        .with("Software Manufactur")
        .as_a("Consultant");

    Person p{ builder };

    std::cout << p << std::endl;
}

static void test_person_builder_example_02()
{
    // short notation

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


static void test_person_builder_example_03()
{
    // very short notation

    Person p{ 
        Person::create("Jack")
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

void test_person_builder_example()
{
    test_person_builder_example_01();
    test_person_builder_example_02();
    test_person_builder_example_03();
}

// ===========================================================================
// End-of-File
// ===========================================================================
