// ===========================================================================
// PersonBuilderExample.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

void test_person_builder_example_01()
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

void test_person_builder_example_02()
{
    PersonBuilder builder{ Person::create("Sepp")
        .lives()
        .at("Kurfuerstendamm")
        .with_postcode("10709")
        .in("Berlin")
        .works()
        .with("Software Manufactur")
        .as_a("Consultant")
        .earning("100000") 
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
