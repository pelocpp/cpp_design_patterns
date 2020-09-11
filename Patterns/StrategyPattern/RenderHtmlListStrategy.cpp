// ===========================================================================
// RenderHtmlListStrategy.cpp
// ===========================================================================

#include <iostream>
#include <sstream>
#include <string>

#include "RenderListStrategy.h"
#include "RenderHtmlListStrategy.h"

void RenderHtmlListStrategy::start(std::ostringstream& oss) {
    oss << "<ul>\n";
}

void RenderHtmlListStrategy::end(std::ostringstream& oss) {
    oss << "</ul>\n";
}

void RenderHtmlListStrategy::addListItem(std::ostringstream& oss, const std::string& item) {
    oss << "<li>" << item << "</li>\n";
}

// ===========================================================================
// End-of-File
// ===========================================================================
