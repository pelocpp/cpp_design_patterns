// ===========================================================================
// Semigraphics.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <unordered_map>
#include <random>

// ===========================================================================

class Character
{
private:
    std::string m_color;
    std::string m_font;

public:
    // c'tor(s), d'tor
    Character() = default;
    virtual ~Character() = default;
    Character(const std::string& color, const std::string& font)
        : m_color{ color }, m_font{ font } {}

    // getter
    std::string getColor() const { return m_color; }
    std::string getFont() const { return m_font; }

    friend std::ostream& operator<<(std::ostream&, const Character&);
};

std::ostream& operator<<(std::ostream& os, const Character& ch)
{
    return os << "[ Color: " << ch.m_color << " - Font: " << ch.m_font << "]";
}

// ===========================================================================

class ConcreteCharacter
{
private:
    std::shared_ptr<Character> m_sharedState;

public:
    ConcreteCharacter() = default;
    explicit ConcreteCharacter(const std::shared_ptr<Character>& state) 
        : m_sharedState{ state } {}
    ~ConcreteCharacter() = default;

    void render(int x, int y) const noexcept;
    friend std::ostream& operator<<(std::ostream&, const ConcreteCharacter&);
};

void ConcreteCharacter::render(int x, int y) const noexcept {
    std::cout 
        << "Character: Position (" << x << ", " << y <<
        ") with shared state " << *m_sharedState << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ConcreteCharacter& cc)
{
    return os << "[ConcreteCharacter: " << *cc.m_sharedState << "]";
}

// ===========================================================================

class CharacterFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<Character>> m_characterMap;

public:
    void addCharacter(const std::string& color, const std::string& font);
    ConcreteCharacter getConcreteCharacter(const std::string& color, const std::string& font);
    std::string getKey(const std::string& color, const std::string& font) const;
    friend std::ostream& operator<<(std::ostream&, const CharacterFactory&);
};

// returns an ConcreteCharacter with a given state or creates a new one
ConcreteCharacter CharacterFactory::getConcreteCharacter(const std::string& color, const std::string& font) {

    std::string key = getKey(color, font);

    if (m_characterMap.find(key) == m_characterMap.end()) {
        std::cout << "CharacterFactory: Can't find this character, creating new one." << std::endl;
        std::shared_ptr<Character> chptr = std::make_shared<Character>(color, font);
        m_characterMap[key] = chptr;
    }
    else {
        std::cout << "CharacterFactory: Reusing existing character." << std::endl;
    }

    std::shared_ptr<Character> ptr = m_characterMap.at(key);
    return ConcreteCharacter(ptr);
}


std::string CharacterFactory::getKey(const std::string& color, const std::string& font) const
{
    return color + "_" + font;     // returns a hash for a given intrinsic state
}

void CharacterFactory::addCharacter(const std::string& color, const std::string& font)
{
    std::string key = getKey(color, font);
    m_characterMap[key] = std::make_shared<Character>(color, font);;
}

std::ostream& operator<<(std::ostream& os, const CharacterFactory& factory) {
    size_t count = factory.m_characterMap.size();
    os << "CharacterFactory: " << count << " characters:" << std::endl;

    for (std::pair<std::string, std::shared_ptr<Character>> ch : factory.m_characterMap) {
        os << ch.first << " => " << *ch.second << std::endl;
    }

    return os;
}

// ===========================================================================

class CharacterClient {
private:
    std::array<std::string, 7> m_colors;
    std::array<std::string, 3> m_fonts;
    std::default_random_engine m_engine{};
    std::uniform_int_distribution<int> m_colorsDistribution{ 0, static_cast<int>(m_colors.size()) - 1 };
    std::uniform_int_distribution<int> m_fontsDistribution{ 0, static_cast<int>(m_fonts.size()) - 1 };

public:
    // c'tor
    CharacterClient();

    std::string getRandomColor();
    std::string getRandomFont();
    int getRandomX();
    int getRandomY();
};

CharacterClient::CharacterClient() {
    m_colors = {
        std::string{ "Red" },
        std::string{ "Green" },
        std::string{ "Blue" },
        std::string{ "White" },
        std::string{ "Black" },
        std::string{ "Yellow" },
        std::string{ "Magenta" }
    };

    m_fonts = {
        std::string{ "Arial" },
        std::string{ "Verdana" },
        std::string{ "Roboto" }
    };
}

std::string CharacterClient::getRandomColor() {
    long long int index = m_colorsDistribution(m_engine);
    return m_colors[index];
}

std::string CharacterClient::getRandomFont() {
    long long int index = m_fontsDistribution(m_engine);
    return m_fonts[index];
}

int CharacterClient::getRandomX() {
    return (m_colorsDistribution(m_engine) * 100);
}

int CharacterClient::getRandomY() {
    return (m_colorsDistribution(m_engine) * 100);
}

// ===========================================================================

void initSmallFactory(CharacterFactory& factory)
{
    std::array<std::string, 5> colors = {
        std::string{ "Red" },
        std::string{ "Green" },
        std::string{ "Blue" }
    };

    for (std::string color : colors) {
        factory.addCharacter(color, std::string{ "Arial" });
    }
}

void initLargeFactory(CharacterFactory& factory)
{
    std::array<std::string, 5> colors = {
    std::string{ "Red" },
    std::string{ "Green" },
    std::string{ "Blue" },
    std::string{ "White" },
    std::string{ "Black" }
    };

    std::array<std::string, 3> fonts = {
        std::string{ "Arial" },
        std::string{ "Fixedsys" },
        std::string{ "Roboto" }
    };

    for (std::string color : colors) {
        for (std::string font : fonts) {
            factory.addCharacter(color, font);
        }
    }
}

void testSemigraphics01() {

    CharacterFactory factory;

    initLargeFactory(factory);

    std::cout << factory << std::endl;
}

void testSemigraphics02() {

    CharacterClient client;

    CharacterFactory factory;

    initSmallFactory(factory);
    // or
    // initLargeFactory(factory);

    for (int i = 0; i < 15; i++) {

        std::string color{ client.getRandomColor() };
        std::string font{ client.getRandomFont() };
        ConcreteCharacter cc{ factory.getConcreteCharacter(color, font) };
        cc.render(client.getRandomX(), client.getRandomY());
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
