#include "game/moves.hpp"
#include "game/game.hpp"
#include "game/pieces.hpp"
#include "game/board.hpp"

namespace Skadi {

Move::Move(Game* game, Board* board, Piece* piece, Square* target, int halfMoveNumber)
    : game_(game), board_(board), piece_(piece), target_(target), captured_(nullptr),
      halfMoveNumber_(halfMoveNumber) {}

bool Move::isLegal() const {
    if (game_ == nullptr || board_ == nullptr || piece_ == nullptr ||
        target_ == nullptr)
        return false;
    return true;
}

Square* Move::getTarget() const { return target_; }
Piece* Move::getPiece() const { return piece_; }

void Move::make() {
    if (!isLegal()) {
        JWLogError << "Illegal move" << endLog;
        return;
    }
    if (target_->piece != nullptr) {
        captured_ = target_->piece;
        target_->piece->capture();
        // FIXME: save for unmake
        game_->resetFiftyMoves();
    }

    original_ =
        game_->getBoard().getSquare(piece_->getRow(), piece_->getColumn());

    oldHalfMoveNumber_ = piece_->getLastMoved();
    piece_->move(target_->row, target_->column, halfMoveNumber_);

    if (piece_->getType() == ChessPiece::pawn) {
        // FIXME: save for unmake
        game_->resetFiftyMoves();
    }
}

void Move::unmake() {
    piece_->move(original_->row, original_->column, oldHalfMoveNumber_);
    if (captured_ != nullptr)
        captured_->uncapture();
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
    if (type_ == CastlingType::castle_short) {
        board_->getSquare(piece_->getRow(), board_->getSize() - 1)
            ->piece->move(piece_->getRow(), 5, halfMoveNumber_);
    } else if (type_ == CastlingType::castle_long) {
        board_->getSquare(piece_->getRow(), 0)
            ->piece->move(piece_->getRow(), 3, halfMoveNumber_);
    }

    Move::make();
}

void PromotionMove::make() {
    Move::make();

    // update piece to promoted piece
    piece_->capture();
    board_->addPiece(createPiece(game_, board_, promotionPiece_, target_->row,
                                 target_->column, piece_->getColor()));
    target_->piece->setLastMoved(halfMoveNumber_);
}

} // namespace Skadi
