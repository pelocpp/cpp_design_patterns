// ===========================================================================
// Facebook.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "SocialNetwork.h"
#include "Facebook.h"

Facebook::Facebook(const std::string& username, const std::string& password)
    : SocialNetwork(username, password) {}

bool Facebook::logIn() {
    std::cout << "Checking user's parameters" << std::endl;
    std::cout << "Name: " << m_username << std::endl;
    std::cout << "Password: ";
    for (unsigned int i = 0; i < m_password.length(); i++) {
        std::cout << "*";
    }

    simulateNetworkLatency();
    std::cout << std::endl << "LogIn success on Facebook" << std::endl;
    return true;
}

bool Facebook::sendData(const std::string& data) {

    bool messagePosted = true;
    if (messagePosted) {
        std::cout << "Message: '" << data << "' was posted on Facebook" << std::endl;
        return true;
    }
    else {
        return false;
    }
}

void Facebook::logOut() {
    std::cout << "User: '" << m_username << "' was logged out from Facebook" << std::endl;
}

void Facebook::simulateNetworkLatency() {
    int i = 0;
    std::cout << std::endl;
    while (i < 5) {
        std::cout << '.';
        std::this_thread::sleep_for(std::chrono::seconds(1));
        i++;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
