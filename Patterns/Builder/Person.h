// ===========================================================================
// Person.h // Builder Pattern
// ===========================================================================

#pragma once

#include <iostream>
#include <string>

class PersonBuilder;

class Person
{
friend class PersonBuilder;
friend std::ostream& operator<<(std::ostream& os, const Person& obj);

private:
    // personal details
    std::string m_name;     
    std::string m_street_address;
    std::string m_post_code;
    std::string m_city;

    // employment details
    std::string m_company_name;
    std::string m_position;
    std::string m_annual_income;

    Person(std::string name) : m_name{ name } {}

public:
    static PersonBuilder create(const std::string& name);
};

// ===========================================================================
// End-of-File
// ===========================================================================
