// ===========================================================================
// Twitter.h
// ===========================================================================

class Twitter : public SocialNetwork {
public:
    Twitter(const std::string& username, const std::string& password);

    virtual bool logIn(const std::string& username, const std::string& password) override;
    virtual bool sendData(const std::string& data) override;
    virtual void logOut() override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
