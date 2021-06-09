// ===========================================================================
// ECommerceApp.cpp // Strategy Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "CreditCard.h"
#include "PaymentStrategy.h"
#include "PayByPayPal.h"
#include "PayByCreditCard.h"
#include "Order.h"

void test_ecommerce_app() {

    Order order;
    std::shared_ptr<PaymentStrategy> strategy = nullptr;

    std::map<int, int> priceOnProducts;
    priceOnProducts[1] = 2000;
    priceOnProducts[2] = 950;
    priceOnProducts[3] = 1200;
    priceOnProducts[4] = 750;

    while (!order.isClosed()) {

        std::string continueChoice;

        do {

            std::cout << "Please, select a product:" << std::endl;
            std::cout << "1 - Mother board" << std::endl;
            std::cout << "2 - CPU" << std::endl;
            std::cout << "3 - HDD" << std::endl;
            std::cout << "4 - Memory" << std::endl;
            std::cout << std::endl;

            int choice;
            std::cin >> choice;

            int cost = priceOnProducts.at(choice);

            std::cout << "Count: ";
            int count;
            std::cin >> count;

            order.setTotalCost(cost * count);

            std::cout << "Do you wish to continue selecting products? Y/N: ";
            std::cin >> continueChoice;

        } while (continueChoice == "Y" || continueChoice == "y");

        if (strategy == nullptr) {

            std::cout << "Please, select a payment method:" << std::endl;
            std::cout << "1 - PalPay" << std::endl;
            std::cout << "2 - Credit Card" << std::endl;
            std::cout << std::endl;

            std::string paymentMethod;
            std::cin >> paymentMethod;

            // application creates different strategies
            // based on input from user, application configuration, etc.
            if (paymentMethod == "1") {
                strategy = std::make_shared<PayByPayPal>();
            }
            else {
                strategy = std::make_shared <PayByCreditCard>();
            }

            // Order object delegates gathering payment data to strategy object,
            // since only strategies know what data they need to process a payment.
            order.processOrder(strategy);

            std::cout
                << "Pay " << order.getTotalCost()
                << " units or Continue shopping? P/C: "
                << std::endl;

            std::string proceed;
            std::cin >> proceed;

            if (proceed == "p" || proceed == "P") {

                // strategy finally handles the payment
                if (strategy->pay(order.getTotalCost())) {
                    std::cout << "Payment has been successful." << std::endl;
                }
                else {
                    std::cout << "FAIL! Please, check your data." << std::endl;
                }

                order.setClosed();
            }
        }
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
