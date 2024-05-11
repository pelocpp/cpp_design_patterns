#include <iostream>
#include <string>
#include <list>
#include <memory>

class Widget
{
private:
    std::string m_htmlCode;

public:
    std::string getHtmlCode()
    {
        return m_htmlCode;
    }

    Widget(const std::string& htmlCode)
    {
        m_htmlCode = htmlCode;
    }
};

class HtmlPage
{
private:
    std::list<std::shared_ptr<Widget>> m_widgets;
    std::string m_htmlCode;

public:
    std::list<std::shared_ptr<Widget>>& getWidgets()
    {
        return m_widgets;
    }

    std::string getHtmlCode() const
    {
        return m_htmlCode;
    }

    void setHtmlCode(const std::string& htmlCode)
    {
        m_htmlCode = htmlCode;
    }
};

class LayoutManager
{
private:
    HtmlPage m_htmlPage;

public:
    LayoutManager() {}

    virtual void addWidget(std::shared_ptr<Widget>) = 0;
    virtual void render() = 0;

    HtmlPage& getHtmlPage()
    {
        return m_htmlPage;
    }
};

class Layouter
{
private:
    std::list<std::shared_ptr<Widget>> m_widgets;
    HtmlPage m_htmlPage;

public:
    Layouter(std::list<std::shared_ptr<Widget>> widgets)
    {
        m_widgets = widgets;
    }

    void doLayout(LayoutManager&& layoutManager)
    {
        for (std::shared_ptr<Widget> widget : m_widgets)
        {
            layoutManager.addWidget(widget);
        }

        layoutManager.render();
        m_htmlPage = layoutManager.getHtmlPage();
    }

    void printLayoutedHtmlCode()
    {
        std::cout << "HTML: " << m_htmlPage.getHtmlCode() << std::endl;
    }
};

class FlowLayoutManager : public LayoutManager
{
public:
    virtual void addWidget(std::shared_ptr<Widget> widget) override
    {
        getHtmlPage().getWidgets().push_back(widget);
    }

    virtual void render() override
    {
        std::string html = renderHtmlFromWidgets();
        getHtmlPage().setHtmlCode(html);
    }

private:
    std::string renderHtmlFromWidgets()
    {
        return std::string("HTML-Code for FlowLayout");
    }
};

class BorderLayoutManager : public LayoutManager
{
public:
    virtual void addWidget(std::shared_ptr<Widget> widget) override
    {
        getHtmlPage().getWidgets().push_back(widget);
    }

    virtual void render() override
    {
        std::string html = renderHtmlFromWidgets();
        getHtmlPage().setHtmlCode(html);
    }

private:
    std::string renderHtmlFromWidgets()
    {
        return std::string("HTML-Code for BorderLayoutManager");
    }
};

class BoxLayoutManager : public LayoutManager
{
public:
    virtual void addWidget(std::shared_ptr<Widget> widget) override
    {
        getHtmlPage().getWidgets().push_back(widget);
    }

    virtual void render() override
    {
        std::string html = renderHtmlFromWidgets();
        getHtmlPage().setHtmlCode(html);
    }

private:
    std::string renderHtmlFromWidgets()
    {
        return std::string("HTML-Code for BoxLayoutManager");
    }
};

void test_layout_manager_example()
{
    std::string widgetHtmlCode = "Widget HTML Code";

    std::list<std::shared_ptr<Widget>> widgets;

    for (int i = 0; i < 5; i++)
    {
        widgets.push_back(std::make_shared<Widget>(widgetHtmlCode));
    }

    Layouter layouter(widgets);

    layouter.doLayout(BorderLayoutManager());
    layouter.printLayoutedHtmlCode();

    layouter.doLayout(BoxLayoutManager());
    layouter.printLayoutedHtmlCode();

    layouter.doLayout(FlowLayoutManager());
    layouter.printLayoutedHtmlCode();
}
