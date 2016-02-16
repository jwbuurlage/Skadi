#include <memory>
#include <vector>

namespace Skadi {

class Board {
    public:
        void initializePieces() {

        };

    private:
        static const unsigned int size_ = 8;
        std::vector<std::unique_ptr<Piece>> whitePieces_;
        std::vector<std::unique_ptr<Piece>> blackPieces_;
};

} // namespace Skadi
