#include "engine.hpp"

namespace Skadi {

Move::Move(Game* game, Board* board, Piece* piece, Square* target, int moveNumber)
    : game_(game), board_(board), piece_(piece), target_(target),
      moveNumber_(moveNumber) {}

bool Move::isLegal() const {
    if (piece_ == nullptr)
        return false;
    return true;
}

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

    piece_->move(target_->row, target_->column, moveNumber_);
    if (piece_->getType() == ChessPiece::pawn) {
        // FIXME: save for unmake
        game_->resetFiftyMoves();
    }
}

void Move::unmake() {
    // undo everything
}

} // namespace Skadi
