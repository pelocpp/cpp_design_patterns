// ===========================================================================
// PersonBuilder.cpp // Builder Pattern
// ===========================================================================

#include "PersonBuilder.h"

PersonBuilder::operator Person&& () {
    return std::move(m_person);
}

PersonBuilder& PersonBuilder::lives(const std::string& country) {
    m_person.m_country = country;
    return *this;
}

PersonBuilder& PersonBuilder::works(const std::string& sector) {
    m_person.m_sector = sector;
    return *this;
}

PersonBuilder& PersonBuilder::with(const std::string& company_name) {
    m_person.m_company_name = company_name;
    return *this;
}

PersonBuilder& PersonBuilder::as_a(const std::string& position) {
    m_person.m_position = position;
    return *this;
}

PersonBuilder& PersonBuilder::at(const std::string& street_address) {
    m_person.m_street_address = street_address;
    return *this;
}

PersonBuilder& PersonBuilder::with_postcode(const std::string& postal_code) {
    m_person.m_post_code = postal_code;
    return *this;
}

PersonBuilder& PersonBuilder::in(const std::string& city) {
    m_person.m_city = city;
    return *this;
}

// ===========================================================================
// End-of-File
// ===========================================================================
