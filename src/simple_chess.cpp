#include <iostream>

#include <jw.hpp>
#include <skadi.hpp>

struct Game {
    int depth;
    char whitePlayer;
    char blackPlayer;
};

Game startGame(const jw::ArgParse& args) {
    Game game;

    game.depth = args.as<int>("--depth");
    game.whitePlayer = args.as<char>("--white");
    game.blackPlayer = args.as<char>("--black");

    return game;
}

std::string requestMove() {
    std::string move;
    std::cin >> move;
    return move;
}

template <class Engine>
Skadi::Result playGame(const Game& game, Engine& engine) {
    int turn = 1;
    while (!engine.getBoard().gameOver()) {
        if (turn % 2 == 1) {
            if (game.whitePlayer == 'h')  {
                JWLogInfo << engine.getBoard();
                std::cout << turn / 2 + 1 << "w. ";
                engine.forcedMove(requestMove());
            } else {
              engine.makeMove();
            }
        } else {
            if (game.blackPlayer == 'h')  {
                JWLogInfo << engine.getBoard();
                std::cout << turn / 2 + 1 << "b. ";
                engine.forcedMove(requestMove());
            } else {
              engine.makeMove();
            }
        }
        ++turn;
    }

    return Skadi::Result::draw;
}

int main(int argc, char** argv) {
    auto args = jw::ArgParse();
    args.addOptionWithDefault("--depth", "The search depth of the engine", 4);
    args.addOptionWithDefault("--white",
                              "Human or computer (h/c)", 'h');
    args.addOptionWithDefault("--black",
                              "Human or computer (h/c)", 'c');
    if(!args.parse(argc, argv))
        return -1;

    auto game = startGame(args);

    auto engine =
        Skadi::Engine<Skadi::PointEvaluator, Skadi::BruteForceSearcher>(
            game.depth, (game.whitePlayer == 'h' ? Skadi::Color::black
                                                 : Skadi::Color::white));

    auto result = playGame(game, engine);

    return 0;
}
