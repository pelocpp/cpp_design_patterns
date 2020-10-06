// ===========================================================================
// Network.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() : m_username{ "" }, m_password{ "" } {}

bool SocialNetwork::post(const std::string& message) {

    // authenticate before posting:
    // every network uses a different authentication method
    if (logIn(m_username, m_password)) {
        
        // send data
        bool result = sendData(message);
        logOut();
        return result;
    }

    return false;
}

// ===========================================================================
// End-of-File
// ===========================================================================
