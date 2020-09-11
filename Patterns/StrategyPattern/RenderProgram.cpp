// ===========================================================================
// RenderProgram.cpp
// ===========================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "RenderOutputFormats.h"
#include "RenderListStrategy.h"
#include "RenderHtmlListStrategy.h"
#include "RenderMarkdownListStrategy.h"
#include "RenderTextProcessor.h"

void test_render_app_dynamically()
{
    // 'markdown' strategy
    TextProcessor tp;
    tp.setOutputFormat(OutputFormat::Markdown);
    tp.appendList({ "foo", "bar", "baz" });
    std::cout << tp.toString() << std::endl;

    // 'html' strategy
    tp.clear();
    tp.setOutputFormat(OutputFormat::Html);
    tp.appendList({ "foo", "bar", "baz" });
    std::cout << tp.toString() << std::endl;
}

template <typename LS>
class AnotherTextProcessor
{
private:
    std::ostringstream m_oss;
    LS m_listStrategy;
    // std::unique_ptr<LS> m_listStrategy;  // would also work

public:
    void clear() {
        m_oss.str("");
        m_oss.clear();
    }

    void appendList(const std::vector <std::string > items)
    {
        m_listStrategy.start(m_oss);

        for (auto& item : items)
            m_listStrategy.addListItem(m_oss, item);

        m_listStrategy.end(m_oss);
    }

    std::string toString() const {
        return m_oss.str();
    }
};

void test_render_app_statically()
{
    // 'markdown' strategy
    AnotherTextProcessor<RenderMarkdownListStrategy> tpm;
    tpm.appendList({ "foo", "bar", "baz" });
    std::cout << tpm.toString() << std::endl;

    // 'html' strategy
    AnotherTextProcessor<RenderHtmlListStrategy> tph;
    tph.appendList({ "foo", "bar", "baz" });
    std::cout << tph.toString() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
