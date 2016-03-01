#include <memory>

#include "game/moves.hpp"

#pragma once

namespace Skadi {

class Evaluator;
class Game;

class Searcher {
  public:
    virtual std::unique_ptr<Move> bestMove(Evaluator* evaluator,
                                           Game* game) = 0;
};

class MinimaxSearcher : public Searcher {
  public:
    MinimaxSearcher(int depth) : depth_(depth) {}
    std::unique_ptr<Move> bestMove(Evaluator* evaluator, Game* game) override;

  private:
    int depth_ = 0;
};

} // namespace Skadi
