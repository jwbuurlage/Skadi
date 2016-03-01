#pragma once

#include <jw/logging.hpp>
#include "../game/pieces.hpp"
#include "../game/board.hpp"
#include "../game/moves.hpp"
#include "../types.hpp"

namespace Skadi {

jw::Logger& operator<<(jw::Logger& logger, const Board& board);
jw::Logger& operator<<(jw::Logger& logger, const Square& square);
jw::Logger& operator<<(jw::Logger& logger, const Piece& piece);
jw::Logger& operator<<(jw::Logger& logger, const Move& move);

} // namespace Skadi
