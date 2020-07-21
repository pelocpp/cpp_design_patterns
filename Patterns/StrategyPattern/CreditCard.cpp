// ===========================================================================
// CreditCard.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "CreditCard.h"

/**
 * c'tor(s) / d'tor
 */
CreditCard::CreditCard() : m_number{ "" }, m_date{ "" }, m_cvv{ "" } {
    m_isValid = false;
    m_amount = 0;
}

CreditCard::CreditCard(std::string number, std::string date, std::string cvv) 
    : m_number{ number }, m_date{ date }, m_cvv{ cvv } {
    m_amount = 5'000;  // maximum balance per month
    m_isValid = false; // has to be set explicitely by 'setValid'
}

/**
 * public interface
 */
bool CreditCard::charge (int amount) {
    if (m_amount - amount >= 0) {
        m_amount -= amount;
        return true;
    }
    else {
        return false;
    }
}

void CreditCard::setValid(bool valid) {
    m_isValid = valid;
}

bool CreditCard::isValid() {
    return m_isValid;
}

// ===========================================================================
// End-of-File
// ===========================================================================
