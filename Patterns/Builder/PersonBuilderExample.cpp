// ===========================================================================
// PersonBuilderExample.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

void test_person_builder_example()
{
    Person p = Person::create("John")
        .lives()
        .at("123 London Road")
        .with_postcode("SW1 1GB")
        .in("London")
        .works()
        .with("PragmaSoft")
        .as_a("Consultant")
        .earning("10e6");

    std::cout << p << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
