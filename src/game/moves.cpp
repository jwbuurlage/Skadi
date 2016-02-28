#include "game/moves.hpp"
#include "game/game.hpp"
#include "game/pieces.hpp"
#include "game/board.hpp"

namespace Skadi {

Move::Move(Game* game, Board* board, Piece* piece, Square* target, int halfMoveNumber)
    : game_(game), board_(board), piece_(piece), target_(target),
      halfMoveNumber_(halfMoveNumber) {}

bool Move::isLegal() const {
    if (game_ == nullptr || board_ == nullptr || piece_ == nullptr ||
        target_ == nullptr)
        return false;
    return true;
}

Square* Move::getTarget() const { return target_; }

void Move::make() {
    if (!isLegal()) {
        JWLogError << "Illegal move" << endLog;
        return;
    }
    if (target_->piece != nullptr) {
        game_->deactivate(target_->piece);
        target_->piece->capture();
        target_->piece = nullptr;

        // FIXME: save for unmake
        game_->resetFiftyMoves();
    }

    piece_->move(target_->row, target_->column, halfMoveNumber_);
    if (piece_->getType() == ChessPiece::pawn) {
        // FIXME: save for unmake
        game_->resetFiftyMoves();
    }
}

void Move::unmake() {
    // undo everything
}

} // namespace Skadi
