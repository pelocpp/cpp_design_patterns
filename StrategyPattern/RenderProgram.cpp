#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "RenderOutputFormats.h"
#include "RenderListStrategy.h"
#include "RenderTextProcessor.h"

void test_render_app()
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