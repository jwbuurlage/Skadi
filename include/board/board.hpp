#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <jw/logging.hpp>

#include "types.hpp"
#include "pieces.hpp"

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

    void addPiece(Color color, ChessPiece piece, int row,
                  int col) {
        auto& colorPieces = (color == Color::white) ? whitePieces_ : blackPieces_;
        pieces_.push_back(std::move(createPiece(this, piece, row, col, color)));
        colorPieces.push_back(&(*pieces_.back()));
    }

    bool gameOver() const { return false; }

    Square* getSquare(int row, int col) { return &squares_[row][col]; }

    void show_() const {
        std::cout << "Current position: " << std::endl;
        std::array<std::string, size_> boardString{
            "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-",
            "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-"};

        const static std::map<ChessPiece, char> labelForPiece = {
            {ChessPiece::rook, 'r'},   {ChessPiece::bishop, 'b'},
            {ChessPiece::knight, 'n'}, {ChessPiece::king, 'k'},
            {ChessPiece::queen, 'q'},  {ChessPiece::pawn, 'p'},
            {ChessPiece::none, '?'}};

        for (auto& p : whitePieces_) {
            boardString[size_ - 1 - p->getRow()][p->getColumn()] =
                labelForPiece.at(p->getType());
        }

        auto toUpper = [](char c) { return c - 'a' + 'A'; };

        for (auto& p : blackPieces_) {
            boardString[size_ - 1 - p->getRow()][p->getColumn()] =
                toUpper(labelForPiece.at(p->getType()));
        }

        for (auto row : boardString) {
            JWLogInfo << row << endLog;
        }
    }

    const std::vector<std::unique_ptr<Piece>>& getPieces() const {
        return pieces_;
    }

    static constexpr int getSize() { return size_; }

  private:
    static constexpr int size_ = 8;
    std::array<std::array<Square, size_>, size_> squares_;
    std::vector<std::unique_ptr<Piece>> pieces_;

    std::vector<Piece*> whitePieces_;
    std::vector<Piece*> blackPieces_;
};

} // namespace Skadi
