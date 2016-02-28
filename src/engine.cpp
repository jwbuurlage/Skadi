#include "engine.hpp"

namespace Skadi {

Engine::Engine(int depth, Color color) : depth_(depth), color_(color) {
    setBoardfromFEN(game_, getBoard(),
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Engine::forcedMove(Move* move) {
    move->make();
    game_.nextMove();
}

} // namespace Skadi
