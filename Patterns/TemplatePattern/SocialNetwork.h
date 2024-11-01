// ===========================================================================
// SocialNetwork.h
// ===========================================================================

class SocialNetwork
{
public:
    SocialNetwork(const std::string& username, const std::string& password);

    /**
     * The template method defines the skeleton of an algorithm:
     * "Publish the data to whatever network"
     */
    bool post(const std::string& message);

    virtual bool logIn() = 0;
    virtual bool sendData(const std::string& data) = 0;
    virtual void logOut() const = 0;

protected:
    std::string m_username;
    std::string m_password;
};

// ===========================================================================
// End-of-File
// ===========================================================================
