// ===========================================================================
// Heist.cpp // Builder Pattern
// ===========================================================================

#include <algorithm>
#include <chrono>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

namespace HeistExample {

    // ---------------------------------------------------------------
    // Product: a finished heist plan. It can only be created by the
    // HeistBuilder (private constructor), so it is never half-built.
    // ---------------------------------------------------------------
    class Heist
    {
    public:
        void briefing() const
        {
            std::println("=== Operation {} ===", m_codename);
            std::println("Target       : {} (security {}/10)", m_target, m_securityLevel);
            std::println("Disguise     : {}", m_disguise);
            std::println("Time limit   : {} min", m_timeLimit.count());
            std::println("Escape route : {}", m_escapeRoute);

            std::println("Crew:");
            for (const auto& member : m_crew) {
                std::println("  - {:<6} {}", member.name, member.specialty);
            }

            std::println("Gadgets:");
            for (const auto& gadget : m_gadgets) {
                std::println("  - {}", gadget);
            }

            std::println("Success chance: {}%\n", m_successChance);
        }

    private:
        friend class HeistBuilder;
        Heist() = default;

        struct CrewMember {
            std::string name;
            std::string specialty;
        };

        std::string              m_codename;
        std::string              m_target;
        int                      m_securityLevel{ 0 };
        std::string              m_disguise{ "none" };
        std::string              m_escapeRoute;
        std::chrono::minutes     m_timeLimit{ 30 };
        std::vector<CrewMember>  m_crew;
        std::vector<std::string> m_gadgets;
        int                      m_successChance{ 0 };
    };

    // ---------------------------------------------------------------
    // Builder: fluent interface, validation happens in build()
    // ---------------------------------------------------------------
    class HeistBuilder
    {
    public:
        HeistBuilder() : m_heist{ std::unique_ptr<Heist>(new Heist) } {}

        HeistBuilder& codename(std::string name) {
            m_heist->m_codename = std::move(name);
            return *this;
        }

        HeistBuilder& target(std::string name, int securityLevel) {
            m_heist->m_target = std::move(name);
            m_heist->m_securityLevel = securityLevel;
            return *this;
        }

        HeistBuilder& addCrewMember(std::string name, std::string specialty) {
            m_heist->m_crew.push_back({ std::move(name), std::move(specialty) });
            return *this;
        }

        HeistBuilder& addGadget(std::string gadget) {
            m_heist->m_gadgets.push_back(std::move(gadget));
            return *this;
        }

        HeistBuilder& disguise(std::string disguise) {
            m_heist->m_disguise = std::move(disguise);
            return *this;
        }

        HeistBuilder& escapeRoute(std::string route) {
            m_heist->m_escapeRoute = std::move(route);
            return *this;
        }

        HeistBuilder& timeLimit(std::chrono::minutes limit) {
            m_heist->m_timeLimit = limit;
            return *this;
        }

        // ownership of the finished plan moves to the caller
        std::unique_ptr<Heist> build()
        {
            if (m_heist->m_target.empty())
                throw std::logic_error("No target chosen - what are we even stealing?");
            if (m_heist->m_crew.empty())
                throw std::logic_error("Nobody in the crew - this is a one-person job? No way.");
            if (m_heist->m_escapeRoute.empty())
                throw std::logic_error("No escape route - this is a one-way trip.");
            if (m_heist->m_crew.size() < static_cast<size_t>(m_heist->m_securityLevel / 3))
                throw std::logic_error("Crew too small for this level of security.");

            int chance = 50
                - 5 * m_heist->m_securityLevel
                + 8 * static_cast<int>(m_heist->m_crew.size())
                + 4 * static_cast<int>(m_heist->m_gadgets.size())
                + (m_heist->m_disguise != "none" ? 5 : 0);
            m_heist->m_successChance = std::clamp(chance, 5, 95);

            auto result = std::move(m_heist);
            m_heist = std::unique_ptr<Heist>(new Heist);   // builder can be reused
            return result;
        }

    private:
        std::unique_ptr<Heist> m_heist;
    };

    // ---------------------------------------------------------------
    // Director: knows ready-made "recipes" and uses the builder
    // ---------------------------------------------------------------
    class Director
    {
    public:
        std::unique_ptr<Heist> casinoJob(HeistBuilder& builder) const
        {
            return builder
                .codename("Golden Dragon")
                .target("Golden Dragon Casino", 9)
                .addCrewMember("Ada", "safecracker")
                .addCrewMember("Rex", "hacker")
                .addCrewMember("Mona", "con artist")
                .addGadget("EMP pulse device")
                .addGadget("thermal drill")
                .addGadget("fake VIP passes")
                .disguise("high roller in a tuxedo")
                .escapeRoute("service elevator to the helipad")
                .timeLimit(std::chrono::minutes{ 12 })
                .build();
        }

        std::unique_ptr<Heist> museumJob(HeistBuilder& builder) const
        {
            return builder
                .codename("Blue Star")
                .target("Vault of the Blue Star Diamond", 7)
                .addCrewMember("Ada", "safecracker")
                .addCrewMember("Lux", "acrobat")
                .addGadget("laser grid mirror")
                .disguise("night cleaning staff")
                .escapeRoute("ventilation shaft to the roof")
                .timeLimit(std::chrono::minutes{ 20 })
                .build();
        }
    };
}

void test_heist_example()
{
    using namespace HeistExample;

    HeistBuilder builder;
    Director director;

    // 1. a ready-made plan from the director
    director.casinoJob(builder)->briefing();
    director.museumJob(builder)->briefing();

    // 2. a custom plan - the client uses the builder directly
    auto custom = builder
        .codename("Quick Grab")
        .target("Corner Jewelry Store", 3)
        .addCrewMember("Rex", "getaway driver")
        .escapeRoute("back alley")
        .build();

    custom->briefing();

    // 3. an invalid plan - the builder refuses to build it
    try {
        auto broken = builder
            .target("Fort Knox", 10)
            .addCrewMember("Rex", "hacker")
            .escapeRoute("tunnel")
            .build();
    }
    catch (const std::logic_error& e) {
        std::println("Plan rejected: {}", e.what());
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
