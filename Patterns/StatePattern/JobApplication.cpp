// ===========================================================================
// JobApplication.cpp
// ===========================================================================

#include <iostream>
#include <memory>
#include <string_view>

namespace JobApplicationExample {

    // ============================================================================
    // Forward declarations
    // ============================================================================

    class JobApplication;

    class Received;
    class Incomplete;
    class Interviewed;
    class Invited;
    class Talentpool;
    class Hired;
    class Refused;


    // ============================================================================
    // State interface
    // ============================================================================

    class IState
    {
    public:
        virtual ~IState() = default;

        // Verhalten abhängig vom aktuellen State
        virtual void inform(JobApplication& application) = 0;
        virtual void process(JobApplication& application) = 0;

        // Nur zur Darstellung
        [[nodiscard]]
        virtual std::string_view name() const noexcept = 0;
    };


    // ============================================================================
    // Concrete State: Received
    // ============================================================================

    class Received final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "your application has been received.\n";
        }

        void process(JobApplication& application) override;

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Received";
        }
    };


    // ============================================================================
    // Concrete State: Incomplete
    // ============================================================================

    class Incomplete final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "your application is incomplete.\n";
        }

        void process(JobApplication& application) override;

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Incomplete";
        }
    };


    // ============================================================================
    // Concrete State: Interviewed
    // ============================================================================

    class Interviewed final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "your interview has been completed.\n";
        }

        void process(JobApplication& application) override;

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Interviewed";
        }
    };


    // ============================================================================
    // Concrete State: Invited
    // ============================================================================

    class Invited final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "you are invited to the next interview.\n";
        }

        void process(JobApplication& application) override;

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Invited";
        }
    };


    // ============================================================================
    // Concrete State: Talentpool
    // ============================================================================

    class Talentpool final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "you have been added to our talent pool.\n";
        }

        void process(JobApplication&) override
        {
            // Terminal state in this example.
        }

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Talentpool";
        }
    };


    // ============================================================================
    // Concrete State: Hired
    // ============================================================================

    class Hired final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "congratulations, you are hired!\n";
        }

        void process(JobApplication&) override
        {
            // Terminal state in this example.
        }

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Hired";
        }
    };


    // ============================================================================
    // Concrete State: Refused
    // ============================================================================

    class Refused final : public IState
    {
    public:
        void inform(JobApplication&) override
        {
            std::cout
                << "Inform applicant: "
                "unfortunately, your application was refused.\n";
        }

        void process(JobApplication&) override
        {
            // Terminal state in this example.
        }

        [[nodiscard]]
        std::string_view name() const noexcept override
        {
            return "Refused";
        }
    };


    // ============================================================================
    // Context: JobApplication
    // ============================================================================

    class JobApplication
    {
    public:
        JobApplication()
            : m_state(std::make_unique<Received>())
        {}

        // ------------------------------------------------------------------------
        // Public interface
        // ------------------------------------------------------------------------

        void inform()
        {
            m_state->inform(*this);
        }

        void process()
        {
            m_state->process(*this);
        }

        [[nodiscard]]
        std::string_view state() const noexcept
        {
            return m_state->name();
        }

        void print() const
        {
            std::cout
                << "Current state: "
                << m_state->name()
                << '\n';
        }

    private:

        // ------------------------------------------------------------------------
        // State transition
        // ------------------------------------------------------------------------

        void setState(std::unique_ptr<IState> nextState)
        {
            if (!nextState)
                return;

            std::cout
                << "Transition: "
                << m_state->name()
                << " -> "
                << nextState->name()
                << '\n';

            m_state = std::move(nextState);
        }

        // ------------------------------------------------------------------------
        // Concrete States are allowed to change the Context's state.
        // ------------------------------------------------------------------------

        friend class Received;
        friend class Incomplete;
        friend class Interviewed;
        friend class Invited;

        std::unique_ptr<IState> m_state;
    };


    // ============================================================================
    // State transitions
    // ============================================================================
    //
    // Die eigentliche Transition-Logik befindet sich in den Concrete States.
    // JobApplication kennt die konkreten States nicht.
    //
    // ============================================================================

    // Received
    //
    // Received -> Incomplete
    // Received -> Interviewed
    //
    void Received::process(JobApplication& application)
    {
        // In einem echten System würde hier z.B. geprüft werden,
        // ob alle Bewerbungsunterlagen vollständig sind.

        const bool applicationIsComplete = true;

        if (applicationIsComplete)
        {
            application.setState(
                std::make_unique<Interviewed>());
        }
        else
        {
            application.setState(
                std::make_unique<Incomplete>());
        }
    }


    // ----------------------------------------------------------------------------
    // Incomplete
    //
    // Incomplete -> Received
    // Incomplete -> Refused
    //
    void Incomplete::process(JobApplication& application)
    {
        // Beispiel:
        // Die fehlenden Unterlagen wurden nachgereicht.

        const bool documentsReceived = true;

        if (documentsReceived)
        {
            application.setState(
                std::make_unique<Received>());
        }
        else
        {
            application.setState(
                std::make_unique<Refused>());
        }
    }


    // ----------------------------------------------------------------------------
    // Interviewed
    //
    // Interviewed -> Invited
    // Interviewed -> Refused
    //
    void Interviewed::process(JobApplication& application)
    {
        // Beispiel:
        // Das Interview wird bewertet.

        const bool interviewSuccessful = true;

        if (interviewSuccessful)
        {
            application.setState(
                std::make_unique<Invited>());
        }
        else
        {
            application.setState(
                std::make_unique<Refused>());
        }
    }


    // ----------------------------------------------------------------------------
    // Invited
    //
    // Invited -> Talentpool
    // Invited -> Hired
    // Invited -> Refused
    //
    void Invited::process(JobApplication& application)
    {
        // Beispielentscheidung.
        //
        // In einem echten System würde hier vermutlich
        // eine fachliche Entscheidung getroffen werden.

        const bool hired = true;

        if (hired)
        {
            application.setState(
                std::make_unique<Hired>());
        }
        else
        {
            application.setState(
                std::make_unique<Talentpool>());
        }
    }
}

void test_jobapplication_example()
{
    using namespace JobApplicationExample;

    JobApplication application;

    application.print();

    application.inform();
    application.process();

    application.print();

    application.inform();
    application.process();

    application.print();

    application.inform();
    application.process();

    application.print();

    application.inform();
}
// ===========================================================================
// End-of-File
// ===========================================================================
