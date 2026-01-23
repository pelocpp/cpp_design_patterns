// ===========================================================================
// CreditCard.h
// ===========================================================================

/**
 * Dummy credit card class
 */

class CreditCard
{
private:
    bool m_isValid;
    int m_amount;
    std::string m_number;
    std::string m_date;
    std::string m_cvv;

public:
    // c'tors
    CreditCard();
    CreditCard(const std::string& number, const std::string& date, const std::string& cvv);

    // public interface
    bool charge(int amount);
    void setValid(bool valid);
    bool isValid();
};

// ===========================================================================
// End-of-File
// ===========================================================================
