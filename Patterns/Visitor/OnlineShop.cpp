// ===========================================================================
// OnlineShop.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <memory>

namespace OnlineShopExample {

    class Visitor
    {
    public:
        virtual ~Visitor() {}

        // note: implicit forward declarations
        virtual void visit(const class Book*) = 0;
        virtual void visit(const class Movie*) = 0;
        virtual void visit(const class Game*) = 0;

        // other names (e.g. no method overloading) is also possible
        // virtual void visitBook(const class Book*) = 0;
        // virtual void visitMovie(const class Movie*) = 0;
        // virtual void visitGame(const class Game*) = 0;
    };

    class Element
    {
    protected:
        int m_count;
        double m_price;
        std::string m_title;

    public:
        // c'tor
        Element(int count, double price, std::string title) :
            m_count{ count }, m_price{ price }, m_title{title } {}

        // getter / setter
        int getCount() const { return m_count; }
        double getPrice() const { return m_price; }
        std::string getTitle() const { return m_title; }

        virtual void accept(Visitor& visitor) const = 0;
    };

    class Book : public Element
    {
    private:
        std::string m_ISBN;
        std::string m_author;
        std::string m_publisher;

    public:
        Book(int count, double price, std::string title)
            : Element{ count, price, title } { }

        // getter / setter
        std::string getISBN() const { return m_ISBN; }
        std::string getAuthor() const { return m_author; }
        std::string getPublisher() const { return m_publisher; }
        void setISBN(std::string isbn) { m_ISBN = isbn; }
        void setAuthor(std::string author) { m_author = author; }
        void setPublisher(std::string publisher) { m_publisher = publisher; }

        void accept(Visitor& visitor) const override
        {
            visitor.visit(this);
        }
    };

    class Movie : public Element
    {
    private:
        long m_length;
        bool m_isHD;
        std::string m_director;

    public:
        Movie(long count, double price, std::string title)
            : Element{ count, price, title }
        {
            m_length = 0;
            m_isHD = false;
            m_director = "";
        }

        // getter / setter
        long getLength() const { return m_length; }
        double getIsHD() const { return m_isHD; }
        std::string getDirector() const { return m_director; }
        void setLength(long length) { m_length = length; }
        void setIsHD(bool isHD) { m_isHD = isHD; }
        void setDirector(std::string director) { m_director = director; }

        void accept(Visitor& visitor) const override
        {
            visitor.visit(this);
        }
    };

    class Game : public Element
    {
    private:
        int m_consoleType;
        std::string m_licenseKey;

    public:
        Game(int count, double price, std::string title)
            : Element{ count, price, title }
        {
            m_consoleType = 0;
            m_licenseKey = "";
        }

        // getter / setter
        int getConsoleType() const { return m_consoleType; }
        std::string getLicenseKey() const { return m_licenseKey; }
        void setConsoleType(int consoleType) { m_consoleType = consoleType; }
        void setLicenseKey(std::string licenseKey) { m_licenseKey = licenseKey; }

        void accept(Visitor& visitor) const override
        {
            visitor.visit(this);
        }
    };

    // =======================================================================
    // DATEN ... loose Kopplung ... Prinzip
    // -----------------------------------------------------------------------
    // OPERATIONEN ... greifen auf die Daten zu
    // =======================================================================

    class CalculatePriceVisitor : public Visitor
    {
    private:
        double m_totalPrice;

    public:
        CalculatePriceVisitor() : m_totalPrice{ 0.0 } {}

        double getTotalPrice() { return m_totalPrice; }

        void visit(const Book* book) override
        {
            m_totalPrice += book->getPrice() * book->getCount();
        }

        void visit(const Movie* movie) override
        {
            m_totalPrice += movie->getPrice() * movie->getCount();
        }

        void visit(const Game* game) override
        {
            m_totalPrice += game->getPrice() * game->getCount();
        }
    };

    class HTMLVisitor : public Visitor
    {
    private:
        std::string m_html;

    public:
        HTMLVisitor() : m_html{ } {}

        std::string getHTML() { return m_html; }

        void visit(const Book* book) override
        {
            m_html = "<b>" + book->getTitle() + "</b> Author: " + book->getAuthor();
        }

        void visit(const Movie* movie) override
        {
            m_html = "<b>" + movie->getTitle() + "</b> Director: " + movie->getDirector();
        }

        void visit(const Game* game) override
        {
            m_html = "<b>" + game->getTitle() + "</b> License Key: " + game->getLicenseKey();
        }
    };

    class ShoppingBasket
    {
    private:
        std::list<std::shared_ptr<Element>> m_products;

    public:
        ShoppingBasket() {}

        std::list<std::shared_ptr<Element>> GetProducts()
        {
            return m_products;
        }

        void addElement(std::shared_ptr<Element> element)
        {
            m_products.push_back(element);
        }

        double calculateTotalPrice()
        {
            CalculatePriceVisitor priceVisitor;

            for (std::shared_ptr<Element> element : m_products)
            {
                element->accept(priceVisitor);
            }

            double totalPrice{ priceVisitor.getTotalPrice() };
            return totalPrice;
        }

        std::string toHTML()
        {
            HTMLVisitor htmlVisitor;
            std::string htmlResult{ "<!doctype html>\n<html>\n<head>\n</head>\n<body>\n" };

            for (std::shared_ptr<Element> element : m_products)
            {
                element->accept(htmlVisitor);
                htmlResult += "    "  + htmlVisitor.getHTML() + '\n';
            }

            htmlResult += "</body>\n</html>";
            return htmlResult;
        }
    };

    static void clientCode()
    {
        ShoppingBasket basket;

        std::shared_ptr<Book> book{ std::make_shared<Book>(1, 10.0f, "The C Programming Language") };
        book->setAuthor("Brian Kernighan / Dennis Ritchie");

        std::shared_ptr<Game> game{ std::make_shared<Game>(3, 5.0f, "Tetris") };
        game->setLicenseKey("12345678");

        std::shared_ptr<Movie> movie{ std::make_shared<Movie>(3, 19.99f, "Once upon a time in Hollywood") };
        movie->setDirector("Quentin Tarantino");

        basket.addElement(book);
        basket.addElement(game);
        basket.addElement(movie);

        double totalPrice{ basket.calculateTotalPrice() };
        std::cout << "OnlineShop Example:" << std::endl;
        std::cout << "Price: " << totalPrice << std::endl;

        std::string html{ basket.toHTML() };
        std::cout << "ShoppingBasket in HTML: " << totalPrice << std::endl;
        std::cout << html << std::endl;
    }
}

void test_onlineshop_example() {

    using namespace OnlineShopExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
