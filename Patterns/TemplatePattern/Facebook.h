// ===========================================================================
// Facebook.h
// ===========================================================================

class Facebook : public SocialNetwork
{
public:
    Facebook(const std::string& username, const std::string& password);

    bool logIn() override;
    bool sendData(const std::string& data) override;
    void logOut() const override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
