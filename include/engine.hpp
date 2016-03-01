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

    inline Game& getGame() { return game_; }

    inline Board& getBoard() { return game_.getBoard(); }
    inline const Board& getBoard() const { return game_.getBoard(); }

    void forcedMove(Move* move);

    void makeMove();

  private:
    int depth_;
    Color color_;
    Game game_;

    std::unique_ptr<PointEvaluator> evaluator_;
    std::unique_ptr<MinimaxSearcher> searcher_;
};

} // namespace Skadi
