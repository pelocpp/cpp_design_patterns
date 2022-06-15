// ===========================================================================
// PersonBuilder.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

PersonBuilder Person::create(std::string name) { return PersonBuilder{ name }; }

PersonBuilder& PersonBuilder::lives() { return *this; }

PersonBuilder& PersonBuilder::works() { return *this; }

PersonBuilder& PersonBuilder::with(std::string company_name) {
    person.m_company_name = company_name;
    return *this;
}

PersonBuilder& PersonBuilder::as_a(std::string position) {
    person.m_position = position;
    return *this;
}

PersonBuilder& PersonBuilder::earning(std::string annual_income) {
    person.m_annual_income = annual_income;
    return *this;
}

PersonBuilder& PersonBuilder::at(std::string street_address) {
    person.m_street_address = street_address;
    return *this;
}

PersonBuilder& PersonBuilder::with_postcode(std::string post_code) {
    person.m_post_code = post_code;
    return *this;
}

PersonBuilder& PersonBuilder::in(std::string city) {
    person.m_city = city;
    return *this;
}


// ===========================================================================
// End-of-File
// ===========================================================================
