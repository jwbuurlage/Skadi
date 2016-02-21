#pragma once

#include "pieces.hpp"
#include "board.hpp"

namespace Skadi {

class Move {
  public:
    Move(Board* board, Piece* piece, Square* target, int moveNumber)
        : board_(board), piece_(piece), target_(target),
          moveNumber_(moveNumber) {}

    bool isLegal() const {
        if (piece_ == nullptr)
            return false;
        return true;
    }

    void make() {
        if (!isLegal()) {
            JWLogError << "Illegal move" << endLog;
            return;
        }

        // FIXME: first remove piece on target by capturing
        // ...
        piece_->move(target_->row, target_->column, moveNumber_);
    }

    void unmake() { };

  private:
      Board* board_;
      Piece* piece_;
      Square* target_;
      int moveNumber_;
};

} // namespace Skadi
