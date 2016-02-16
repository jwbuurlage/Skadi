#include <skadi.hpp>

struct Game {
    unsigned int depth;
    char playerColor;
};

Game startGame() {
    Game game;
    cout << "depth = ";
    cin >> game.depth;

    cout << "color (b/w) = ";
    cin >> game.playerColor;

    return game;
}

std::string requestMove() {
    std::string move;
    cin >> move;
    return move;
}

Skadi::Result playGame(const Game& game, const Skadi::Engine& engine) {
    unsigned int turn = 1;
    while (!engine.getBoard().gameOver()) {
        if (turn % 2 == 1) {
            (game.playerColor == 'w') ? engine.hisMove(requestMove())
                                      : engine.yourMove();
        } else {
            (game.playerColor == 'b') ? engine.hisMove(requestMove())
                                      : engine.yourMove();
        }
        ++turn;
    }

    return Skadi::Result::draw;
}

int main() {
    auto game = startGame();

    auto engine =
        Skadi::Engine<Skadi::PointEvaluator, Skadi::BruteForceSearcher>(
            depth, (game.playerColor == 'w' ? Skadi::black : Skadi::white));

    auto result = playGame(game, engine);

    return 0;
}
