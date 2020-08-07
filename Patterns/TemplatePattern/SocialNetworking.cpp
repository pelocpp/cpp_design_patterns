// ===========================================================================
// SocialNetworking.cpp // Template Pattern
// ===========================================================================

#include <iostream>
#include <string>

#include "Network.h"
#include "Facebook.h"
#include "Twitter.h"

void test_social_networking() {

    std::cout << "Input user name: ";
    std::string userName;
    std::cin >> userName;

    std::cout << "Input password: ";
    std::string password;
    std::cin >> password;

    std::cout << "Input message: ";
    std::string message;
    std::cin >> message;

    std::cout << "Choose social network for posting message:" << std::endl;
    std::cout << "1 - Facebook" << std::endl;
    std::cout << "2 - Twitter" << std::endl;
    std::cout << std::endl;

    int choice;
    std::cin >> choice;

    // create proper network object and send the message
    Network* network = nullptr;
    if (choice == 1) {
        network = new Facebook(userName, password);
    }
    else if (choice == 2) {
        network = new Twitter(userName, password);
    }
    else {
        std::cout << "Wrong Choice!" << std::endl;
    }

    if (network != nullptr) {
        network->post(message);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
