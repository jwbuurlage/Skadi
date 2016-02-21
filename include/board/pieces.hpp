#pragma once

#include <vector>
#include <string>
#include <memory>

#include "board.hpp"

namespace Skadi {

class Board;

class Piece {
  public:
    Piece(Board* board, int row, int col, Color color)
        : board_(board), row_(row), column_(col), color_(color) {
        board_->getSquare(row_, column_)->piece = this;
    }

    void move(int row, int col, int moveNumber) {
        // remove from current square
        board_->getSquare(row_, column_)->piece = nullptr;

        // add to new square
        board_->getSquare(row, col)->piece = this;

        // update position
        row_ = row;
        column_ = col;
        lastMoved_ = moveNumber;
    }

    int getRow() const { return row_; }
    int getColumn() const { return column_; }

    virtual std::vector<Square*> targets() { return std::vector<Square*>(); }

    virtual ChessPiece getType() const { return ChessPiece::none; }

    virtual bool canTarget(int row, int col) {
        for (auto square : targets()) {
            if (square->row == row && square->column == col)
                return true;
        }
        return false;
    }

    Color getColor() const { return color_; }

  protected:
    Board* board_;

    int row_;
    int column_;

    int lastMoved_ = 0;

    Color color_;

    // FIXME rmeove board and piece
    void squaresForDirection(std::vector<int> di, std::vector<int> dj,
                             std::vector<Square*>& targets) {
        for (size_t k = 0; k < di.size(); ++k) {
            for (int i = row_ + di[k], j = column_ + dj[k];
                 i >= 0 && i < board_->getSize() && j >= 0 &&
                 j < board_->getSize();
                 i += di[k], j += dj[k]) {
                auto square = board_->getSquare(i, j);
                if (square->piece != nullptr) {
                    if (square->piece->getColor() != color_)
                        targets.push_back(square);
                    break;
                }
                targets.push_back(square);
            }
        }
    }

    void filterValidSquares(std::vector<int> di, std::vector<int> dj,
                            std::vector<Square*>& targets) {
        for (size_t k = 0; k < di.size(); ++k) {
            int i = row_ + di[k];
            int j = column_ + dj[k];
            if (i >= 0 && i < board_->getSize() && j >= 0 &&
                j < board_->getSize()) {
                auto square = board_->getSquare(i, j);
                if (square->piece != nullptr) {
                    if (square->piece->getColor() != color_)
                        targets.push_back(square);
                } else {
                    targets.push_back(square);
                }
            }
        }
    }
};

class Pawn : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::pawn; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;

        // the target row is always one 'forward'
        auto targetRow = (color_ == Color::white) ? row_ + 1 : row_ - 1;

        // can capture left
        if (column_ > 0) {
            auto leftSquare = board_->getSquare(targetRow, column_ - 1);
            if (leftSquare->piece != nullptr) {
                targets.push_back(leftSquare);
            }
        }

        // can capture right
        if (column_ < board_->getSize() - 1) {
            auto rightSquare = board_->getSquare(targetRow, column_ + 1);
            if (rightSquare->piece != nullptr) {
                targets.push_back(rightSquare);
            }
        }

        // can move forward
        auto forwardSquare = board_->getSquare(targetRow, column_);
        if (forwardSquare->piece == nullptr) {
            targets.push_back(forwardSquare);
            // if not moved yet, can move two
            if (lastMoved_ == 0) {
                auto targetRowNext =
                    (color_ == Color::white) ? row_ + 2 : row_ - 2;
                auto nextForwardSquare =
                    board_->getSquare(targetRowNext, column_);
                if (nextForwardSquare->piece == nullptr)
                    targets.push_back(nextForwardSquare);
            }
        }

        // FIXME: can capture en passent
        // ...

        return targets;
    }
};

class Rook : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::rook; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        squaresForDirection({0, 1, 0, -1}, {-1, 0, 1, 0}, targets);
        return targets;
    }
};

class Knight : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::knight; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        filterValidSquares({2, 2, 1, 1, -1, -1, -2, -2},
                           {1, -1, 2, -2, 2, -2, 1, -1}, targets);
        return targets;
    }
};

class Bishop : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::bishop; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        squaresForDirection({1, -1, 1, -1}, {1, 1, -1, -1}, targets);
        return targets;
    }
};

class Queen : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::queen; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        squaresForDirection({0, 1, 0, -1, 1, -1, 1, -1},
                            {-1, 0, 1, 0, 1, 1, -1, -1}, targets);
        return targets;
    }
};

class King : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::king; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        filterValidSquares({1, 1, 1, 0, 0, -1, -1, -1},
                           {1, 0, -1, 1, -1, 1, 0, -1}, targets);
        return targets;
    }
};

std::unique_ptr<Piece> createPiece(Board* board, ChessPiece piece, int row,
                                   int col, Color color) {
    switch (piece) {
    case ChessPiece::pawn:
        return std::move(std::make_unique<Pawn>(board, row, col, color));
        break;

    case ChessPiece::rook:
        return std::move(std::make_unique<Rook>(board, row, col, color));
        break;

    case ChessPiece::knight:
        return std::move(std::make_unique<Knight>(board, row, col, color));
        break;

    case ChessPiece::bishop:
        return std::move(std::make_unique<Bishop>(board, row, col, color));
        break;

    case ChessPiece::queen:
        return std::move(std::make_unique<Queen>(board, row, col, color));
        break;

    case ChessPiece::king:
        return std::move(std::make_unique<King>(board, row, col, color));
        break;

    default:
        return std::move(std::make_unique<Pawn>(board, row, col, color));
        break;
    }
}

} // namespace Skadi
