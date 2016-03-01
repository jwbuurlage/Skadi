#pragma once

#include "game/board.hpp"

namespace Skadi {

class Evaluator {
  public:
    Evaluator() = default;
    virtual int evaluate(const Board& board) { return 1; }
};

class PointEvaluator : public Evaluator {
  public:
    PointEvaluator() = default;
    int evaluate(const Board& board) override;
};

} // namespace Skadi
