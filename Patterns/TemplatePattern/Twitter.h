// ===========================================================================
// Twitter.h
// ===========================================================================

class Twitter : public SocialNetwork {
public:
    Twitter(const std::string& username, const std::string& password);

    bool logIn(const std::string& username, const std::string& password) override;
    bool sendData(const std::string& data) override;
    void logOut() override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
