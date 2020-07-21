// ===========================================================================
// PayByCreditCard.h
// ===========================================================================

/**
 * Concrete strategy. Implements credit card payment method.
 */

class PayByCreditCard : public PaymentStrategy {

private:
    CreditCard* m_card;

public:
    PayByCreditCard();
    ~PayByCreditCard();

    bool pay(int paymentAmount) override;
    void collectPaymentDetails() override;

private:
    bool cardIsPresent();
};

// ===========================================================================
// End-of-File
// ===========================================================================
