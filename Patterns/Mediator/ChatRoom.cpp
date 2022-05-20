// ===========================================================================
// ChatRoom.cpp // Mediator
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

namespace ChatRoomMediatorPattern
{
    // abstract Mediator // MediatorBase
    class ChatRoom 
    {
    public:
        virtual void broadcast(std::string from, std::string msg) = 0;                 // notify
        virtual void message(std::string from, std::string to, std::string msg) = 0;   // reactOn
    };

    class PersonBase {
    protected:
        std::weak_ptr<ChatRoom> m_room;  // mediator

    public:
        PersonBase() = default;
    };

    // concrete Collegue
    class Person : public PersonBase
    {
    private:
        std::string               m_name;
        std::vector<std::string>  m_log;

    public:
        // c'tors
        Person(std::string name);

        // getter/setter
        void setRoom(const std::shared_ptr<ChatRoom>& sp);
        const std::string& getName() const;

        void say(std::string msg) const;
        void postMessage(const std::string& to, const std::string& msg) const;
        void receive(const std::string& from, const std::string& msg);
    };

    // concrete Mediator
    class GoogleChat : public ChatRoom, public std::enable_shared_from_this<GoogleChat>
    {
    private:
        std::vector<std::shared_ptr<Person>> m_people;

    public:
        virtual void broadcast(std::string from, std::string msg) override;
        virtual void message(std::string from, std::string to, std::string msg) override;

        void join(const std::shared_ptr<Person>& person);
    };

    // ===========================================================================
    // implementation class Person

    Person::Person(std::string name) : PersonBase{}, m_name(name) {}

    void Person::setRoom(const std::shared_ptr<ChatRoom>& sp) { m_room = sp; }

    const std::string& Person::getName() const { return m_name; }

    void Person::say(std::string msg) const {

        if (std::shared_ptr<ChatRoom> room; (room = m_room.lock()) != nullptr) {
            room->broadcast(m_name, msg);
        }
    }

    void Person::postMessage(const std::string& to, const std::string& msg) const {

        if (std::shared_ptr<ChatRoom> room; (room = m_room.lock()) != nullptr) {
            room->message(m_name, to, msg);
        }
    }

    void Person::receive(const std::string& from, const std::string& msg) {
        std::string s{ from + ": \"" + msg + "\"" };
        std::cout << "[" << m_name << "'s chat session]" << s << "\n";
        m_log.emplace_back(s);
    }

    // ===========================================================================
    // implementation class GoogleChat

    void GoogleChat::join(const std::shared_ptr<Person>& person) {
        std::string join_msg = person->getName() + " joins the chat";
        broadcast("room", join_msg);
        person->setRoom(shared_from_this());
        m_people.push_back(person);
    }

    void GoogleChat::broadcast(std::string from, std::string msg) {
        for (auto& person : m_people) {
            if (person->getName() != from)
                person->receive(from, msg);
        }
    }

    void GoogleChat::message(std::string from, std::string to, std::string msg) {
        std::vector<std::shared_ptr<Person>>::iterator target = std::find_if(
            std::begin(m_people),
            std::end(m_people),
            [&](const auto& person) {
                return person->getName() == to;
            }
        );

        if (target != std::end(m_people)) {
            (*target)->receive(from, msg);
        }
    }
};


void test_chatroom_example()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    using namespace ChatRoomMediatorPattern;


    // colleagues
    std::shared_ptr<Person> john{ std::make_shared<Person>("John") };
    std::shared_ptr<Person> jane{ std::make_shared<Person>("Jane") };

    // mediator
    std::shared_ptr<GoogleChat> room{ std::make_shared<GoogleChat>() };

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
/*
[John's chat session]room: "Jane joins the chat"
[Jane's chat session]John: "hi room"
[John's chat session]Jane: "oh, hey john"
[John's chat session]room: "Simon joins the chat"
[Jane's chat session]room: "Simon joins the chat"
[John's chat session]Simon: "hi everyone!"
[Jane's chat session]Simon: "hi everyone!"
[Simon's chat session]Jane: "glad you found us, simon!"
*/

// ===========================================================================
// End-of-File
// ===========================================================================

