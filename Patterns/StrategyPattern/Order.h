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
    int m_totalCost;
    bool m_isClosed;
};

// ===========================================================================
// End-of-File
// ===========================================================================
