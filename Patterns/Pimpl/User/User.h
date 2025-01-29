// ===========================================================================
// User.h
// ===========================================================================

// https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/

#pragma once

/* |INTERFACE| User.h file */

#pragma once

#include <memory>
#include <string>

class User
{
public:
	// c'tor / d'tor
	User(std::string name);
	~User();

	// assignment operator and copy constructor
	// note: copy constructor uses swao idiom
	User(const User& other);
	User& operator=(User rhs);

	// getter / setter
	int getAge();
	void setAge(int);

private:
	// internal implementation class
	class Impl;

	// pointer to the internal implementation
	std::unique_ptr<Impl> m_pimpl;
};

// ===========================================================================
// End-of-File
// ===========================================================================
