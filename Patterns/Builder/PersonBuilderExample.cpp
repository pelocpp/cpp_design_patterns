// ===========================================================================
// PersonBuilderExample.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

void test_person_builder_example()
{
    Person p = Person::create("Hans")
        .lives()
        .at("Kurfuerstendamm")
        .with_postcode("10709")
        .in("Berlin")
        .works()
        .with("Software Manufactur")
        .as_a("Consultant")
        .earning("100000");

    std::cout << p << std::endl;
}


// ===========================================================================
// End-of-File
// ===========================================================================
