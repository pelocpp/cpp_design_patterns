// ===========================================================================
// MotivationDocumentHtmlMarkdown.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <type_traits>
#include <variant>

namespace MotivationVisitor_01_Starting_Point
{
    class Document
    {
    public:
        virtual void addToList(const std::string& line) = 0;
    };

    class Markdown : public Document
    {
    private:
        std::string m_start;
        std::list<std::string> m_content;

    public:
        Markdown() : m_start{ "* " } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }
    };

    class HTML : public Document
    {
    private:
        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;

    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }
    };
}

namespace MotivationVisitor_02_Intrusive
{
    class Document
    {
    public:
        virtual void addToList(const std::string& line) = 0;
        virtual void print() = 0;
    };

    class Markdown : public Document
    {
    public:
        Markdown() : m_start{ "* " } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }

        virtual void print() override {
            for (const std::string& item : m_content) {
                std::cout << m_start << item << std::endl;
            }
        }

    private:
        std::string m_start;
        std::list<std::string> m_content;
    };

    class HTML : public Document
    {
    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }

        virtual void print() override {
            std::cout << "<ul>" << std::endl;
            for (const std::string& item : m_content) {
                std::cout << "    " << m_start << item << m_end << std::endl;
            }
            std::cout << "</ul>" << std::endl;
        }

    private:
        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;
    };

    static void clientCode02()
    {
        Document * d1 = new HTML;
        d1->addToList("This is line");
        d1->print();

        Document * d2 = new Markdown;
        d2->addToList("This is another line");
        d2->print();

        delete d1;
        delete d2;
    }
}

namespace MotivationVisitor_03_Reflective
{
    class Document
    {
    public:
        virtual void addToList(const std::string& line) = 0;
    };

    class Markdown : public Document
    {
    friend class DocumentPrinter;

    public:
        Markdown() : m_start{ "* " } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }

    private:
        std::string m_start;
        std::list<std::string> m_content;
    };

    class HTML : public Document
    {
    friend class DocumentPrinter;

    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }

    private:
        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;
    };

    class DocumentPrinter
    {
    public:
        static void print(Document* e) {
            if (auto md = dynamic_cast<Markdown*>(e)) {
                for (const std::string& item : md->m_content)
                    std::cout << md->m_start << item << std::endl;
            }
            else if (auto hd = dynamic_cast<HTML*>(e)) {
                std::cout << "<ul>" << std::endl;
                for (const std::string& item : hd->m_content) {
                    std::cout << "    " << hd->m_start << item << hd->m_end << std::endl;
                }
                std::cout << "</ul>" << std::endl;
            }
        }
    };

    static void clientCode03() {

        Document * d1 = new HTML;
        d1->addToList("This is line");
        DocumentPrinter::print(d1);
   
        Document * d2 = new Markdown;
        d2->addToList("This is another line");
        DocumentPrinter::print(d2);
   
        delete d1;
        delete d2;
    }
}

namespace MotivationVisitor_04_Classical_Visitor_Pattern
{
    // ---------------------------------------------
    // Generic Visitor Classes

    class Markdown;
    class HTML;

    class DocumentVisitor
    {
    public:
        virtual void visit(Markdown*) = 0;
        virtual void visit(HTML*) = 0;
    };

    // ---------------------------------------------
    // Document Classes Hierarchy
    
    class Document
    {
    public:
        virtual void addToList(const std::string& line) = 0;
        virtual void accept(DocumentVisitor*) = 0;    // <<<<<
    };

    class Markdown : public Document
    {
    public:
        Markdown() : m_start{ "* " } {}

        virtual void addToList(const std::string& line) override { 
            m_content.push_back(line);
        }

        virtual void accept(DocumentVisitor* dv) override {  // <<<<<
            dv->visit(this);
        } 

        std::string m_start;
        std::list<std::string> m_content;
    };

    class HTML : public Document
    {
    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        virtual void addToList(const std::string& line) override {
            m_content.push_back(line);
        }

        virtual void accept(DocumentVisitor* dv) override {    // <<<<<
            dv->visit(this);
        } 

        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;
    };

    // ---------------------------------------------
    // Specific Printer Visitor Class

    class DocumentPrinter : public DocumentVisitor
    {
    public:
        virtual void visit(Markdown* md) override;
        virtual void visit(HTML* hd) override;
    };

    void DocumentPrinter::visit(Markdown* md) {
        for (const std::string& item : md->m_content)
            std::cout << md->m_start << item << std::endl;
    }

    void DocumentPrinter::visit(HTML* hd) {
        std::cout << "<ul>" << std::endl;
        for (const std::string& item : hd->m_content)
            std::cout << "    " << hd->m_start << item << hd->m_end << std::endl;
        std::cout << "</ul>" << std::endl;
    }

