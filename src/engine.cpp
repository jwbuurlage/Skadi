#include "engine.hpp"
#include "evaluator.hpp"
#include "searcher.hpp"

#include <memory>

namespace Skadi {

Engine::Engine(int depth, Color color) : depth_(depth), color_(color) {
    setBoardfromFEN(game_, getBoard(),
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    evaluator_ = std::make_unique<PointEvaluator>();
    searcher_ = std::make_unique<MinimaxSearcher>(depth_);
}

void Engine::forcedMove(Move* move) {
    move->make();
    game_.nextMove();
}

void Engine::makeMove() {
    auto move = searcher_->bestMove(evaluator_.get(), &game_);
    JWLogVar(*move);
    move->make();
    game_.nextMove();
}

} // namespace Skadi
