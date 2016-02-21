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
        auto move = generateMove(game_, moveString, game_.colorToMove(), game_.getHalfMove());
        move.make();
        game_.nextMove();
    }

    void makeMove() {
        game_.nextMove();
    }

  private:
    int depth_;
    Color color_;
    Game game_;

    Evaluator evaluator;
    Searcher searcher;
};

} // namespace Skadi
