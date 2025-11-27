// ===========================================================================
// GeneratingPasswords.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <array>
#include <random>

class PasswordGenerator
{
public:
    virtual ~PasswordGenerator() {}

    virtual std::string generate(std::default_random_engine&) const = 0;
    virtual std::string allowedChars() const = 0;
    virtual size_t length() const = 0;
    virtual void add(std::unique_ptr<PasswordGenerator>) = 0;
    virtual void clear() = 0;
};

class BasicPasswordGenerator : public PasswordGenerator
{
private:
    size_t m_len;

public:
    explicit BasicPasswordGenerator(size_t len) noexcept : m_len{ len } {}

    virtual std::string generate(std::default_random_engine& engine) const override
    {
        std::string chars = allowedChars();

        std::uniform_int_distribution<> ud{ 0, static_cast<int>(chars.length() - 1) };

        std::string password{};

        for (size_t i{}; i != length(); ++i)
            password += chars[ud(engine)];

        return password;
    }

    // role as 'composite' not supported
    virtual void add(std::unique_ptr<PasswordGenerator>) override
    {
        throw std::runtime_error("not implemented");
    }

    // role as 'composite' not supported
    virtual void clear() override
    {
        throw std::runtime_error("not implemented");
    }

    virtual size_t length() const override final
    {
        return m_len;
    }
};

class DigitGenerator : public BasicPasswordGenerator
{
public:
    explicit DigitGenerator(size_t len) noexcept
        : BasicPasswordGenerator{ len } {}

    virtual std::string allowedChars() const override
    {
        return std::string("0123456789");
    }
};

class SymbolGenerator : public BasicPasswordGenerator
{
public:
    explicit SymbolGenerator(size_t len) noexcept
        : BasicPasswordGenerator{ len } {}

    virtual std::string allowedChars() const override
    {
        return std::string("!@#$%^&*(){}[]?<>");
    }
};

class UpperLetterGenerator : public BasicPasswordGenerator
{
public:
    explicit UpperLetterGenerator(size_t len) noexcept
        : BasicPasswordGenerator{ len } {}

    virtual std::string allowedChars() const override
    {
        return std::string("ABCDEFGHIJKLMNOPQRSTUVXYWZ");
    }
};

class LowerLetterGenerator : public BasicPasswordGenerator
{
public:
    explicit LowerLetterGenerator(size_t len) noexcept
        : BasicPasswordGenerator{ len } {}

    virtual std::string allowedChars() const override
    {
        return std::string("abcdefghijklmnopqrstuvxywz");
    }
};

class CompositePasswordGenerator : public PasswordGenerator
{
private:
    std::vector<std::unique_ptr<PasswordGenerator>> m_generators;

private:
    virtual std::string allowedChars() const override
    {
        throw std::runtime_error("not implemented");
    };

    virtual size_t length() const override
    {
        throw std::runtime_error("not implemented");
    };

public:
    CompositePasswordGenerator() {}

    virtual std::string generate(std::default_random_engine& engine) const override
    {
        std::string password{};

        for (const auto& generator : m_generators) {
            password += generator->generate(engine);
        }

        std::shuffle(std::begin(password), std::end(password), engine);

        return password;
    }

    virtual void add(std::unique_ptr<PasswordGenerator> generator) override
    {
        m_generators.push_back(std::move(generator));
    }

    virtual void clear() override
    {
        m_generators.clear();
    }
};

void generating_passwords() {
    //std::random_device rd;
    std::mt19937 engine;
    std::string password;

    // in case of using 'seed'
    // auto seed_data = std::array<int, std::mt19937::state_size> {};
    // std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    // std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    // engine.seed(seq);

    // using 'leaf' components directly
    std::unique_ptr<PasswordGenerator> digitGen = std::make_unique<DigitGenerator>(4);
    password = digitGen->generate(engine);
    std::cout << "DigitGenerator:       " << password << std::endl;

    std::unique_ptr<PasswordGenerator> symbolGen = std::make_unique<SymbolGenerator>(6);
    password = symbolGen->generate(engine);
    std::cout << "SymbolGenerator:      " << password << std::endl;

    std::unique_ptr<PasswordGenerator> upperLetterGen = std::make_unique<UpperLetterGenerator>(8);
    password = upperLetterGen->generate(engine);
    std::cout << "UpperLetterGenerator: " << password << std::endl;

    std::unique_ptr<PasswordGenerator> lowerLetterGen = std::make_unique<LowerLetterGenerator>(10);
    password = lowerLetterGen->generate(engine);
    std::cout << "LowerLetterGenerator: " << password << std::endl << std::endl;

    // using 'composite' component
    // here: using some of the available 'leaf' components
    CompositePasswordGenerator compositeGenerator;
    compositeGenerator.add(std::make_unique<UpperLetterGenerator>(8));
    compositeGenerator.add(std::make_unique<LowerLetterGenerator>(8));
    password = compositeGenerator.generate(engine);
    compositeGenerator.clear();
    std::cout << "CompositeGenerator:   " << password << std::endl;

    // using 'composite' component
    // here: using all of the available 'leaf' components
    compositeGenerator.add(std::make_unique<SymbolGenerator>(4));
    compositeGenerator.add(std::make_unique<DigitGenerator>(4));
    compositeGenerator.add(std::make_unique<UpperLetterGenerator>(4));
    compositeGenerator.add(std::make_unique<LowerLetterGenerator>(4));

    password = compositeGenerator.generate(engine);
    std::cout << "CompositeGenerator:   " << password << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
