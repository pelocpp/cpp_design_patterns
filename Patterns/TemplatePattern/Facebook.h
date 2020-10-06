// ===========================================================================
// Facebook.h
// ===========================================================================

class Facebook : public SocialNetwork {
public:
    Facebook(const std::string& username, const std::string& password);

    bool logIn(const std::string& username, const std::string& password) override;
    bool sendData(const std::string& data) override;
    void logOut() override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
