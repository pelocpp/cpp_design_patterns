// ===========================================================================
// SRP.cpp // Single Responsibility Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

namespace AntiConceptualExampleSRP {

    class Journal
    {
    private:
        std::string              m_title;
        std::vector<std::string> m_entries;
        std::size_t              m_count;

    public:
        Journal(const std::string& title) 
            : m_title{ title }, m_count{}
        {}

        void addEntry(const std::string& entry) {
            m_count++;
            std::string text { std::to_string(m_count) + ": " + entry };
            m_entries.push_back(text);
        }

        auto getEntries() const { return m_entries; }

        void save(const std::string& filename, std::ostream& os) {

            os << m_title << std::endl;
            for (const auto& entry : m_entries) {
                os << entry << std::endl;
            }
        }
    };
}

namespace ConceptualExampleSRP
{
    class Journal 
    {
    private:
        std::string              m_title;
        std::vector<std::string> m_entries;
        std::size_t              m_count;

    public:
        Journal(const std::string& title)
            : m_title{ title }, m_count{}
        {}

        void addEntry(const std::string& entry) {
            m_count++;
            std::string text { std::to_string(m_count) + ": " + entry };
            m_entries.push_back(text);
        }

        auto getTitle() const { return m_title; }
        auto getEntries() const { return m_entries; }
    };

    struct SavingManager
    {
        static void save(const Journal& journal, const std::string& filename, std::ostream& os) {

            os << journal.getTitle() << std::endl;
            for (const auto& entry : journal.getEntries()) {
                os << entry << std::endl;
            }
        }
    };
}

static void test_anti_conceptual_example_srp ()
{
    using namespace AntiConceptualExampleSRP;

    Journal journal{ "John" };
    journal.addEntry("In the morning I went to school");
    journal.addEntry("In the afternoon I did my homework");
    journal.save("diary.txt", std::cout);
}

static void test_conceptual_example_srp()
{
    using namespace ConceptualExampleSRP;

    Journal journal{ "John" };
    journal.addEntry("In the morning I went to school");
    journal.addEntry("In the afternoon I did my homework");
    SavingManager::save(journal, "diary.txt", std::cout);
}

void test_srp()
{
    test_anti_conceptual_example_srp();
    test_conceptual_example_srp();
}

// ===========================================================================
// End-of-File
// ===========================================================================
