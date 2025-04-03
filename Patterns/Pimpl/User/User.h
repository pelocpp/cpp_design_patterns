// ===========================================================================
// User.h
// ===========================================================================

#pragma once

// https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/

/* |INTERFACE| User.h file */

#include <memory>
#include <string>

class User
{
public:
	// c'tor / d'tor
	User(std::string&& name);
	~User();

	// assignment operator and copy constructor
	// note: assignment operator uses swap idiom
	User(const User& other);
	User& operator=(User rhs);

	// getter / setter
	int getAge();
	void setAge(int);

private:
	// internal implementation class
	class UserImpl;

	// pointer to the internal implementation
	std::unique_ptr<UserImpl> m_pimpl;
};

// ===========================================================================
// End-of-File
// ===========================================================================
