// ===========================================================================
// Program.cpp
// ===========================================================================

// 1.) Das Traversieren der Verzeichnisstruktur in einen Thread auslagern ....


// 2.) Zweite Console
//https://codereview.stackexchange.com/questions/195157/using-multiple-console-windows-for-output
//https://www.codeproject.com/Articles/13368/Multiple-consoles-for-a-single-application
//https://stackoverflow.com/questions/20847474/multiple-consoles-for-a-single-application-c

// ===========================================================================

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <filesystem>

#include "IExplorationObserver.h"
#include "IExplorationStrategy.h"
#include "ExplorationObserver.h"

#include "ExplorationStrategy.h"
#include "FileTypeStrategy.h"
#include "FolderStrategy.h"
#include "ASyncTestStrategy.h"

#include "ListView.h"
#include "ListViewAdapter.h"

// ===========================================================================

void testStategyPattern() {

    // initialization section: setup strategy
    std::shared_ptr<IExplorationStrategy> explorer;
    std::shared_ptr<IExplorationStrategy> folderStrategy = std::make_shared<FolderStrategy>();
    std::shared_ptr<IExplorationStrategy> fileTypeStrategy = std::make_shared<FileTypeStrategy>();
    std::shared_ptr<IExplorationStrategy> asyncTestStrategy = std::make_shared<ASyncTestStrategy>();

    // initialization section: setup observer
    std::shared_ptr<IExplorationObserver> concreteObserver = std::make_shared<ExplorationObserver>();
    folderStrategy->attach(concreteObserver);
    fileTypeStrategy->attach(concreteObserver);
    asyncTestStrategy->attach(concreteObserver);

    // initialization section: setup listviewadapter
    std::shared_ptr<ListViewAdapter> adapter = std::make_shared<ListViewAdapter>();
    std::map<std::string, long> empty;
    adapter->update(empty);
    folderStrategy->attach(adapter);
    fileTypeStrategy->attach(adapter);
    asyncTestStrategy->attach(adapter);

    // choose strategy
    int input = 1;
    switch (input)
    {
    case 0:
        explorer = folderStrategy;
        break;

    case 1:
        explorer = fileTypeStrategy;
        break;

    case 2:
        explorer = asyncTestStrategy;
        break;

    default:
        break;
        // more strategies ....
    }

    // execute the algorithm
    constexpr const char* path =
        R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns)";

    explorer->explore(path);
    // explorer->printResults();

    // block main thread
    char ch;
    std::cin >> ch;
}

int main() {
    std::cout << "Cpp Design Patterns Case Studies: Storage Explorer" << std::endl;
    testStategyPattern();
    std::cout << "Done." << std::endl;
    return 0; 
}

// ===========================================================================
// End-of-File
// ===========================================================================
