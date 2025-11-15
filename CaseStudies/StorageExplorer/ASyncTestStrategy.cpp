// ===========================================================================
// FileTypeStrategy.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <list>
#include <thread> 
#include <chrono>

#include "IExplorationObserver.h"
#include "IExplorationStrategy.h"
#include "ExplorationObserver.h"

#include "ExplorationStrategy.h"
#include "ASyncTestStrategy.h"

// ===========================================================================

void ASyncTestStrategy::explore(const std::string& path)
{
    std::thread t([this]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            onFinish();
        });

    t.detach();
}

void ASyncTestStrategy::exploreHelper(const std::string& path) {

}

void ASyncTestStrategy::printResults() {

    //std::for_each(
    //    std::begin(m_explorationResult),
    //    std::end(m_explorationResult),
    //    [](const std::pair<std::string, long>& entry) {
    //        std::cout << "Ext: " << entry.first << " - Total Sizes: " << entry.second << '\n';
    //    }
    //);
}

// ===========================================================================
// End-of-File
// ===========================================================================
