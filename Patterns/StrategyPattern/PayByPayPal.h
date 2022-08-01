// ===========================================================================
// PayByPayPal.h
// ===========================================================================

/**
 * Concrete strategy. Implements PayPal payment method.
 */

class PayByPayPal : public PaymentStrategy
{
private:
    std::string m_email;
    std::string m_password;
    bool m_isSignedIn;

    std::map<std::string, std::string> m_paypalDataBase;

public:
    PayByPayPal();
    ~PayByPayPal();

    virtual bool pay(int paymentAmount) override;
    virtual void collectPaymentDetails() override;

private:
    bool verify();
};

// ===========================================================================
// End-of-File
// ===========================================================================
