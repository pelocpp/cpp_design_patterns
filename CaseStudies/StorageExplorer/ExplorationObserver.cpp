// ===========================================================================
// ExplorationObserver.cpp
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
#include "FileTypeStrategy.h"
#include "FolderStrategy.h"

// ===========================================================================

void ExplorationObserver::update(std::map<std::string, long> result) {
    std::cout << "Done: received " << result.size() << " results!" << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
