// ===========================================================================
// StaticStrategyExample.cpp // Static Strategy Pattern Example
// ===========================================================================

#include <initializer_list>
#include <iostream>
#include <memory>
#include <print>
#include <sstream>
#include <string>

// =====================================================================
// dynamic strategy pattern example

namespace DynamicStrategyPatternExample {

    enum class Format { Markdown, Html };

    struct IListStrategy
    {
        virtual ~IListStrategy() {}

        virtual void start(std::ostringstream& oss) = 0;
        virtual void end(std::ostringstream& oss) = 0;
        virtual void add_item(std::ostringstream& oss, const std::string& item) = 0;
    };

    struct MarkdownListStrategy : public IListStrategy
    {
        void start(std::ostringstream& oss) override {};

        void end(std::ostringstream& oss) override {};

        void add_item(std::ostringstream& oss, const std::string& item) override {
            oss << " - " << item << std::endl;
        }
    };

    struct HtmlListStrategy : public IListStrategy
    {
        void start(std::ostringstream& oss) override {
            oss << "<ul>" << std::endl;
        }

        void end(std::ostringstream& oss) override {
            oss << "</ul>" << std::endl;
        }

        void add_item(std::ostringstream& oss, const std::string& item) override {
            oss << "\t<li>" << item << "</li>" << std::endl;
        }
    };

    class TextProcessor
    {
    private:
        std::unique_ptr<IListStrategy> m_list_strategy;
        std::ostringstream             m_oss;

    public:
        void clear() {
            m_oss.str("");
            m_oss.clear();
        }

        void append_list(std::initializer_list<std::string> items) {

            m_list_strategy->start(m_oss);
            for (const auto& item : items) {
                m_list_strategy->add_item(m_oss, item);
            }
            m_list_strategy->end(m_oss);
        }

        void set_output_format(Format format) {

            switch (format)
            {
            case Format::Markdown:
                m_list_strategy = std::make_unique<MarkdownListStrategy>();
                break;

            case Format::Html:
                m_list_strategy = std::make_unique<HtmlListStrategy>();
                break;
            }
        }

        std::string str() { return m_oss.str(); }
    };
}

void test_dynamic_strategy_example ()
{
    using namespace DynamicStrategyPatternExample;

    // markdown
    TextProcessor tp{};
    tp.set_output_format(Format::Markdown);
    tp.append_list({ "foo", "bar", "baz" });
    std::println("{}", tp.str());

    // html
    tp.clear();
    tp.set_output_format(Format::Html);
    tp.append_list({ "foo", "bar", "baz" });
    std::println("{}", tp.str());
}

// =====================================================================
// static strategy pattern example

namespace StaticStrategyPatternExample {

    template <typename TList>
    concept ListRequirements = requires(TList& list, std::ostringstream& oss, const std::string& item)
    {
        { list.start(oss) } -> std::same_as<void>;
        { list.end(oss) } -> std::same_as<void>;
        { list.add_item(oss, item) } -> std::same_as<void>;
    };

    template<typename TList>
        requires ListRequirements<TList>
    class TextProcessorEx
    {
    private:
        TList              m_list;
        std::ostringstream m_oss;

    public:
        void append_list(std::initializer_list<std::string> items)
        {
            m_list.start(m_oss);
            for (const auto& item : items) {
                m_list.add_item(m_oss, item);
            }
            m_list.end(m_oss);
        }

        std::string str() const { return m_oss.str(); }
    };

    struct MarkdownListStrategyEx
    {
        void start(std::ostringstream& oss) {};

        void end(std::ostringstream& oss) {};

        void add_item(std::ostringstream& oss, const std::string& item) {
            oss << " - " << item << std::endl;
        }
    };

    struct HtmlListStrategyEx
    {
        void start(std::ostringstream& oss) {
            oss << "<ul>" << std::endl;
        }

        void end(std::ostringstream& oss) {
            oss << "</ul>" << std::endl;
        }

        void add_item(std::ostringstream& oss, const std::string& item) {
            oss << "\t<li>" << item << "</li>" << std::endl;
        }
    };
}

void test_static_strategy_example ()
{
    using namespace StaticStrategyPatternExample;

    // Markdown
    TextProcessorEx<MarkdownListStrategyEx> tp1{};
    tp1.append_list({ "foo", "bar", "baz" });
    std::println("{}", tp1.str());

    // <Html
    TextProcessorEx<HtmlListStrategyEx> tp2{};
    tp2.append_list({ "foo", "bar", "baz" });
    std::println("{}", tp2.str());
}

// ===========================================================================
// End-of-File
// ===========================================================================
