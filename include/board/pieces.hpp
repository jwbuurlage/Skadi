#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Skadi {

enum class ChessPiece { pawn, rook, knight, bishop, queen, king };

class Piece {
  public:
    void setPosition(unsigned int row, unsigned int col) {
        row_ = row;
        column_ = col;
    }

    unsigned int getRow() const { return row_; }
    unsigned int getColumn() const { return column_; }

    virtual std::vector<std::string> moves() {
        return std::vector<std::string>();
    }

    virtual void move(std::string square) {}

    virtual char getLabel() const { return '?'; }

  protected:
    Piece(unsigned int row, unsigned int col) {
        row_ = row;
        column_ = col;
    }

    unsigned int row_;
    unsigned int column_;
};

class Pawn : public Piece {
  public:
    Pawn(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'p'; }
};

class Rook : public Piece {
  public:
    Rook(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'r'; }
};

class Knight : public Piece {
  public:
    Knight(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'n'; }
};

class Bishop : public Piece {
  public:
    Bishop(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'b'; }
};

class King : public Piece {
  public:
    King(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'k'; }
};

class Queen : public Piece {
  public:
    Queen(unsigned int row, unsigned int col) : Piece(row, col) {}
    char getLabel() const override { return 'q'; }
};


std::unique_ptr<Piece> createPiece(ChessPiece piece, unsigned int row,
                                   unsigned int col) {
    switch (piece) {
    case ChessPiece::pawn:
        return std::move(std::make_unique<Pawn>(row, col));
        break;

    case ChessPiece::rook:
        return std::move(std::make_unique<Rook>(row, col));
        break;

    case ChessPiece::knight:
        return std::move(std::make_unique<Knight>(row, col));
        break;

    case ChessPiece::bishop:
        return std::move(std::make_unique<Bishop>(row, col));
        break;

    case ChessPiece::queen:
        return std::move(std::make_unique<Queen>(row, col));
        break;

    case ChessPiece::king:
        return std::move(std::make_unique<King>(row, col));
        break;

    default:
        return std::move(std::make_unique<Pawn>(row, col));
        break;
    }
}

} // namespace Skadi
