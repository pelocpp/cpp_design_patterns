// ===========================================================================
// RenderProgram.cpp
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

void test_render_app_dynamically()
{
    RenderTextProcessor processor;

    // 'markdown' strategy
    processor.setOutputFormat(std::make_unique<RenderMarkdownListStrategy>());
    processor.appendList({ "foo", "bar", "baz" });
    std::cout << processor.toString() << std::endl;

    // 'html' strategy
    processor.clear();
    processor.setOutputFormat(std::make_unique<RenderHtmlListStrategy>());
    processor.appendList({ "FOO", "BAR", "BAZ" });
    std::cout << processor.toString() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
