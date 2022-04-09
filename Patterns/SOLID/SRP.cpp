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
        std::string               m_title;
        std::vector<std::string>  m_entries;

    public:
        explicit Journal(const std::string& title) : m_title{ title } {}

        void addEntries(const std::string& entry) {
            static uint32_t count = 0;
            count++;
            std::string text = std::to_string(count) + ": " + entry;
            m_entries.push_back(text);
        }

        auto getEntries() const { return m_entries; }

        void save(const std::string& filename, std::ostream& os) {

            for (auto& s : m_entries) {
                os << s << std::endl;
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

// ===========================================================================
// End-of-File
// ===========================================================================
