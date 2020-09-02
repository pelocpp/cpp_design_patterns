// ===========================================================================
// OnlineShop.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <list>

namespace OnlineShopExample {

    class Visitor
    {
    public:
        // note: implicit forward declarations
        virtual void visit(const class Book*) = 0;
        virtual void visit(const class Movie*) = 0;
        virtual void visit(const class Game*) = 0;
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
            m_count(count), m_price(price), m_title(title) {}

        // getter / setter
        int getCount() const { return m_count; }
        double getPrice() const { return m_price; }
        std::string getTitle() const { return m_title; }

        virtual void accept(Visitor* visitor) const = 0;
    };

    class Book : public Element
    {
    private:
        std::string m_ISBN;
        std::string m_author;
        std::string m_publisher;

    public:
        Book(int count, double price, std::string title)
            : Element(count, price, title) { }

        // getter / setter
        std::string getISBN() const { return m_ISBN; }
        std::string getAuthor() const { return m_author; }
        std::string getPublisher() const { return m_publisher; }
        void setISBN(std::string isbn) { m_ISBN = isbn; }
        void setAuthor(std::string author) { m_author = author; }
        void setPublisher(std::string publisher) { m_publisher = publisher; }

        virtual void accept(Visitor* visitor) const override
        {
            visitor->visit(this);
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
            : Element(count, price, title)
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

        virtual void accept(Visitor* visitor) const override
        {
            visitor->visit(this);
        }
    };

    class Game : public Element
    {
    private:
        int m_consoleType;
        std::string m_licenseKey;

    public:
        Game(int count, double price, std::string title)
            : Element(count, price, title)
        {
            m_consoleType = 0;
            m_licenseKey = "";
        }

        // getter / setter
        int getConsoleType() const { return m_consoleType; }
        std::string getLicenseKey() const { return m_licenseKey; }
        void setConsoleType(int consoleType) { m_consoleType = consoleType; }
        void setLicenseKey(std::string licenseKey) { m_licenseKey = licenseKey; }

        virtual void accept(Visitor* visitor) const override
        {
            visitor->visit(this);
        }
    };

    class CalculatePriceVisitor : public Visitor
    {
    private:
        double m_totalPrice;

    public:
        CalculatePriceVisitor() : m_totalPrice(0.0) {}

        double getPrice() { return m_totalPrice; }

        virtual void visit(const Book* book) override
        {
            m_totalPrice += book->getPrice() * book->getCount();
        }

        virtual void visit(const Movie* movie) override
        {
            m_totalPrice += movie->getPrice() * movie->getCount();
        }

        virtual void visit(const Game* game) override
        {
            m_totalPrice += game->getPrice() * game->getCount();
        }
    };

    class HTMLVisitor : public Visitor
    {
    private:
        std::string m_html;

    public:
        HTMLVisitor() : m_html("") {}

        std::string getHTML() { return m_html; }

        virtual void visit(const Book* book) override
        {
            m_html = "<b>" + book->getTitle() + "</b> Author: " + book->getAuthor();
        }

        virtual void visit(const Movie* movie) override
        {
            m_html = "<b>" + movie->getTitle() + "</b> Director: " + movie->getDirector();
        }

        virtual void visit(const Game* game) override
        {
            m_html = "<b>" + game->getTitle() + "</b> License Key: " + game->getLicenseKey();
        }
    };

    class ShoppingBasket
    {
    private:
        std::list<Element*> m_products;

    public:
        ShoppingBasket() = default;

        std::list<Element*> GetProdukte()
        {
            return m_products;
        }

        void addElement(Element* element)
        {
            m_products.push_back(element);
        }

        double calculateTotalPrice()
        {
            CalculatePriceVisitor* priceVisitor = new CalculatePriceVisitor();

            for (Element* element : m_products)
            {
                element->accept(priceVisitor);
            }

            double totalPrice = priceVisitor->getPrice();
            delete priceVisitor;
            return totalPrice;
        }

        std::string toHTML()
        {
            HTMLVisitor* htmlVisitor = new HTMLVisitor();
            std::string htmlResult = "<!doctype html>\n<html>\n<head>\n</head>\n<body>\n";

            for (Element* element : m_products)
            {
                element->accept(htmlVisitor);
                htmlResult += "    "  + htmlVisitor->getHTML() + '\n';
            }

            delete htmlVisitor;

            htmlResult += "</body>\n</html>";
            return htmlResult;
        }
    };

    void clientCode()
    {
        ShoppingBasket basket;

        Book* book = new Book(1, 10.0f, "The C Programming Language");
        book->setAuthor("Brian Kernighan / Dennis Ritchie");

        Game* game = new Game(3, 5.0f, "Tetris");
        game->setLicenseKey("12345678");

        Movie* movie = new Movie(3, 19.99f, "Once upon a time in Hollywood");
        movie->setDirector("Quentin Tarantino");

        basket.addElement(book);
        basket.addElement(game);
        basket.addElement(movie);

        double totalPrice = basket.calculateTotalPrice();
        std::cout << "OnlineShop Example:" << std::endl;
        std::cout << "Price: " << totalPrice << std::endl;

        std::string html = basket.toHTML();
        std::cout << "ShoppingBasket in HTML: " << totalPrice << std::endl;
        std::cout << html << std::endl;

        delete book;
        delete game;
        delete movie;
    }
}

void test_onlineshop_example() {

    using namespace OnlineShopExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
