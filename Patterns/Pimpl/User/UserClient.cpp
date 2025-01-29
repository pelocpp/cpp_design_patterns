// ===========================================================================
// UserClient.cpp // Opaque Pointer
// ===========================================================================

#include "User.h"

#include <print>

void test_user()
{
    User hans{ "Hans" };
    int age{ hans.getAge() };
    std::println("Age of Hans: {}", age);

    User copyOfHans{ hans };

    hans.setAge(age + 1);

    std::println("Age of Copy of Hans: {}", copyOfHans.getAge());
    std::println("Age of Hans: {}", hans.getAge());
}

// ===========================================================================
// End-of-File
// ===========================================================================
