#pragma once

#include "pieces.hpp"
#include "board.hpp"

namespace Skadi {

class Move {
  public:
    Move(Board* board, Piece* piece, Square* target)
        : board_(board), piece_(piece), target_(target) {}

    bool isLegal() const { return true; }

    void make() { piece_->setPosition(target_->row, target_->column); }
    void unmake() { };

  private:
      Board* board_;
      Piece* piece_;
      Square* target_;
};

} // namespace Skadi
