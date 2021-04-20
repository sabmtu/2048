#include <visualizer/board.h>

namespace game_2048 {

Board::Board() {}

Board::Board(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side), board_size_(board_size) {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        vector<size_t> columns;

        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            columns.push_back(0);
        }
        tiles_.push_back(columns);
    }
}

void Board::Draw() {

}



}
