#pragma once

#include "types.hpp"
#include "util/notation.hpp"
#include "board/board.hpp"

namespace Skadi {

template <class Evaluator, class Searcher>
class Engine {
  public:
    Engine(unsigned int depth, Color color) : depth_(depth), color_(color) {
        setBoardfromFEN(
            this->board_,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    const Board& getBoard() const { return board_; }

    void hisMove(std::string move) {}

    void yourMove() {
    }

  private:
    unsigned int depth_;
    Color color_;
    Board board_;

    unsigned int move_;
    bool whiteToMove_;

    struct CastlingRight {
        bool whiteQueenSide = true;
        bool whiteKingSide = true;
        bool blackQueenSide = true;
        bool blackKingSide = true;
    };

    CastlingRight castlingRight_;

    Evaluator evaluator;
    Searcher searcher;
};

} // namespace Skadi
