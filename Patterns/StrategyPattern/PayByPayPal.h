// ===========================================================================
// PayByPayPal.h
// ===========================================================================

/**
 * Concrete strategy. Implements PayPal payment method.
 */

class PayByPayPal : public PaymentStrategy {

private:
    std::string m_email;
    std::string m_password;
    bool m_isSignedIn;

    std::map<std::string, std::string> m_paypal_DataBase;

public:
    PayByPayPal();

    bool pay(int paymentAmount) override;
    void collectPaymentDetails() override;

private:
    bool verify();
};

// ===========================================================================
// End-of-File
// ===========================================================================
