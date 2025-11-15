// ===========================================================================
// NotificationSender.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

class SystemOperator
{
private:
    std::string m_name;
    std::string m_pager;
    std::string m_cellPhone;
    std::string m_email;

public:
    SystemOperator() : m_name{}, m_pager{}, m_cellPhone{}, m_email{} {}

    SystemOperator(std::string name, std::string email, std::string cellPhone, std::string pager)
        : m_name{ name }, m_pager{ pager }, m_cellPhone{ cellPhone }, m_email{ email } {}

    void setName(std::string name) { m_name = name; }
    void setPager(std::string pager) { m_pager = pager; }
    void setCellPhone(std::string cellPhone) { m_cellPhone = cellPhone; }
    void setEmail(std::string email) { m_email = email; }

    std::string getName() { return m_name; }
    std::string getPager() { return m_pager; }
    std::string getCellPhone() { return m_cellPhone; }
    std::string getEmail() { return m_email; }
};

class NotificationSenderBase
{
protected:
    SystemOperator m_operator;

public:
    NotificationSenderBase(const SystemOperator& systemOperator)
        : m_operator{ systemOperator } {}

protected:
    virtual std::string getNotificationHeader() = 0;
    virtual std::string getNotificationTrailer() = 0;
    virtual std::string getProtocolDetails() = 0;
    virtual void sendText(std::string) = 0;

public:
    void notify(std::string text)
    {
        std::string header{ getNotificationHeader() };
        sendText(header);

        sendText(text);

        std::string trailer{ getNotificationTrailer() };
        sendText(trailer);

        std::string tmp{ getProtocolDetails() };
        std::string details = 
            tmp + 
            std::string(" - Length of message: ") + 
            std::to_string(text.length());

        sendText(details);
    }
};

class MailNotificationSender : public NotificationSenderBase
{
public:
    MailNotificationSender(SystemOperator systemOperator) 
        : NotificationSenderBase{ systemOperator } {}

protected:
    virtual std::string getNotificationHeader() override
    {
        // SMTP: emtpy line between header and body
        std::string header = std::string("EMail Header: Using SMPT Protocol.");
        return header + std::string("\n");  
    }

    virtual std::string getNotificationTrailer() override
    {
        // SMTP: end of body: single line just containing a '.'
        std::string trailer = "\n.\n"; 
        return trailer + std::string("<End-of-EMail>") + std::string("\n");
    }

    virtual std::string getProtocolDetails() override
    {
        std::string sender = m_operator.getEmail();
        return std::string("Server: FROM <") + sender + std::string(">");
    }

    virtual void sendText(std::string text) override
    {
        std::cout << text;
    }
};

class SmsNotificationSender : public NotificationSenderBase
{
public:
    SmsNotificationSender(SystemOperator systemOperator)
        : NotificationSenderBase(systemOperator)
    {}

protected:
    virtual std::string getNotificationHeader() override
    {
        // SMS: emtpy line between header and body
        std::string header = std::string("SMS Header: Using Short Message Service Protocol.");
        return header + std::string("\n");
    }

    virtual std::string getNotificationTrailer() override
    {
        // SMS: insert single line for better readability
        std::string trailer = "\n";
        return trailer + std::string("<End-of-SMS>") + std::string("\n");
    }

    virtual std::string getProtocolDetails() override
    {
        std::string sender = m_operator.getCellPhone();
        return std::string("Server: Originator Address (OA) <") + sender + std::string(">");
    }

    virtual void sendText(std::string text) override
    {
        if (text.length() > 160) {
            throw std::invalid_argument("length of message too long");
        }

        // content of sms should be converted to 7-bit characters from the GSM character set 
        std::cout << text;
    }
};

class Message
{
private:
    std::shared_ptr<NotificationSenderBase> m_sender;

public:
    void setSender(std::shared_ptr<NotificationSenderBase> sender) { m_sender = sender; }

    void postMessage(std::string text)
    {
        m_sender->notify(text);
    }
};

void test_notification_sender()
{
    SystemOperator systemOperator 
    {
        "Super Operator",
        "system@operator.com",
        "0049151123456789",
        "465565456"
    };

    std::shared_ptr<NotificationSenderBase> sender1{
        std::make_shared<MailNotificationSender>(systemOperator) 
    };

    std::shared_ptr<NotificationSenderBase> sender2{
        std::make_shared<SmsNotificationSender>(systemOperator) 
    };

    Message message{};

    message.setSender(sender1);
    message.postMessage("This is a message being sent as Email ...");

    std::cout << std::endl << std::endl;

    message.setSender(sender2);
    message.postMessage("...and this message is sent as SMS");
}

// ===========================================================================
// End-of-File
// ===========================================================================
