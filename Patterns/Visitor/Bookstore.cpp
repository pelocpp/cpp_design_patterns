// ===========================================================================
// Bookstore.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <variant>
#include <initializer_list>
#include <vector>

namespace Bookstore_Example {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double m_price;
        size_t m_count;

    public:
        Book(std::string author, std::string title, double price, size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count } { }

        // getter / setter
        std::string getAuthor() const { return m_author; }
        std::string getTitle() const { return m_title; }
        double getPrice() const { return m_price; }
        size_t getCount() const { return m_count; }
    };

    class Movie
    {
    private:
        std::string m_title;
        std::string m_director;
        double m_price;
        size_t m_count;

    public:
        Movie(std::string title, std::string director, double price, size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count } { }

        // getter / setter
        std::string getTitle() const { return m_title; }
        std::string getDirector() const { return m_director; }
        double getPrice() const { return m_price; }
        size_t getCount() const { return m_count; }
    };

    template <typename ... TMedia>
    class Bookstore
    {
    private:
        using Stock = std::vector<std::variant<TMedia ...>>;
        using StockList = std::initializer_list<std::variant<TMedia ...>>;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        // template member method
        template <typename T>
        void addMedia(const T& media) {
            m_stock.push_back(media);
        }

        double totalBalance() {

            double total{};

            for (const auto& media : m_stock) {

                double price{};
                size_t count{};

                std::visit(
                    [&](const auto& element) {
                        price = element.getPrice();
                        count = element.getCount();
                    },
                    media
                );

                total += price * count;
            }

            return total;
        }

        size_t count() {

            size_t total{};

            for (const auto& element : m_stock) {

                size_t count{};

                std::visit(
                    [&](const auto& element) {
                        count = element.getCount();
                    },
                    element
                );

                total += count;
            }

            return total;
        }

        // -----------------------------------------------
        // demonstrating std::visit with returning a value

        double totalBalanceEx() {

            double total{};

            for (const auto& media : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        double price = element.getPrice();
                        size_t count = element.getCount();
                        return price * count;
                    },
                    media
                );
            }

            return total;
        }

        size_t countEx() {

            size_t total{};

            for (const auto& element : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        return element.getCount();
                    },
                    element
                );
            }

            return total;
        }

    private:
        Stock m_stock;
    };

    static void clientCode_01() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Book javaBook{"Java", "James Gosling", 17.99, 21 };
        Book cppBook{"C++", "Bjarne Stroustrup", 16.99, 4 };
        Book csharpBook{"C#", "Anders Hejlsberg", 21.99, 8 };

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore = MyBookstore {
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::cout << "Total value of Bookstore: " << balance << std::endl;
        size_t count{ bookstore.count() };
        std::cout << "Count of elements in Bookstore: " << count << std::endl;
    }

    static void clientCode_02() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 1 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 1 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore = MyBookstore{
            cBook, movieBond
        };

        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 1 };
        bookstore.addMedia(csharpBook);

        size_t count{ bookstore.count() };
        std::cout << "Count of elements in Bookstore: " << count << std::endl;
    }
}

void test_bookstore_example()
{
    using namespace Bookstore_Example;
    clientCode_01();
    clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
