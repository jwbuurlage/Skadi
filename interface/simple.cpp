#include <iostream>
#include <memory>

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

std::unique_ptr<Skadi::Move> requestMove(Skadi::Engine& engine) {
    std::string moveDescription;
    std::cin >> moveDescription;
    return Skadi::generateMove(engine.getGame(), moveDescription,
                        engine.getGame().colorToMove(),
                        engine.getGame().getHalfMove());
}

void playerMove(Skadi::Engine& engine, int turn) {
    JWLogInfo << engine.getBoard();
    std::unique_ptr<Skadi::Move> move = std::make_unique<Skadi::NullMove>();
    while (!move->isLegal()) {
        std::cout << (turn - 1) / 2 + 1 << "."
                  << ((engine.getGame().colorToMove() == Skadi::Color::black)
                          ? " (b) "
                          : " (w) ");
        move = requestMove(engine);
    }
    engine.forcedMove(move.get());
}

template <class Engine>
Skadi::Result playGame(const Game& game, Engine& engine) {
    int turn = 1;
    while (!engine.getBoard().gameOver()) {
        if (turn % 2 == 1) {
            if (game.whitePlayer == 'h')  {
                playerMove(engine, turn);
            } else {
              engine.makeMove();
            }
        } else {
            if (game.blackPlayer == 'h')  {
                playerMove(engine, turn);
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
        Skadi::Engine(
            game.depth, (game.whitePlayer == 'h' ? Skadi::Color::black
                                                 : Skadi::Color::white));

    playGame(game, engine);

    return 0;
}
