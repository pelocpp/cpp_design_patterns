// ===========================================================================
// Authentication.cpp // Chain of Responsibility
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ChainofResponsibilityExample
{
    class Authentication
    {
    protected:
        std::unique_ptr<Authentication> m_next;

    public:
        // c'tor(s)
        Authentication() : m_next{ nullptr } {}

        virtual bool authenticate() = 0;   // handleRequest

        void nextAuthentication(std::unique_ptr<Authentication>& nextAuth) {  // setSuccessor
            m_next = std::move(nextAuth);
        }
    };

    class AuthenticateUserName : public Authentication
    {
    private:
        std::string m_name;

    public:
        // c'tor(s)
        AuthenticateUserName(std::string name) : m_name{ name } {}

        bool authenticate() override {

            if (!is_valid_user_name()) {
                std::cout << "Invalid user name" << std::endl;
                return false;
            }
            else if (m_next) {
                return m_next->authenticate();
            } 
            else 
                return true;
        }

    private:
        // helper methods
        bool is_valid_user_name() {
            std::cout << "Authentication of User Name succeeded!" << std::endl;
            return true;
        }
    };

    class AuthenticatePassword : public Authentication
    {
    private:
        std::string m_password;

    public:
        // c'tor(s)
        AuthenticatePassword(std::string password) : m_password{ password } {}

        bool authenticate() override {

            if (!is_valid_password()) {
                std::cout << "Invalid password" << std::endl;
                return false;
            }
            else if (m_next) {
                return m_next->authenticate();
            }
            else 
                return true;
        }

    private:
        // helper methods
        bool is_valid_password() {
            std::cout << "Authentication of Password succeeded!" << std::endl;
            return true;
        }
    };
}

void test_authentication_example()
{
    using namespace ChainofResponsibilityExample;

    std::unique_ptr<Authentication> auth1{ 
        new AuthenticateUserName{"John"} 
    };

    std::unique_ptr<Authentication> auth2{
        new AuthenticatePassword{"12345678"} 
    };

    auth1->nextAuthentication(auth2);

    bool result{ auth1->authenticate() };

    if (result) {
        std::cout << "Authentication succeeded!" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
