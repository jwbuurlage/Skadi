#pragma once

namespace Skadi {

enum class Color { black, white };

enum class Result { black_win, white_win, draw, stalemate };

class Piece;

struct Square {
    int row;
    int column;
    Piece* piece;
};

} // namespace Skadi
