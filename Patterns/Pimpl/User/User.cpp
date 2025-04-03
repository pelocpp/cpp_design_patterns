// ===========================================================================
// User.cpp
// ===========================================================================

/* |IMPLEMENTATION| User.cpp file */

#include "User.h"

#include <print>

class User::UserImpl
{
public:
	std::string m_name;
    int         m_age; 

public:
	UserImpl(std::string&& name)
		: m_name{ std::move(name) }, m_age{ 30 }
	{}
	
	~UserImpl() {}

	void welcomeMessage() const
	{
		std::println("Welcome, {}", m_name);
	}
};

// constructor connected with our Impl structure
User::User(std::string&& name) 
	: m_pimpl{ std::make_unique<UserImpl>(std::move(name)) }
{
	m_pimpl->welcomeMessage();
}

// destructor
User::~User() = default;

// assignment operator and copy constructor
User::User(const User& other) 
	: m_pimpl{ new UserImpl{ *other.m_pimpl } }
{}

User& User::operator=(User rhs)
{
	std::swap(m_pimpl, rhs.m_pimpl);
	return *this;
}

// getter and setter
int User::getAge()
{
	return m_pimpl->m_age;
}

void User::setAge(int age)
{
	m_pimpl->m_age = age;
	std::println("Age set to {}", m_pimpl->m_age);
}

// ===========================================================================
// End-of-File
// ===========================================================================
