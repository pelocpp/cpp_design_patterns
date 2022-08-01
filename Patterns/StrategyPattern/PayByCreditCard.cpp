// ===========================================================================
// PayByCreditCard.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "PaymentStrategy.h"
#include "CreditCard.h"
#include "PayByCreditCard.h"

/**
 * c'tor(s) / d'tor
 */
PayByCreditCard::PayByCreditCard()
{
    m_card = nullptr;
}

/**
 * collect customer's data
 */
void PayByCreditCard::collectPaymentDetails()
{

    std::cout << "Enter the card number: ";
    std::string number;
    std::cin >> number;

    std::cout << "Enter the card expiration date 'mm/yy': ";
    std::string date;
    std::cin >> date;

    std::cout << "Enter the CVV code: ";
    std::string cvv;
    std::cin >> cvv;

    // validate credit card number...

    m_card = std::make_unique<CreditCard>(number, date, cvv);
    m_card->setValid(true);
}

/**
 * handle payment process:
 * after card validation we can charge customer's credit card
 */
bool PayByCreditCard::pay(int paymentAmount)
{

    if (cardIsPresent()) {
        std::cout << "Paying " << paymentAmount << " using Credit Card" << std::endl;
        bool result = m_card->charge(paymentAmount);
        return result;
    }
    else {
        return false;
    }
}

bool PayByCreditCard::cardIsPresent()
{
    return m_card->isValid();
}

// ===========================================================================
// End-of-File
// ===========================================================================
