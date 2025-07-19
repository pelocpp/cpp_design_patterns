// ===========================================================================
// Chess.cpp // Command Pattern
// ===========================================================================

#include <iostream>
#include <queue> 
#include <stack>
#include <stdexcept>
#include <memory>

namespace ChessExample {

    class Position
    {
    private:
        int m_x;
        int m_y;

    public:
        // c'tor(s)
        Position() : m_x{ -1 }, m_y{ -1 } {}
        Position(int x, int y) : m_x{ x }, m_y{ y } {}

        // getter/setter
        int getX() const { return m_x; }
        void setX(int x) { m_x = x; }
        int getY() const { return m_y; }
        void setY(int y) { m_y = y; }
    };

    class ChessPiece
    {
    private:
        bool     m_isComputer;
        Position m_currentPosition;

    public:
        // c'tor(s)
        ChessPiece() : m_isComputer{ false }, m_currentPosition{} {}
        ChessPiece(bool isComputer, const Position& position)
        {
            m_isComputer = isComputer;
            m_currentPosition = position;
        }

        // getter/setter
        const Position& getCurrentPosition() const { return m_currentPosition; }
        void setCurrentPosition(const Position& currentPosition) { m_currentPosition = currentPosition; }

        bool isComputer() const { return m_isComputer; }
        void setComputer(bool isComputer) { m_isComputer = isComputer; }

        // public interface
        void move(const Position& position)
        {
            validateMove(position);
            m_currentPosition = position;
        }

    protected:
        virtual void validateMove(const Position& newPosition) const
        {
            if (newPosition.getX() < 1 || newPosition.getX() > 8)
                throw std::invalid_argument("Die neue X-Positon muss zwischen 1 und 8 sein");
            if (newPosition.getY() < 1 || newPosition.getY() > 8)
                throw std::invalid_argument("Die neue Y-Positon muss zwischen 1 und 8 sein");
        }
    };

    class Tower : public ChessPiece
    {
    public:
        // c'tor(s)
        Tower(bool isComputer, Position position) : ChessPiece(isComputer, position) {}

    protected:
        void validateMove(const Position& newPosition) const override
        {
            ChessPiece::validateMove(newPosition);

            if (newPosition.getX() != getCurrentPosition().getX() &&
                newPosition.getY() != getCurrentPosition().getY())
                throw std::invalid_argument("Der Turm darf nicht diagonal bewegt werden");
        }
    };

    class Move
    {
    private:
        std::shared_ptr<ChessPiece> m_piece;

    public:
        // c'tor(s)
        Move(const std::shared_ptr<ChessPiece>& piece) : m_piece{ piece } {}

        // public (concrete) interface
        std::shared_ptr<ChessPiece>& getChessPiece() { return m_piece; }

        // abstract interface
        virtual void doMove() = 0;
        virtual void undoMove() = 0;
    };

    class SimpleMove : public Move
    {
    private:
        Position m_newPosition;
        Position m_oldPosition;

    public:
        SimpleMove(const std::shared_ptr<ChessPiece>& piece, const Position& position) 
            : Move{ piece }, m_newPosition{ position }, m_oldPosition{}
        {}

        virtual void doMove() override
        {
            m_oldPosition = getChessPiece()->getCurrentPosition();
            std::cout
                << "Bewege gleich die Spielfigur. Alte Position: "
                << m_oldPosition.getX() 
                << "/" 
                << m_oldPosition.getY()
                << std::endl;

            std::shared_ptr<ChessPiece> piece{ getChessPiece() };
            piece->move(m_newPosition);

            std::cout
                << "Spielfigur bewegt. Neue Position: "
                << piece->getCurrentPosition().getX()
                << "/" 
                << piece->getCurrentPosition().getY()
                << std::endl;
        }

        virtual void undoMove() override
        {
            std::cout 
                << "Bewege gleich die Spielfigur zurueck. Alte Position: " 
                << getChessPiece()->getCurrentPosition().getX()
                << "/" 
                << getChessPiece()->getCurrentPosition().getY() 
                << std::endl;

            std::shared_ptr<ChessPiece> piece{ getChessPiece() };
            piece->move(m_oldPosition);

            std::cout 
                << "Spielfigur zurueck bewegt. Neue Position: "
                << piece->getCurrentPosition().getX() 
                << "/" 
                << piece->getCurrentPosition().getY()
                << std::endl;
        }
    };

    class Board
    {
    private:
        std::queue<std::shared_ptr<Move>> m_moves;
        std::stack<std::shared_ptr<Move>> m_undos;

    public:
        Board() {}

        void enqueue(const std::shared_ptr<Move>& spielzug)
        {
            m_moves.push(spielzug);
        }

        void play()
        {
            std::cout << "Spiele " << m_moves.size() << " Spielzuege:" << std::endl;

            while (!m_moves.empty())
            {
                std::shared_ptr<Move> move{ m_moves.front() };
                m_moves.pop();

                move->doMove();
                m_undos.push(move);
            }

            std::cout << "Done." << std::endl;
        }

        void undo()
        {
            std::cout << "Starte Undos:" << std::endl;

            if (!m_undos.empty())
            {
                std::shared_ptr<Move> move = m_undos.top();
                m_undos.pop();

                move->undoMove();
                std::cout << "Undo ausgefuehrt" << std::endl;
            }
        }
    };

    class ChessGame
    {
    private:
        Board m_board;

    public:
        ChessGame() {}

        void play(const std::shared_ptr<ChessPiece>& piece, const Position& position)
        {
            std::shared_ptr<Move> move{ std::make_shared<SimpleMove>(piece, position) };
            m_board.enqueue(move);
            m_board.play();
        }

        void enqueue(const std::shared_ptr<ChessPiece>& piece, const Position& position)
        {
            std::shared_ptr<Move> move{ std::make_shared<SimpleMove>(piece, position) };
            m_board.enqueue(move);
        }

        void undo()
        {
            m_board.undo();
        }

        void play()
        {
            m_board.play();
        }
    };

    static void clientCode()
    {
        ChessGame game{};

        std::shared_ptr<ChessPiece> tower {
            std::make_shared<Tower>(false, Position{ 1, 1 })
        };

        game.enqueue(tower, Position{ 4, 1 });
        game.enqueue(tower, Position{ 6, 1 });

        game.play();

        game.undo();
        game.undo();
    }
}

void test_chess_example() {

    using namespace ChessExample;
    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
