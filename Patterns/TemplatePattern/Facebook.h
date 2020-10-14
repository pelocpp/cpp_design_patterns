// ===========================================================================
// Facebook.h
// ===========================================================================

class Facebook : public SocialNetwork {
public:
    Facebook(const std::string& username, const std::string& password);

    virtual bool logIn() override;
    virtual bool sendData(const std::string& data) override;
    virtual void logOut() override;

private:
    void simulateNetworkLatency();
};

// ===========================================================================
// End-of-File
// ===========================================================================
