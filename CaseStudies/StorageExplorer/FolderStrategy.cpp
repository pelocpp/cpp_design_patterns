// ===========================================================================
// FolderStrategy.cpp
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
#include "FolderStrategy.h"

// ===========================================================================

// function prototypes
static inline bool endsWith(std::string const& value, std::string const& ending);
static long getFolderSize(std::string path);

// ===========================================================================

/* This class retrieves folders size under a given path;
 * then sizes are placed in a hashtable containing folder names
 * and the size of the folders
 */
void FolderStrategy::explore(const std::string& path)
{
    exploreHelper(path);
    onFinish();
}

void FolderStrategy::exploreHelper(const std::string& path)
{
    std::filesystem::path p(path);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;

    auto entriesLambda = [this](const std::filesystem::directory_entry& entry) mutable {

        if (std::filesystem::is_directory(entry)) {

            // skip - at least for the moment - .git and .vs sub directories
            // const std::filesystem::path ext = entry.path().extension();
            std::string s = entry.path().string();
            if (endsWith(s, ".git") or endsWith(s, ".vs")) {
                return;
            }

            // retrieve size of bytes of this folder
            uintmax_t size = 0;
            try
            {
                size = getFolderSize(entry.path().string());
            }
            catch (std::filesystem::filesystem_error& e) {
                std::cout << e.what() << '\n';
            }

            // add size to the map
            m_explorationResult[s] = static_cast<long>(size);

            exploreHelper(s);
        }
    };

    std::for_each(start, end, entriesLambda);
}

void FolderStrategy::printResults()
{
    std::for_each(
        std::begin(m_explorationResult),
        std::end(m_explorationResult),
        [](const std::pair<std::string, uintmax_t>& entry) {
            std::cout << "Folder: " << entry.first << " - Size: " << entry.second << '\n';
        }
    );
}

inline bool endsWith(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

long getFolderSize(std::string path)
{
    uintmax_t r = 0;
    try {
        if (!std::filesystem::is_directory(path))
        {
            r += std::filesystem::file_size(path);
        }
        else
        {
            for (auto entry : std::filesystem::directory_iterator(path))
                r += getFolderSize(entry.path().string());
        }
    }
    catch (std::filesystem::filesystem_error& e)
    {
        std::cout << e.what() << '\n';
    }

    return static_cast<long>(r);
}

// ===========================================================================
// End-of-File
// ===========================================================================
