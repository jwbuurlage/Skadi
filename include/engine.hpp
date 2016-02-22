#pragma once

#include "types.hpp"
#include "util/notation.hpp"
#include "game/game.hpp"
#include "searcher.hpp"
#include "evaluator.hpp"

namespace Skadi {

class Engine {
  public:
    Engine(int depth, Color color);
    inline Board& getBoard() { return game_.getBoard(); }
    inline const Board& getBoard() const { return game_.getBoard(); }

    void forcedMove(std::string moveString);

    inline void makeMove() {
        game_.nextMove();
    }

  private:
    int depth_;
    Color color_;
    Game game_;

    std::unique_ptr<Evaluator> evaluator;
    std::unique_ptr<Searcher> searcher;
};

} // namespace Skadi
