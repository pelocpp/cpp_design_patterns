// ===========================================================================
// ListViewAdapter.cpp
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

#include "ListView.h"
#include "ListViewAdapter.h"

// ===========================================================================

ListViewAdapter::ListViewAdapter() 
{
    // initialization section: setup listview
    m_listView = std::make_shared<ListView>();
    m_listView->setColumns(3);
    m_listView->setColumnHeader({"AAA", "BBB", "CCC"});
    m_listView->show();
}

ListViewAdapter::~ListViewAdapter()
{
}

void ListViewAdapter::update(std::map<std::string, long> result)
{
    // TODO HIer result adden ....
    std::cout << "Yeahhhhhhhhhhhhhhhh" << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
