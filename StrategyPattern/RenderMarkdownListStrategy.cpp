#include <iostream>
#include <sstream>
#include <string>

#include "RenderListStrategy.h"
#include "RenderMarkdownListStrategy.h"

void MarkdownListStrategy::addListItem(std::ostringstream& oss, const std::string& item) {
    oss << "  * " << item << std::endl;
}
