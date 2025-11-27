// ===========================================================================
// ExplorationStrategy.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <memory>

#include "IExplorationObserver.h"
#include "IExplorationStrategy.h"
#include "ExplorationObserver.h"

#include "ExplorationStrategy.h"

/**
* observer management methods
*/
void ExplorationStrategy::attach(std::shared_ptr<IExplorationObserver> observer) {
    m_list_observers.push_back(observer);
}

void ExplorationStrategy::detach(std::shared_ptr<IExplorationObserver> observer) {
    m_list_observers.remove(observer);
}

void ExplorationStrategy::onFinish() {
    std::cout << "got onFinish" << std::endl;
    std::list<std::shared_ptr<IExplorationObserver>>::iterator iterator = m_list_observers.begin();

    while (iterator != m_list_observers.end()) {
        std::shared_ptr<IExplorationObserver> ptr = *iterator;
        ptr->update(m_explorationResult);
        ++iterator;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
