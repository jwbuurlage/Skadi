#pragma once

#include <string>
#include <sstream>
#include <map>

#include "game/pieces.hpp"
#include "game/game.hpp"
#include "game/board.hpp"
#include "game/moves.hpp"

#include "util/logging.hpp"

#include "types.hpp"

namespace Skadi {

void setBoardfromFEN(Game& game, Board& board, std::string fen);
std::string boardToFEN(Board& board);

Move generateMove(Game& game, std::string move, Color byColor, int moveNumber);

} // namespace Skadi
