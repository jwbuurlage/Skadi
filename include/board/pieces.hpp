#pragma once

#include <vector>
#include <string>

namespace Skadi {

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
    Piece() {
        row_ = 0;
        column_ = 0;
    }

    unsigned int row_;
    unsigned int column_;
};

class Pawn : public Piece {
  public:
    char getLabel() const override { return 'p'; }
};

class Rook : public Piece {
  public:
    char getLabel() const override { return 'r'; }
};

class Bishop : public Piece {
  public:
    char getLabel() const override { return 'b'; }
};

class Knight : public Piece {
  public:
    char getLabel() const override { return 'n'; }
};

class King : public Piece {
  public:
    char getLabel() const override { return 'k'; }
};

class Queen : public Piece {
  public:
    char getLabel() const override { return 'q'; }
};

} // namespace Skadi
