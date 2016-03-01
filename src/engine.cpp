#include "engine.hpp"
#include "evaluator.hpp"

#include <memory>

namespace Skadi {

Engine::Engine(int depth, Color color) : depth_(depth), color_(color) {
    setBoardfromFEN(game_, getBoard(),
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    evaluator_ = std::make_unique<PointEvaluator>();
}

void Engine::forcedMove(Move* move) {
    move->make();
    game_.nextMove();
}

void Engine::makeMove() {
    // apply first valid move
    std::vector<std::unique_ptr<Move>> allMoves;

    for (auto piece : game_.getActivePieces()) {
        if (piece->getColor() != game_.colorToMove())
            continue;

        for (auto& move : piece->moves(game_.getHalfMove())) {
            allMoves.push_back(std::move(move));
        }
    }

    Move* bestMove = nullptr;
    int bestScore = -1000000;
    for (auto& move : allMoves) {
        move->make();
        auto score = evaluator_->evaluate(game_.getBoard());
        move->unmake();

        if (game_.colorToMove() == Color::black)
            score *= -1;

        if (score > bestScore) {
            bestMove = move.get();
        }
    }

    JWAssert(bestMove != nullptr);

    bestMove->make();
    game_.nextMove();
}

} // namespace Skadi
