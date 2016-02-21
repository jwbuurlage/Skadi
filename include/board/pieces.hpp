#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Skadi {

enum class ChessPiece { pawn, rook, knight, bishop, queen, king, none };

class Board;

class Piece {
  public:
    Piece(Board* board, int row, int col, Color color)
        : board_(board), row_(row), column_(col), color_(color) {}

    void setPosition(int row, int col) {
        row_ = row;
        column_ = col;
    }

    int getRow() const { return row_; }
    int getColumn() const { return column_; }

    virtual std::vector<Square*> targets() {
        return std::vector<Square*>();
    }

    virtual ChessPiece getType() const { return ChessPiece::none; }

    virtual bool canTarget(int row, int col) {
        for (auto square : targets()) {
            if (square->row == row && square->column == col)
                return true;
        }
        return false;
    }

  protected:
    int row_;
    int column_;

    Color color_;
    Board* board_;
};

class Pawn : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::pawn; }

    std::vector<Square*> targets() override {
        std::vector<Square*> targets;
        // can move forward
        auto targetRow = (color_ == Color::white) ? row_ + 1 : row_ - 1;
        if (column_ > 0) {
            auto leftSquare = board_->getSquare(targetRow, column_ - 1);
            if (leftSquare->piece != nullptr) {
                targets.push_back(leftSquare);
            }
        }
        if (column_ < board->getSize() - 1) {
            auto rightSquare = board_->getSquare(targetRow, column_ + 1);
            if (rightSquare->piece != nullptr) {
                targets.push_back(rightSquare);
            }
        }
        auto forwardSquare = board_->getSquare(targetRow, column_);
        if (forwardSquare->piece == nullptr) {
            targets.push_back(forwardSquare);
        }

        return targets;
    }
};

class Rook : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::rook; }
};

class Knight : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::knight; }
};

class Bishop : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::bishop; }
};

class Queen : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::queen; }
};

class King : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::king; }
};

std::unique_ptr<Piece> createPiece(Board* board, ChessPiece piece, int row, int col,
                                   Color color) {
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
