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
        target_->piece->capture();
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

EnPassantMove::EnPassantMove(Game* game, Board* board, Piece* piece,
                             Square* target, int halfMoveNumber,
                             EnPassantDirection direction)
    : Move(game, board, piece, target, halfMoveNumber), direction_(direction) {}

void EnPassantMove::make() {
    if (direction_ == EnPassantDirection::left) {
        board_->getSquare(piece_->getRow(), piece_->getColumn() - 1)
            ->piece->capture();
    } else if (direction_ == EnPassantDirection::right) {
        board_->getSquare(piece_->getRow(), piece_->getColumn() + 1)
            ->piece->capture();
    }

    Move::make();
}

void CastlingMove::make() {
    JWLogInfo << "CastlingMove::make()" << endLog;

    if (type_ == CastlingType::castle_short) {
        board_->getSquare(piece_->getRow(), board_->getSize() - 1)
            ->piece->move(piece_->getRow(), 5, halfMoveNumber_);
    } else if (type_ == CastlingType::castle_long) {
        board_->getSquare(piece_->getRow(), 0)
            ->piece->move(piece_->getRow(), 3, halfMoveNumber_);
    }

    Move::make();
}

} // namespace Skadi
