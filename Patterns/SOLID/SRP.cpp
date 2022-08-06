// ===========================================================================
// SRP.cpp // Single Responsibility Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace AntiConceptualExampleSRP {

    class Journal
    {
    private:
        std::string m_title;
        std::vector<std::string> m_entries;

    public:
        Journal(const std::string& title) : m_title{ title } {}

        void addEntries(const std::string& entry) {
            static uint32_t count = 0;
            count++;
            std::string text = std::to_string(count) + ": " + entry;
            m_entries.push_back(text);
        }

        auto getEntries() const { return m_entries; }

        void save(const std::string& filename, std::ostream& os) {

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
        std::string m_title;
        std::vector<std::string> m_entries;

    public:
        Journal(const std::string& title) : m_title{ title } {}

        void addEntries(const std::string& entry) {
            static uint32_t count = 0;
            count++;
            std::string text = std::to_string(count) + ": " + entry;
            m_entries.push_back(text);
        }

        auto get_entries() const { return m_entries; }
    };

    struct SavingManager
    {
        static void save(const Journal& journal, const std::string& filename, std::ostream& os) {

            for (const auto& entry : journal.get_entries()) {
                os << entry << std::endl;
            }
        }
    };
}

void test_anti_conceptual_example_srp ()
{
    using namespace AntiConceptualExampleSRP;

    Journal journal{ "Peter" };
    journal.addEntries("In the morning I went to school");
    journal.addEntries("In the afternoon I did my homework");
    journal.save("diary.txt", std::cout);
}

void test_conceptual_example_srp()
{
    using namespace ConceptualExampleSRP;

    Journal journal{ "Peter" };
    journal.addEntries("In the morning I went to school");
    journal.addEntries("In the afternoon I did my homework");
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
