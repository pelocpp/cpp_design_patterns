// ===========================================================================
// Facebook.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "Network.h"
#include "Facebook.h"

// TODO Basisklassen Konstruktor aufrufen ....
Facebook::Facebook() {

}

bool Facebook::logIn(const std::string& username, const std::string& password) {
    std::cout << "\nChecking user's parameters";
    std::cout << "Name: " << m_username;
    std::cout << "Password: ";
    for (unsigned int i = 0; i < m_password.length(); i++) {
        std::cout << "*";
    }

    simulateNetworkLatency();
    std::cout << "\n\nLogIn success on Facebook";
    return true;
}

bool Facebook::sendData(const std::string& data) {

    bool messagePosted = true;
    if (messagePosted) {
        std::cout << "Message: '" << data << "' was posted on Facebook";
        return true;
    }
    else {
        return false;
    }
}

void Facebook::logOut() {
    std::cout << "User: '" << m_username << "' was logged out from Facebook";
}

void Facebook::simulateNetworkLatency() {

}

// ===========================================================================
// End-of-File
// ===========================================================================
