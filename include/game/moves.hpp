#pragma once

#include <jw/logging.hpp>

#include "game.hpp"
#include "pieces.hpp"
#include "board.hpp"

namespace Skadi {

class Move {
  public:
    Move(Game* game, Board* board, Piece* piece, Square* target, int moveNumber)
        : game_(game), board_(board), piece_(piece), target_(target),
          moveNumber_(moveNumber) {}

    bool isLegal() const {
        if (piece_ == nullptr)
            return false;
        return true;
    }

    virtual void make() {
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

    void unmake() {
        // undo everything
    }

  protected:
    Game* game_;
    Board* board_;
    Piece* piece_;
    Square* target_;

    int moveNumber_;
};

class NullMove : public Move{
  public:
    NullMove() : Move(nullptr, nullptr, nullptr, nullptr, 0) {}
    void make() override { }
};

class EnPassentMove : public Move {

};

class CastlingMove : public Move {
    CastlingMove(bool castleShort, Game* game, Board* board, int moveNumber) {}
};

} // namespace Skadi
