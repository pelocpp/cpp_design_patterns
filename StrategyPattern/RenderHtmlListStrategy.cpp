#include <iostream>
#include <sstream>
#include <string>

#include "RenderListStrategy.h"
#include "RenderHtmlListStrategy.h"

void HtmlListStrategy::start(std::ostringstream& oss) {
    oss << "<ul>\n";
}

void HtmlListStrategy::end(std::ostringstream& oss) {
    oss << "</ul>\n";
}

void HtmlListStrategy::addListItem(std::ostringstream& oss, const std::string& item) {
    oss << "<li>" << item << "</li>\n";
}
