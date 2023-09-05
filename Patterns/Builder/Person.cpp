// ===========================================================================
// Person.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

PersonBuilder Person::create(const std::string& name) {
    return PersonBuilder{ name };
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os 
        << person.m_name << std::endl
        << "  Lives at " << person.m_street_address
        << " with postcode " << person.m_post_code
        << " in " << person.m_city
        << " (" << person.m_country << ")" << std::endl
        << "  Work Area: Sector of " << person.m_sector
        << "  as a " << person.m_position
        << " for " << person.m_company_name;

    return os;
}

// ===========================================================================
// End-of-File
// ===========================================================================
