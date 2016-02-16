#include <types.hpp>

namespace Skadi {

template <class Evaluator, class Searcher>
class Engine {
  public:
    Engine(unsigned int depth, Color color) : depth_(depth), color_(color) {}

    const Board& getBoard() const { return Board; }

    void hisMove(std::string move) {}

    void yourMove() {

    }

  private:
    unsigned int depth_;
    Color color_;
    Board board_;

    Evaluator evaluator;
    Searcher searcher;
};

} // namespace Skadi
