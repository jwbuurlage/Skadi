#pragma once


#include <memory>

#include "game/pieces.hpp"
#include "game/game.hpp"
#include "game/board.hpp"
#include "game/moves.hpp"

#include "util/logging.hpp"

#include "types.hpp"

namespace Skadi {

void setBoardfromFEN(Game& game, Board& board, std::string fen);
std::string boardToFEN(Board& board);

std::unique_ptr<Move> generateMove(Game& game, std::string move, Color byColor, int moveNumber);

} // namespace Skadi
