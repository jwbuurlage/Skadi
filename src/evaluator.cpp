#include "evaluator.hpp"
#include "game/board.hpp"
#include "game/pieces.hpp"

namespace Skadi {

int PointEvaluator::evaluate(const Board& board) {
    static std::map<ChessPiece, int> scores = {
        { ChessPiece::rook, 5 },
        { ChessPiece::knight, 3 },
        { ChessPiece::bishop, 3 },
        { ChessPiece::queen, 9 },
        { ChessPiece::king, 100 },
        { ChessPiece::pawn, 1 }
    };

    int whiteScore = 0;
    int blackScore = 0;
    for (auto& piece : board.getPieces()) {
        if (piece->getColor() == Color::white) {
            whiteScore += scores[piece->getType()];
        } else {
            blackScore += scores[piece->getType()];
        }
    }

    return whiteScore - blackScore;
}

} // namespace Skadi
