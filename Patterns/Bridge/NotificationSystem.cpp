// ===========================================================================
// NotificationSystem.cpp // Bridge Pattern
// ===========================================================================

#include <memory>
#include <print>

/**
 *  Real World Example: Notification System
 */

namespace RealWorldExample_Bridge_Pattern_NotificationSystem {

    // ===========================================================================
    // Kind of Message: Alert, Reminder, Marketing Message

    class Sender {
    public:
        virtual ~Sender() = default;

        virtual void send(const std::string& text) = 0;
    };

    class EmailSender : public Sender {
    public:
        void send(const std::string& text) override {
            std::println("Email: {}", text);
        }
    };

    class SmsSender : public Sender {
    public:
        void send(const std::string& text) override {
            std::println("SMS: {}", text);
        }
    };

    // ===========================================================================
    // Kind of Delivery: Email, SMS, Push

    // abtraction
    class Notification
    {
    protected:
        Sender& sender;

    public:
        virtual ~Notification() = default;

        Notification(Sender& sender) : sender{ sender } {}
        virtual void notify() = 0;
    };

    class Alert : public Notification {
    public:
        using Notification::Notification;

        void notify() override {
            sender.send("ALERT!");
        }
    };

    class Reminder : public Notification {
    public:
        using Notification::Notification;

        void notify() override {
            sender.send("Don't forget!");
        }
    };

    static void clientCode(Notification& notification) {
        // ...
        notification.notify();
        // ...
    }
}

void test_real_word_example_notification()
{
    using namespace RealWorldExample_Bridge_Pattern_NotificationSystem;

    EmailSender email;
    Alert alert{ email };
    clientCode(alert);

    SmsSender sms;
    Reminder reminder{ sms };
    clientCode(reminder);
}

// ===========================================================================
// End-of-File
// ===========================================================================
