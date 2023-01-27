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
    Person m_person;

public:
    PersonBuilder(const std::string& name) : m_person{ name } {}

    operator Person&& (); // type conversion operator

    PersonBuilder& lives(const std::string& country);
    PersonBuilder& at(const std::string& street_address);
    PersonBuilder& with_postcode(const std::string& postal_code);
    PersonBuilder& in(const std::string& city);
    PersonBuilder& works(const std::string& sector);
    PersonBuilder& with(const std::string& company_name);
    PersonBuilder& as_a(const std::string& position);
};

// ===========================================================================
// End-of-File
// ===========================================================================
