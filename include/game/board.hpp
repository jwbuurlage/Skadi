#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <jw/logging.hpp>

#include "types.hpp"

namespace Skadi {

class Piece;

class Board {
  public:
    Board();

    void addPiece(std::unique_ptr<Piece>&& piece);
    bool gameOver() const;

    Square* getSquare(int row, int col);
    Square* getSquare(std::string description);

    const std::vector<std::unique_ptr<Piece>>& getPieces() const;

    static constexpr int getSize() { return size_; }

    bool squareUnderAttack(int row, int col, Color forColor) const;

  private:
    static constexpr int size_ = 8;
    std::array<std::array<Square, size_>, size_> squares_;
    std::vector<std::unique_ptr<Piece>> pieces_;
};

} // namespace Skadi
