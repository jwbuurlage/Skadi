#pragma once

#include "game/board.hpp"

namespace Skadi {

class Evaluator {
  public:
    virtual unsigned int evaluate(const Board& board) = 0;
};

class PointEvaluator : Evaluator {
  public:
    unsigned int evaluate(const Board& board) override { return 1; }
};

} // namespace Skadi
