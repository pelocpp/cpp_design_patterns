// ===========================================================================
// SocialNetworking.cpp // Template Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "SocialNetwork.h"
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

    // create proper network object
    std::unique_ptr<SocialNetwork> socialNetwork;
    if (choice == 1) {
        socialNetwork = std::make_unique<Facebook>(userName, password);
    }
    else if (choice == 2) {
        socialNetwork = std::make_unique<Twitter>(userName, password);
    }
    else {
        std::cout << "Wrong Choice!" << std::endl;
    }

    // send the message to network object
    if (socialNetwork != nullptr) {
        socialNetwork->post(message);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
