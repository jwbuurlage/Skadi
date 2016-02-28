#include "engine.hpp"

namespace Skadi {

Engine::Engine(int depth, Color color) : depth_(depth), color_(color) {
    setBoardfromFEN(game_, getBoard(),
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Engine::forcedMove(std::string moveString) {
    auto move = generateMove(game_, moveString, game_.colorToMove(), game_.getHalfMove());
    move.make();
    game_.nextMove();
}

} // namespace Skadi