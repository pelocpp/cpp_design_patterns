// ===========================================================================
// PayByPayPal.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <map>

#include "PaymentStrategy.h"
#include "PayByPayPal.h"

/**
 * c'tor(s) / d'tor
 */
PayByPayPal::PayByPayPal()
{
    m_paypalDataBase = 
    {
        { "secret", "hans@web.de" },
        { "peter", "peter@web.de" },
        { "geheim", "sepp@web.de" },
        { "12345678", "georg@web.de" }
    };
}

PayByPayPal::~PayByPayPal() {}

/**
 * collect customer's data
 */
void PayByPayPal::collectPaymentDetails()
{
    while (!m_isSignedIn) {
        std::cout << "Enter the user's email address: ";
        std::cin >> m_email;
        std::cout << "Enter the password: ";
        std::cin >> m_password;
        if (verify()) {
            std::cout << "Data verification has been successful." << std::endl;
        }
        else {
            std::cout << "Wrong email or password!" << std::endl;
        }
    }
}

/**
 * handle payment process
 */
bool PayByPayPal::pay(int paymentAmount)
{

    if (m_isSignedIn) {
        std::cout << "Paying " << paymentAmount << " using PayPal.";
        return true;
    }
    else {
        return false;
    }
}

/**
 * private helper methods
 */
bool PayByPayPal::verify()
{

    m_isSignedIn = (m_email == m_paypalDataBase[m_password]);
    return m_isSignedIn;
}

// ===========================================================================
// End-of-File
// ===========================================================================
