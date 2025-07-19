// ===========================================================================
// ChatRoom.cpp // Mediator
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace ChatRoomMediatorPattern
{
    class ChatRoomBase                        // MediatorBase
    {
    public:
        virtual void broadcast(const std::string& from, const std::string& msg) = 0;                        // notify
        virtual void message(const std::string& from, const std::string& to, const std::string& msg) = 0;   // reactOn
    };

    class PersonBase                          // ColleagueBase
    {
    protected:
        std::weak_ptr<ChatRoomBase> m_room;

    public:
        PersonBase() {};
    };

    // -----------------------------------------------------------------------

    class Person : public PersonBase          // Concrete Colleague
    {
    private:
        std::string              m_name;
        std::vector<std::string> m_log;

    public:
        // c'tors
        Person(const std::string& name);

        // getter/setter
        void setRoom(const std::shared_ptr<ChatRoomBase>& sp);
        const std::string& getName() const;

        void say(const std::string& msg) const;
        void postMessage(const std::string& to, const std::string& msg) const;
        void receive(const std::string& from, const std::string& msg);
    };

    // -----------------------------------------------------------------------

    // Concrete Mediator
    class ChatRoom : public ChatRoomBase, public std::enable_shared_from_this<ChatRoom>
    {
    private:
        std::vector<std::shared_ptr<Person>> m_people;

    public:
        void broadcast(const std::string& from, const std::string& msg) override;
        void message(const std::string& from, const std::string& to, const std::string& msg) override;

        void join(const std::shared_ptr<Person>& person);
    };

    // ===========================================================================
    // implementation class Person

    Person::Person(const std::string& name) 
        : PersonBase{}, m_name{ name } 
    {}

    void Person::setRoom(const std::shared_ptr<ChatRoomBase>& room) {
        m_room = room;
    }

    const std::string& Person::getName() const {
        return m_name;
    }

    void Person::say(const std::string& msg) const {

        std::shared_ptr<ChatRoomBase> room{ m_room.lock() };
        if (room != nullptr) {
            room->broadcast(m_name, msg);
        }
    }

    void Person::postMessage(const std::string& to, const std::string& msg) const {

        std::shared_ptr<ChatRoomBase> room{ m_room.lock() };
        if (room != nullptr) {
            room->message(m_name, to, msg);
        }
    }

    void Person::receive(const std::string& from, const std::string& msg) {
        std::string s{ from + ": \"" + msg + "\"" };
        std::cout << "[" << m_name << "'s chat session] " << s << std::endl;
        m_log.emplace_back(s);
    }

    // ===========================================================================
    // implementation class ChatRoom

    void ChatRoom::join(const std::shared_ptr<Person>& person) {
        // add person to chat room
        person->setRoom(shared_from_this());
        m_people.push_back(person);

        // inform all chat room members - including the current one - about a new member
        std::string join_msg{ person->getName() + " joins the chat" };
        broadcast("my_room", join_msg);
    }

    void ChatRoom::broadcast(const std::string& from, const std::string& msg) {
        for (const auto& person : m_people) {
            // send message to all chat room members - excluding the sender
            if (person->getName() != from) {
                person->receive(from, msg);
            }
        }
    }

    void ChatRoom::message(const std::string& from, const std::string& to, const std::string& msg) {

        std::vector<std::shared_ptr<Person>>::iterator target{ 
            std::find_if(
                m_people.begin(),
                m_people.end(),
                [&](const auto& person) {
                    return person->getName() == to;
                }
            ) 
        };

        if (target != m_people.end()) {
            (*target)->receive(from, msg);
        }
    }
};

void test_chatroom_example()
{
    using namespace ChatRoomMediatorPattern;

    // colleagues
    std::shared_ptr<Person> john{ std::make_shared<Person>("John") };
    std::shared_ptr<Person> jane{ std::make_shared<Person>("Jane") };

    // mediator
    std::shared_ptr<ChatRoom> room{ std::make_shared<ChatRoom>() };

    // join colleagues with mediator
    room->join(john);
    room->join(jane);

    // communicate via mediator
    john->say("Hi anybody ...");
    jane->say("Oh, hello John");

    // join one more colleague
    std::shared_ptr<Person> simon{ std::make_shared<Person>("Simon") };

    room->join(simon);

    simon->say("Hi everyone!");

    jane->postMessage("Simon", "Glad you found us, simon!");
}

// ===========================================================================
// End-of-File
// ===========================================================================

