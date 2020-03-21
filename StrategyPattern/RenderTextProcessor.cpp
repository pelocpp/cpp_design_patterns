// ===========================================================================
// RenderTextProcessor.cpp
// ===========================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "RenderOutputFormats.h"
#include "RenderListStrategy.h"
#include "RenderMarkdownListStrategy.h"
#include "RenderHtmlListStrategy.h"
#include "RenderTextProcessor.h"

void TextProcessor::setOutputFormat(const OutputFormat format) {
    switch (format)
    {
    case OutputFormat::Markdown:
        m_listStrategy = std::make_unique<MarkdownListStrategy>();
        break;
    case OutputFormat::Html:
        m_listStrategy = std::make_unique<HtmlListStrategy>();
        break;
    default:
        throw std::runtime_error("Unsupported strategy!");
    }
}

void TextProcessor::appendList(const std::vector<std::string>& items) {
    m_listStrategy->start(m_oss);

    for (const auto& item : items)
        m_listStrategy->addListItem(m_oss, item);

    m_listStrategy->end(m_oss);
}

std::string TextProcessor::toString() const {
    return m_oss.str();
}

void TextProcessor::clear() {
    m_oss.str("");
    m_oss.clear();
}

// ===========================================================================
// End-of-File
// ===========================================================================
