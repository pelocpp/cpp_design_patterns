// ===========================================================================
// PaymentStrategy.h
// ===========================================================================

/**
 * common interface for all strategies
 */
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() {};
    virtual bool pay(int paymentAmount) = 0;
    virtual void collectPaymentDetails() = 0;
};

// ===========================================================================
// End-of-File
// ===========================================================================
