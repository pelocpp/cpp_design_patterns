// ===========================================================================
// PayByCreditCard.h
// ===========================================================================

/**
 * Concrete strategy. Implements credit card payment method.
 */

class PayByCreditCard : public PaymentStrategy {

private:
    std::unique_ptr<CreditCard> m_card;

public:
    PayByCreditCard();
    ~PayByCreditCard() = default;

    virtual bool pay(int paymentAmount) override;
    virtual void collectPaymentDetails() override;

private:
    bool cardIsPresent();
};

// ===========================================================================
// End-of-File
// ===========================================================================
