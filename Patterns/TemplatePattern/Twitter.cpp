// ===========================================================================
// Twitter.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Network.h"
#include "Twitter.h"

Twitter::Twitter(const std::string& username, const std::string& password)
    : Network()
{
    m_username = username;
    m_password = password;
}

bool Twitter::logIn(const std::string& username, const std::string& password) {
    std::cout << "Checking user's parameters" << std::endl;
    std::cout << "Name: " << m_username << std::endl;
    std::cout << "Password: ";
    for (unsigned int i = 0; i < m_password.length(); i++) {
        std::cout << "*";
    }

    simulateNetworkLatency();
    std::cout << std::endl << "LogIn success on Twitter" << std::endl;
    return true;
}

bool Twitter::sendData(const std::string& data) {

    bool messagePosted = true;
    if (messagePosted) {
        std::cout << "Message: '" << data << "' was posted on Twitter" << std::endl;
        return true;
    }
    else {
        return false;
    }
}

void Twitter::logOut() {
    std::cout << "User: '" << m_username << "' was logged out from Twitter" << std::endl;
}

void Twitter::simulateNetworkLatency() {
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
