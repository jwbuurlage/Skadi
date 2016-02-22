#pragma once

#include <string>

namespace Skadi {

enum class Color { black, white };
enum class Result { black_win, white_win, draw, stalemate };
enum class ChessPiece { pawn, rook, knight, bishop, queen, king, none };

class Piece;

struct Square {
    int row;
    int column;
    Piece* piece;
};

const static std::string columnNames = "abcdefgh";
const static std::string rowNames = "12345678";

} // namespace Skadi
