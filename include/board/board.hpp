#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <jw/logging.hpp>

#include "pieces.hpp"

namespace Skadi {

struct Square {
    int row;
    int col;
    Piece* piece;
};

class Board {
  public:
    void show_() const {
        std::cout << "Current position: " << std::endl;
        std::array<std::string, size_> boardString{
            "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-",
            "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-"};

        for (auto& p : whitePieces_) {
            boardString[size_ - 1 - p->getRow()][p->getColumn()] =
                p->getLabel();
        }

        auto toUpper = [](char c) { return c - 'a' + 'A'; };

        for (auto& p : blackPieces_) {
            boardString[size_ - 1 - p->getRow()][p->getColumn()] =
                toUpper(p->getLabel());
        }

        for (auto row : boardString) {
            JWLogInfo << row << endLog;
        }
    }

    void addPiece(Color color, ChessPiece piece, unsigned int row,
                  unsigned int col) {
        auto& pieces = (color == Color::white) ? whitePieces_ : blackPieces_;
        pieces.push_back(std::move(createPiece(piece, row, col)));
    }

    bool gameOver() const { return false; }

  private:
    static constexpr unsigned int size_ = 8;
    std::array<std::array<Square, size_>, size_> squares_;
    std::vector<std::unique_ptr<Piece>> whitePieces_;
    std::vector<std::unique_ptr<Piece>> blackPieces_;
};

} // namespace Skadi
