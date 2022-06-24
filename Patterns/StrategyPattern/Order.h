// ===========================================================================
// Order.h
// ===========================================================================

class Order
{
public:
    Order();

    void processOrder(std::shared_ptr<PaymentStrategy> strategy);

    void addToTotalCost(int cost);
    int getTotalCost();
    bool isClosed();
    void setClosed();

private:
    int m_totalCost = 0;
    bool m_isClosed = false;
};

// ===========================================================================
// End-of-File
// ===========================================================================
