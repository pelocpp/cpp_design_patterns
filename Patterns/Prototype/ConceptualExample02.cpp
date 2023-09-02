// ===========================================================================
// ConceptualExample02.cpp // Prototype Pattern am Beispiel eines Schachbretts
// ===========================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <type_traits>
#include <vector>
#include <memory>

// König -    King
// Dame -     Queen
// Turm -     Rook
// Läufer -   Bishop
// Springer - Knight
// Bauer -    Pawn

namespace ExamplesPrototypePattern {

    class IChessPiece
    {
    public:
        virtual ~IChessPiece() {};

        virtual std::unique_ptr<IChessPiece> clone() const = 0;
        virtual std::string str() const = 0;
    };

    // -----------------------------------------------------------------------

    class ChessPiece : public IChessPiece
    {
    private:
        std::string m_name;

    protected:
        ChessPiece(std::string name) : m_name{ name } {}

    public:
        std::string str() const override final {
            return m_name;
        }
    };

    // -----------------------------------------------------------------------

    class King : public ChessPiece
    {
    public:
        King() : ChessPiece{ "King" } {}

        std::unique_ptr<IChessPiece> clone() const override {
            return std::make_unique<King>(*this);
        }
    };

    // -----------------------------------------------------------------------

    class Pawn : public ChessPiece
    {
    public:
        Pawn() : ChessPiece{ "Pawn" } {}

        std::unique_ptr<IChessPiece> clone() const override {
            return std::make_unique<Pawn>(*this);
        }
    };

    // -----------------------------------------------------------------------

    class Rook : public ChessPiece
    {
    public:
        Rook() : ChessPiece{ "Rook" } {}

        std::unique_ptr<IChessPiece> clone() const override {
            return std::make_unique<Rook>(*this);
        }
    };

    // -----------------------------------------------------------------------

    class GameBoard
    {
        friend std::ostream& operator<< (std::ostream&, const GameBoard&);

    public:
        GameBoard();                       // default c'tor
        GameBoard(const GameBoard&);       // copy c'tor

        virtual ~GameBoard() {};           // virtual defaulted d'tor

        GameBoard& operator=(const GameBoard&);   // assignment operator

        std::unique_ptr<IChessPiece>& at(size_t, size_t);
        const std::unique_ptr<IChessPiece>& at(size_t, size_t) const;

        static constexpr size_t DefaultWidth = 4;
        static constexpr size_t DefaultHeight = 4;

    private:
        std::vector<std::vector<std::unique_ptr<IChessPiece>>> m_cells;
    };

    GameBoard::GameBoard()
    {
        m_cells.resize(DefaultWidth);
        for (auto& row : m_cells) {
            row.resize(DefaultHeight);
        }
    }

    GameBoard::GameBoard(const GameBoard& other) : GameBoard()
    {
        // need to redirect to default c'tor at first 
        // to allocate the proper amount of memory

        // now copy the data
        for (size_t i = 0; i != m_cells.size(); ++i) {
            for (size_t j = 0; j != m_cells[i].size(); ++j) {
                if (other.m_cells[i][j]) {

                    // compiler error
                    // m_cells[i][j] = other.m_cells[i][j];
                    // m_cells[i][j] = std::make_unique<ChessPiece>(*other.m_cells[i][j]);

                    m_cells[i][j] = other.m_cells[i][j]->clone();
                }
            }
        }
    }

    GameBoard& GameBoard::operator=(const GameBoard& other) {

        // check for self-assignment
        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i != m_cells.size(); ++i) {
            for (size_t j = 0; j != m_cells[i].size(); ++j) {
                if (other.m_cells[i][j] != nullptr) {

                    // compiler error
                    // m_cells[i][j] = other.m_cells[i][j];
                    // m_cells[i][j] = std::make_unique<ChessPiece>(*other.m_cells[i][j]);

                    m_cells[i][j] = other.m_cells[i][j]->clone();
                }
            }
        }

        return *this;
    }

    std::unique_ptr<IChessPiece>& GameBoard::at(size_t x, size_t y)
    {
        return m_cells[x][y];
    }

    const std::unique_ptr<IChessPiece>& GameBoard::at(size_t x, size_t y) const
    {
        return m_cells[x][y];
    }

    std::ostream& operator<< (std::ostream& os, const GameBoard& board) {

        for (const auto& row : board.m_cells) {
            for (const auto& cell : row) {
                if (cell != nullptr) {
                    std::cout << std::setw(8) << std::left << cell->str();
                }
                else {
                    std::cout << std::setw(8) << std::left << "<empty>";
                }

            }
            std::cout << std::endl;
        }

        return os;
    }

    // ========================================================================
}

void test_prototype_pattern_chess_01()
{
    using namespace ExamplesPrototypePattern;

    King king;
    std::cout << king.str() << std::endl;
}

void test_prototype_pattern_chess_02()
{
    using namespace ExamplesPrototypePattern;

    GameBoard board;

    board.at(0, 0) = std::make_unique<King>();
    board.at(0, 1) = std::make_unique<Pawn>();
    board.at(1, 0) = std::make_unique<Pawn>();
    board.at(1, 1) = std::make_unique<Rook>();

    std::cout << board << std::endl;

    GameBoard boardCopy;
    boardCopy = board;
    std::cout << boardCopy << std::endl;

    GameBoard secondBoardCopy{ board };
    std::cout << secondBoardCopy << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
