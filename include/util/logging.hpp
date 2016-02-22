#pragma once

namespace Skadi {

#include <jw/logging.hpp>
#include "../game/pieces.hpp"
#include "../game/board.hpp"
#include "../types.hpp"

jw::Logger& operator<<(jw::Logger& logger, const Board& board);
jw::Logger& operator<<(jw::Logger& logger, const Square& square);
jw::Logger& operator<<(jw::Logger& logger, const Piece& piece);

} // namespace Skadi
