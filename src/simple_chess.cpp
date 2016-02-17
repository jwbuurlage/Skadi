#include <iostream>

#include <skadi.hpp>

struct Game {
    unsigned int depth;
    char playerColor;
};

Game startGame() {
    Game game;
//    std::cout << "depth = ";
//    std::cin >> game.depth;
//
//    std::cout << "color (b/w) = ";
//    std::cin >> game.playerColor;

    game.depth = 2;
    game.playerColor = 'w';

    return game;
}

std::string requestMove() {
    std::string move;
    std::cin >> move;
    return move;
}

template <class Engine>
Skadi::Result playGame(const Game& game, Engine& engine) {
    unsigned int turn = 1;
    while (!engine.getBoard().gameOver()) {
        engine.getBoard().show_();
        if (turn % 2 == 1) {
            (game.playerColor == 'w') ? engine.hisMove(requestMove())
                                      : engine.yourMove();
        } else {
            (game.playerColor == 'b') ? engine.hisMove(requestMove())
                                      : engine.yourMove();
        }
        engine.getBoard().show_();
        ++turn;
    }

    return Skadi::Result::draw;
}

int main() {
    auto game = startGame();

    auto engine =
        Skadi::Engine<Skadi::PointEvaluator, Skadi::BruteForceSearcher>(
            game.depth, (game.playerColor == 'w' ? Skadi::Color::black
                                                 : Skadi::Color::white));

    auto result = playGame(game, engine);

    return 0;
}
