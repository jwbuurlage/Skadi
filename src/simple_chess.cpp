#include <iostream>

#include <jw.hpp>
#include <skadi.hpp>

struct Game {
    unsigned int depth;
    char playerColor;
};

Game startGame(const jw::ArgParse& args) {
    Game game;

    game.depth = args.as<unsigned int>("--depth");
    game.playerColor = args.as<char>("--playercolor");

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

int main(int argc, char** argv) {
    auto args = jw::ArgParse();
    args.addOptionWithDefault("--depth", "The search depth of the engine", 4);
    args.addOptionWithDefault("--playercolor",
                              "The color of the starting player (b/w)", 'w');
    if(!args.parse(argc, argv))
        return -1;

    auto game = startGame(args);

    auto engine =
        Skadi::Engine<Skadi::PointEvaluator, Skadi::BruteForceSearcher>(
            game.depth, (game.playerColor == 'w' ? Skadi::Color::black
                                                 : Skadi::Color::white));

    auto result = playGame(game, engine);

    return 0;
}
