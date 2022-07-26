// ===========================================================================
// Network.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "SocialNetwork.h"

SocialNetwork::SocialNetwork(const std::string& username, const std::string& password) 
    : m_username{ username }, m_password{ password } {}

bool SocialNetwork::post(const std::string& message)
{
    // authenticate before posting:
    // every network uses a different authentication method
    if (logIn()) {
        
        // send data
        bool result{ sendData(message) };
        logOut();
        return result;
    }

    return false;
}

// ===========================================================================
// End-of-File
// ===========================================================================
