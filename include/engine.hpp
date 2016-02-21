#pragma once

#include "types.hpp"
#include "util/notation.hpp"
#include "game/game.hpp"

namespace Skadi {

template <class Evaluator, class Searcher>
class Engine {
  public:
    Engine(int depth, Color color) : depth_(depth), color_(color) {
        setBoardfromFEN(game_, getBoard(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    Board& getBoard() { return game_.getBoard(); }
    const Board& getBoard() const { return game_.getBoard(); }

    void forcedMove(std::string moveString) {
        auto move = generateMove(game_, moveString, colorToMove(), move_);
        move.make();
        nextMove();
    }

    Color colorToMove() const {
        return (move_ % 2 == 1) ? Color::white : Color::black;
    }

    void makeMove() {
        nextMove();
    }

    void nextMove() {
        ++move_;
        turn_ = (move_ - 1) / 2 + 1;
    }

  private:
    int depth_;
    Color color_;
    Game game_;

    // every player makes two moves each turn
    int move_ = 1;

    // a turn consists of two moves
    int turn_ = 1;

    bool whiteToMove_;

    struct CastlingRights {
        bool whiteQueenSide = true;
        bool whiteKingSide = true;
        bool blackQueenSide = true;
        bool blackKingSide = true;
    };

    CastlingRights castlingRights_;

    Evaluator evaluator;
    Searcher searcher;
};

} // namespace Skadi
