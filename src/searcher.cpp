#include "searcher.hpp"
#include "game/game.hpp"
#include "evaluator.hpp"

namespace Skadi {

std::unique_ptr<Move> MinimaxSearcher::bestMove(Evaluator* evaluator, Game* game) {
    std::vector<std::unique_ptr<Move>> allMoves;

    for (auto piece : game->getActivePieces()) {
        if (piece->getColor() != game->colorToMove())
            continue;

        for (auto& move : piece->moves(game->getHalfMove())) {
            allMoves.push_back(std::move(move));
        }
    }

    std::unique_ptr<Move> bestMove;
    int bestScore = -1000000;
    for (auto& move : allMoves) {
        move->make();
        auto score = evaluator->evaluate(game->getBoard());
        move->unmake();

        if (game->colorToMove() == Color::black)
            score *= -1;

        if (score > bestScore) {
            bestMove = std::move(move);
        }
    }

    return std::move(bestMove);
}

} // namespace Skadi