    static void clientCode04()
    {
        DocumentVisitor* dp = new DocumentPrinter();

        Document* d1 = new HTML;
        d1->addToList("This is line");
        d1->accept(dp);

        Document* d2 = new Markdown;
        d2->addToList("This is another line");
        d2->accept(dp);

        delete d1;
        delete d2;
        delete dp;
    }
}

// ===========================================================================

namespace MotivationVisitor_05_Modern_Cpp
{
    /* ------ Document Classes -------- */
    class Markdown
    {
    private:
        std::string m_start;
        std::list<std::string> m_content;

    public:
        Markdown() : m_start{ "* " } {}

        void addToList(const std::string& line) {
            m_content.push_back(line);
        }

        std::string getStart() const { return m_start; }
        std::list<std::string> getContent() const { return m_content; }
    };

    class HTML
    {
    private:
        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;

    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        void addToList(const std::string& line) {
            m_content.push_back(line);
        }

        std::string getStart() const { return m_start; }
        std::string getEnd() const { return m_end; }
        std::list<std::string> getContent() const { return m_content; }
    };

    /* ------ Specific Printer Visitor Class -------- */
    class DocumentPrinter
    {
    public:
        void operator() (const Markdown& md) {
            for (const std::string& item : md.getContent()) {
                std::cout << md.getStart() << item << std::endl;
            }
        }

        void operator() (const HTML& hd) {
            std::cout << "<ul>" << std::endl;
            for (const std::string& item : hd.getContent()) {
                std::cout << "    " << hd.getStart() << item << hd.getEnd() << std::endl;
            }
            std::cout << "</ul>" << std::endl;
        }
    };

    /* ------ std::variant & std::visit -------- */
    static void clientCode05() {
        HTML hd;
        hd.addToList("This is line");
        std::variant<Markdown, HTML> doc = hd;
        DocumentPrinter dp;
        std::visit(dp, doc);

        Markdown md;
        md.addToList("This is another line");
        doc = md;
        std::visit(dp, doc);
    }
}

// ===========================================================================

namespace MotivationVisitor_06_Much_More_Modern_Cpp
{
    /* ------ Document Classes -------- */
    class Markdown
    {
    private:
        std::string m_start;
        std::list<std::string> m_content;

    public:
        Markdown() : m_start{ "* " } {}

        void addToList(const std::string& line) {
            m_content.push_back(line); 
        }

        std::string getStart() const { return m_start; }
        std::list<std::string> getContent() const { return m_content; }
    };

    class HTML
    {
    private:
        std::string m_start;
        std::string m_end;
        std::list<std::string> m_content;

    public:
        HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}

        void addToList(const std::string& line) {
            m_content.push_back(line); 
        }

        std::string getStart() const { return m_start; }
        std::string getEnd() const { return m_end; }
        std::list<std::string> getContent() const { return m_content; }
    };

    /* ------ std::variant & std::visit & Generic Lambda -------- */
    static void clientCode06() {

        auto genericVisitor = [](const auto& doc) {

            using DocumentType = decltype (doc);

            using DocumentTypeWithoutRef = std::remove_reference<DocumentType>::type;

            using DocumentTypeWithoutRefAndConst
                = std::remove_const<DocumentTypeWithoutRef>::type;

            if constexpr (std::is_same<DocumentTypeWithoutRefAndConst, HTML>::value == true)
            {
                std::cout << "<ul>" << std::endl;
                for (const std::string& item : doc.getContent()) {
                    std::cout << "    " << doc.getStart() << item << doc.getEnd() << std::endl;
                }
                std::cout << "</ul>" << std::endl;
            }
            else if constexpr (std::is_same<DocumentTypeWithoutRefAndConst, Markdown>::value == true)
            {
                for (const std::string& item : doc.getContent()) {
                    std::cout << doc.getStart() << item << std::endl;
                }
            }
            else
            {
                std::cout << "Unknown Document Format! " << std::endl;
            }
        };

        HTML hd;
        hd.addToList("This is line");
        std::variant<Markdown, HTML> var{ hd };
        std::visit(genericVisitor, var);

        Markdown md;
        md.addToList("This is another line");
        var = md;
        std::visit(genericVisitor, var);
    }
}

void test_motivation_example()
{
    using namespace MotivationVisitor_02_Intrusive;
    clientCode02();
    using namespace MotivationVisitor_03_Reflective;
    clientCode03();
    using namespace MotivationVisitor_04_Classical_Visitor_Pattern;
    clientCode04();
    using namespace MotivationVisitor_05_Modern_Cpp;
    clientCode05();
    using namespace MotivationVisitor_06_Much_More_Modern_Cpp;
    clientCode06();
}

// ===========================================================================
// End-of-File
// ===========================================================================
