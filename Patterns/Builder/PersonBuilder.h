// ===========================================================================
// PersonBuilder.h // Builder Pattern
// ===========================================================================

#pragma once

#include <iostream>
#include <string>

#include "Person.h"

class PersonBuilder
{
private:
    Person person;

public:
    PersonBuilder(const std::string& name) : person{ name } {}

    operator Person() { return std::move(person); }

    PersonBuilder& lives();
    PersonBuilder& at(std::string street_address);
    PersonBuilder& with_postcode(std::string post_code);
    PersonBuilder& in(std::string city);
    PersonBuilder& works();
    PersonBuilder& with(std::string company_name);
    PersonBuilder& as_a(std::string position);
    PersonBuilder& earning(std::string annual_income);
};

// ===========================================================================
// End-of-File
// ===========================================================================
