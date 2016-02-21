#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <jw/logging.hpp>

#include "types.hpp"

namespace Skadi {

class Board {
  public:
    Board() {
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                squares_[i][j].row = i;
                squares_[i][j].column = j;
                squares_[i][j].piece = nullptr;
            }
        }
    }

    void addPiece(std::unique_ptr<Piece>&& piece) {
        pieces_.push_back(std::move(piece));
    }

    bool gameOver() const { return false; }

    Square* getSquare(int row, int col) { return &squares_[row][col]; }

    const std::vector<std::unique_ptr<Piece>>& getPieces() const {
        return pieces_;
    }

    static constexpr int getSize() { return size_; }

  private:
    static constexpr int size_ = 8;
    std::array<std::array<Square, size_>, size_> squares_;
    std::vector<std::unique_ptr<Piece>> pieces_;
};

} // namespace Skadi
