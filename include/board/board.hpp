#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "../util/logging.hpp"
#include "pieces.hpp"

namespace Skadi {

class Board {
  public:
      void show_() const {
          std::array<std::string, 8> boardString{
              "-+-+-+-+",
              "+-+-+-+-",
              "-+-+-+-+",
              "+-+-+-+-",
              "-+-+-+-+",
              "+-+-+-+-",
              "-+-+-+-+",
              "+-+-+-+-"
          };

          for (auto& p : whitePieces_) {
              LogVar(p->getRow());
              LogVar(p->getColumn());
              LogVar(p->getLabel());
              boardString[p->getRow()][p->getColumn()] = p->getLabel();
          }

          auto toUpper = [](char c) { return c - 'a' + 'A'; };

          for (auto& p : whitePieces_) {
              boardString[p->getRow()][p->getColumn()] = toUpper(p->getLabel());
          }

          for (auto row : boardString) {
              std::cout << row << std::endl;
          }
      }

      template <class TPiece>
      void addPiece(Color color, TPiece piece) {
          if (color == Color::white) {
              whitePieces_.push_back(std::make_unique<TPiece>(piece));
          } else {
              blackPieces_.push_back(std::make_unique<TPiece>(piece));
          }
      }

      bool gameOver() const { return false; }

  private:
    static const unsigned int size_ = 8;
    std::vector<std::unique_ptr<Piece>> whitePieces_;
    std::vector<std::unique_ptr<Piece>> blackPieces_;
};

} // namespace Skadi
