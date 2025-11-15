// ===========================================================================
// FileTypeStrategy.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <filesystem>
#include <memory>

#include "IExplorationObserver.h"
#include "IExplorationStrategy.h"
#include "ExplorationObserver.h"

#include "ExplorationStrategy.h"
#include "FileTypeStrategy.h"

// ===========================================================================

void FileTypeStrategy::explore(const std::string& path)
{
    exploreHelper(path);
    onFinish();
}

void FileTypeStrategy::exploreHelper(const std::string& path) {

    std::filesystem::path p(path);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;

    auto entriesLambda = [this](const std::filesystem::directory_entry& entry) mutable {

        const std::filesystem::path file = entry.path().filename();
        const std::string name{ file.string() };
        const std::string ext{ file.extension().string() };

        //std::cout << "Entry: " << " = " << name << '\n';
        //std::cout << "Extension: [" << ext << "]" << '\n';

        if (std::filesystem::is_regular_file(entry)) {

            if (ext.empty()) {
                // to be done - no extension !!!
                return;
            }

            uintmax_t size = 0;
            try
            {
                size = file_size(entry);
            }
            catch (std::filesystem::filesystem_error& e) {
                std::cout << e.what() << '\n';
            }

            if (m_explorationResult.count(ext) > 0) {
                m_explorationResult[ext] = static_cast<long>(m_explorationResult[ext] + size);
            }
            else {
                m_explorationResult[ext] = static_cast<long>(size);;
            }
        }
        else if (std::filesystem::is_directory(entry)) {

            // do the same process to the subdirectories

            //  std::filesystem::directory_entry subEntry { entry };
            std::string s = entry.path().string();

            // skip - at least for the moment - .git sub directory
            if (s == std::string(".git") or s == std::string(".git")) {
                return;
            }

            exploreHelper(s);
        }
    };

    std::for_each(start, end, entriesLambda);
}

void FileTypeStrategy::printResults()
{

    std::for_each(
        std::begin(m_explorationResult),
        std::end(m_explorationResult),
        [](const std::pair<std::string, uintmax_t>& entry) {
            std::cout << "Ext: " << entry.first << " - Total Sizes: " << entry.second << '\n';
        }
    );
}

// ===========================================================================
// End-of-File
// ===========================================================================
