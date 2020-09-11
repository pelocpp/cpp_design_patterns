// ===========================================================================
// RenderProgramTemplates.cpp // class StaticTextProcessor
// ===========================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "RenderListStrategy.h"
#include "RenderHtmlListStrategy.h"
#include "RenderMarkdownListStrategy.h"
#include "RenderTextProcessor.h"

template <typename LS>
class StaticTextProcessor
{
private:
    std::ostringstream m_oss;
    std::unique_ptr<LS> m_listStrategy;

public:
    StaticTextProcessor()
    {
        m_listStrategy = std::make_unique<LS>();
    }
    
    void clear() {
        m_oss.str("");
        m_oss.clear();
    }

    void appendList(const std::vector <std::string> items)
    {
        m_listStrategy->start(m_oss);

        for (auto& item : items)
            m_listStrategy->add(m_oss, item);

        m_listStrategy->end(m_oss);
    }

    std::string toString() const {
        return m_oss.str();
    }
};

void test_render_app_statically()
{
    // 'markdown' strategy
    StaticTextProcessor<RenderMarkdownListStrategy> tpMarkdown;
    tpMarkdown.appendList({ "foo", "bar", "baz" });
    std::cout << tpMarkdown.toString() << std::endl;

    // 'html' strategy
    StaticTextProcessor<RenderHtmlListStrategy> tpHtml;
    tpHtml.appendList({ "FOO", "BAR", "BAZ" });
    std::cout << tpHtml.toString() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
