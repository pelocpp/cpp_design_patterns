// ===========================================================================
// Chess_Modern.cpp // Command Pattern using Modern C++
// ===========================================================================

#include <print> // Ersetzt <iostream> für modernere I/O
#include <queue> 
#include <stack>
#include <stdexcept>
#include <memory>
#include <utility>

namespace ChessExample_Modern {

    class Position {
    private:
        // Modern: In-Class-Initialisierung statt magischer Zahlen im Konstruktor
        int m_x{ -1 };
        int m_y{ -1 };

    public:
        // Standard-Konstruktor nutzt nun automatisch die Standard-Werte oben
        Position() = default;
        Position(int x, int y) : m_x{ x }, m_y{ y } {}

        int getX() const { return m_x; }
        void setX(int x) { m_x = x; }
        int getY() const { return m_y; }
        void setY(int y) { m_y = y; }
    };

    class ChessPiece {
    private:
        bool     m_isComputer{ false };
        Position m_currentPosition;

    public:
        virtual ~ChessPiece() = default; // Virtueller Destruktor für Basisklasse

        ChessPiece() = default;
        ChessPiece(bool isComputer, Position position)
            : m_isComputer{ isComputer }, m_currentPosition{ std::move(position) }
        {}

        const Position& getCurrentPosition() const { return m_currentPosition; }
        void setCurrentPosition(Position currentPosition) { m_currentPosition = std::move(currentPosition); }

        bool isComputer() const { return m_isComputer; }
        void setComputer(bool isComputer) { m_isComputer = isComputer; }

        void move(const Position& position) {
            validateMove(position);
            m_currentPosition = position;
        }

    protected:
        virtual void validateMove(const Position& newPosition) const {
            if (newPosition.getX() < 1 || newPosition.getX() > 8)
                throw std::invalid_argument("Die neue X-Positon muss zwischen 1 und 8 sein");
            if (newPosition.getY() < 1 || newPosition.getY() > 8)
                throw std::invalid_argument("Die neue Y-Positon muss zwischen 1 und 8 sein");
        }
    };

    // Modern: final verhindert ungewollte weitere Vererbung
    class Rook final : public ChessPiece {
    public:
        Rook(bool isComputer, Position position)
            : ChessPiece(isComputer, std::move(position))
        {}

    protected:
        void validateMove(const Position& newPosition) const override {
            ChessPiece::validateMove(newPosition);

            if (newPosition.getX() != getCurrentPosition().getX() &&
                newPosition.getY() != getCurrentPosition().getY())
                throw std::invalid_argument("Der Turm darf nicht diagonal bewegt werden");
        }
    };

    // Die Command-Basisklasse
    class Move {
    protected:
        // shared_ptr ist hier richtig, da mehrere Moves dieselbe Figur referenzieren
        std::shared_ptr<ChessPiece> m_piece;

    public:
        virtual ~Move() = default;

        explicit Move(std::shared_ptr<ChessPiece> piece)
            : m_piece{ std::move(piece) }
        {}

        // Modern: Rückgabe als const-Referenz oder normale Referenz auf den shared_ptr
        const std::shared_ptr<ChessPiece>& getChessPiece() const { return m_piece; }

        virtual void doMove() = 0;
        virtual void undoMove() = 0;
    };

    // Das konkrete Command
    class SimpleMove final : public Move {
    private:
        Position m_newPosition;
        Position m_oldPosition;

    public:
        SimpleMove(std::shared_ptr<ChessPiece> piece, Position position)
            : Move{ std::move(piece) }, m_newPosition{ std::move(position) }
        {}

        void doMove() override {
            m_oldPosition = m_piece->getCurrentPosition();

            std::println("Bewege gleich die Spielfigur. Alte Position: {}/{}",
                m_oldPosition.getX(), m_oldPosition.getY());

            m_piece->move(m_newPosition);

            std::println("Spielfigur bewegt. Neue Position: {}/{}",
                m_piece->getCurrentPosition().getX(), m_piece->getCurrentPosition().getY());
        }

        void undoMove() override {
            std::println("Bewege gleich die Spielfigur zurueck. Alte Position: {}/{}",
                m_piece->getCurrentPosition().getX(), m_piece->getCurrentPosition().getY());

            m_piece->move(m_oldPosition);

            std::println("Spielfigur zurueck bewegt. Neue Position: {}/{}",
                m_piece->getCurrentPosition().getX(), m_piece->getCurrentPosition().getY());
        }
    };

    // Der Invoker / Receiver-Manager
    class Board {
    private:
        // Modern: Ein Move gehört exklusiv dem Board-Verlauf, daher unique_ptr
        std::queue<std::unique_ptr<Move>> m_moves;
        std::stack<std::unique_ptr<Move>> m_undos;

    public:
        Board() = default;

        // Nimmt das Command per unique_ptr und Eigentumsübergang an
        void enqueue(std::unique_ptr<Move> spielzug) {
            m_moves.push(std::move(spielzug));
        }

        void play() {
            std::println("Spiele {} Spielzuege:", m_moves.size());

            while (!m_moves.empty()) {
                // Eigentum aus der Queue herausbewegen (ab C++23 via .pop() direkt, 
                // in C++20 via front() + pop())
                std::unique_ptr<Move> move = std::move(m_moves.front());
                m_moves.pop();

                move->doMove();
                m_undos.push(std::move(move)); // Weiter in den Undo-Stack schieben
            }

            std::println("Done.");
        }

        void undo() {
            std::println("Starte Undo:");

            if (!m_undos.empty()) {
                std::unique_ptr<Move> move = std::move(m_undos.top());
                m_undos.pop();

                move->undoMove();
                std::println("Undo ausgefuehrt");
            }
            else {
                std::println("Keine Zuege zum Rueckgaengigmachen vorhanden.");
            }
        }
    };

    class ChessGame {
    private:
        Board m_board;

    public:
        ChessGame() = default;

        void play(const std::shared_ptr<ChessPiece>& piece, Position position) {
            // make_unique statt make_shared für das Command
            m_board.enqueue(std::make_unique<SimpleMove>(piece, std::move(position)));
            m_board.play();
        }

        void enqueue(const std::shared_ptr<ChessPiece>& piece, Position position) {
            m_board.enqueue(std::make_unique<SimpleMove>(piece, std::move(position)));
        }

        void undo() { m_board.undo(); }
        void play() { m_board.play(); }
    };

    static void clientCode() {
        ChessGame game;

        // Die Figur selbst bleibt shared, da sie über mehrere Züge hinweg existiert
        auto tower = std::make_shared<Rook>(false, Position{ 1, 1 });

        game.enqueue(tower, Position{ 4, 1 });
        game.enqueue(tower, Position{ 6, 1 });

        game.play();

        game.undo();
        game.undo();
    }
}

void test_chess_example_modern() {

    using namespace ChessExample_Modern;

    clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
