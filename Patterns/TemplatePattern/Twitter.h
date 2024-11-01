// ===========================================================================
// Twitter.h
// ===========================================================================

class Twitter : public SocialNetwork
{
public:
    Twitter(const std::string& username, const std::string& password);

    virtual bool logIn() override;
    virtual bool sendData(const std::string& data) override;
    virtual void logOut() const override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
