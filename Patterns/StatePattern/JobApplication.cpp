// ===========================================================================
// JobApplication.cpp
// ===========================================================================

#include <iostream>
#include <type_traits>
#include <memory>

namespace JobApplicationExample {

    class State
    {
    public:
        virtual ~State() {}

        virtual void inform() = 0;             // inform applicant
        virtual void process() = 0;            // process job application
        virtual std::string to_string() = 0;   // print current state
    };

    // =======================================================================

    // Abgesagt
    class Refused : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Refused"; }
    };

    // Eingegangen
    class Received : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Received"; }
    };

    // Eingeladen
    class Invited : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Invited"; }
    };

    // Eingestellt
    class Hired : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Hired"; }
    };

    // Interviewt
    class Interviewed : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Interviewed"; }
    };

    // Talentpool
    class Talentpool : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Talentpool"; }
    };

    // Unvollstaendig
    class Incomplete : public State
    {
    public:
        void inform() override {}
        void process() override {}
        std::string to_string() override { return "Incomplete"; }
    };

    // =======================================================================

    class JobApplication
    {
    private:
        std::shared_ptr<State> m_state;

    public:
        JobApplication()
        {
            m_state = std::make_shared<Received>();
        }

        std::shared_ptr<State> getState()
        {
            return m_state;
        }

        void setState(std::shared_ptr<State> nextState)
        {
            if (nextState != m_state)
            {
                if (!isStateAccepted(nextState)) {
                    std::cout << "State " << nextState->to_string() << " not allowed here!" << std::endl;
                }
                else {
                    m_state = nextState;
                }
            }
        }

        void inform()
        {
            m_state->inform();
        }

        void process()
        {
            m_state->process();
        }

        void print()
        {
            std::cout << m_state->to_string() << std::endl;
        }

    private:
        bool isStateAccepted(std::shared_ptr<State> nextState)
        {
            if (typeid(*m_state) == typeid(Received)) {
                return
                    typeid(*nextState) == typeid(Incomplete) ||
                    typeid(*nextState) == typeid(Interviewed);
            }

            if (typeid(*m_state) == typeid(Incomplete)) {
                return
                    typeid(*nextState) == typeid(Refused) ||
                    typeid(*nextState) == typeid(Received);
            }

            if (typeid(*m_state) == typeid(Interviewed)) {
                return
                    typeid(*nextState) == typeid(Refused) ||
                    typeid(*nextState) == typeid(Invited);
            }

            if (typeid(*m_state) == typeid(Refused)) {
                return false;
            }

            if (typeid(*m_state) == typeid(Invited)) {
                return
                    typeid(*nextState) == typeid(Talentpool) ||
                    typeid(*nextState) == typeid(Hired) ||
                    typeid(*nextState) == typeid(Refused);
            }

            if (typeid(*m_state) == typeid(Talentpool)) {
                return false;
            }

            if (typeid(*m_state) == typeid(Hired)) {
                return false;
            }

            return false;
        }
    };

    static void clientCode()
    {
        JobApplication b;
        b.print();

        b.setState(std::make_shared<Hired>());         // state not allowed here
        b.setState(std::make_shared<Interviewed>());   // state allowed
        b.print();
        b.inform();
        b.process();

        b.setState(std::make_shared<Talentpool>());    // state not allowed here

        b.setState(std::make_shared<Invited>());       // state allowed
        b.print();

        b.setState(std::make_shared<Received>());      // state not allowed here

        b.setState(std::make_shared<Hired>());         // state allowed
        b.print();
    }
}

void test_jobapplication_example() {

    using namespace JobApplicationExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
