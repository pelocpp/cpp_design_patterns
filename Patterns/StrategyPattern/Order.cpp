// ===========================================================================
// Order.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "PaymentStrategy.h"
#include "Order.h"

/**
 * class Order:
 * Doesn't know the concrete payment method (strategy) the user has choosen.
 * It uses a strategy interface to delegate collecting payment data
 * to strategy object.
 *
 * In this example class Order has the role of the so called 'Context':
 * The Context maintains a reference to one of the Strategy objects.
 */
Order::Order() : m_totalCost{ }, m_isClosed{ false } {}

/**
 * public interface
 */
void Order::processOrder(std::shared_ptr<PaymentStrategy> strategy) {

    strategy->collectPaymentDetails();
}

void Order::setTotalCost(int cost) {
    m_totalCost += cost;
}

int Order::getTotalCost() {
    return m_totalCost;
}

bool Order::isClosed() {
    return m_isClosed;
}

void Order::setClosed() {
    m_isClosed = true;
}

// ===========================================================================
// End-of-File
// ===========================================================================
