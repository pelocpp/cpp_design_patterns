// ===========================================================================
// Bookstore.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <variant>
#include <initializer_list>
#include <vector>
#include <print>

namespace Bookstore_ExampleClassic {

    struct IMedia
    {
        virtual ~IMedia() = default;

        virtual double getPrice() const = 0;
        virtual size_t getCount() const = 0;
    };

    class Book : public IMedia
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        size_t      m_count;

    public:
        Book(std::string author, std::string title, double price, size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        std::string getAuthor() const { return m_author; }
        std::string getTitle() const { return m_title; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        size_t getCount() const override { return m_count; }
    };

    class Movie : public IMedia
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        size_t      m_count;

    public:
        Movie(std::string title, std::string director, double price, size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        {
        }

        // getter / setter
        std::string getTitle() const { return m_title; }
        std::string getDirector() const { return m_director; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        size_t getCount() const override { return m_count; }
    };

    class Bookstore
    {
    private:
        using Stock = std::vector<std::shared_ptr<IMedia>>;
        using StockList = std::initializer_list<std::shared_ptr<IMedia>>;

        Stock m_stock;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        void addMedia(const std::shared_ptr<IMedia>& media) {
            m_stock.push_back(media);
        }

        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {
                total += media->getPrice() * media->getCount();
            }

            return total;
        }

        size_t count() const {

            size_t total{};

            for (const auto& media : m_stock) {
                total += media->getCount();
            }

            return total;
        }
    };

    static void clientCodeClassic_01() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> javaBook{ std::make_shared<Book>("Java", "James Gosling", 17.99, 21) };
        std::shared_ptr<IMedia> cppBook{ std::make_shared<Book>("C++", "Bjarne Stroustrup", 16.99, 4) };
        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void clientCodeClassic_02() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{ cBook, movieBond };

        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };
        bookstore.addMedia(csharpBook);

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        bookstore.addMedia(movieTarantino);

        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }
}

namespace Bookstore_ExampleModern {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double m_price;
        size_t m_count;

    public:
        Book(std::string author, std::string title, double price, size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count } {
        }

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
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count } {
        }

        // getter / setter
        std::string getTitle() const { return m_title; }
        std::string getDirector() const { return m_director; }
        double getPrice() const { return m_price; }
        size_t getCount() const { return m_count; }
    };

    template<typename T>
    concept MediaConcept = requires (const T & m)
    {
        { m.getPrice() } -> std::same_as<double>;
        { m.getCount() } -> std::same_as<size_t>;
    };

    template <typename ... TMedia>
        requires (MediaConcept<TMedia> && ...)
    class Bookstore
    {
    private:
        using Stock = std::vector<std::variant<TMedia ...>>;
        using StockList = std::initializer_list<std::variant<TMedia ...>>;

        Stock m_stock;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        // template member method
        template <typename T>
            requires MediaConcept<T>
        void addMedia(const T& media) {
            m_stock.push_back(media);
        }

        // or
        void addMediaEx(const MediaConcept auto& media) {
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
    };

    static void clientCodeModern_01() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Book javaBook{ "Java", "James Gosling", 17.99, 21 };
        Book cppBook{ "C++", "Bjarne Stroustrup", 16.99, 4 };
        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore = MyBookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::cout << "Total value of Bookstore: " << balance << std::endl;
        size_t count{ bookstore.count() };
        std::cout << "Count of elements in Bookstore: " << count << std::endl;
    }

    static void clientCodeModern_02() {

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
    using namespace Bookstore_ExampleClassic;
    clientCodeClassic_01();
    clientCodeClassic_02();

    using namespace Bookstore_ExampleModern;
    clientCodeModern_01();
    clientCodeModern_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
