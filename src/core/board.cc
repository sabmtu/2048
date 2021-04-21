#include <core/board.h>

namespace game_2048 {

Board::Board() {}

Board::Board(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
        : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
          tile_side_length_((board_size - (kTileMargin * (num_tiles_per_side_ - 1)))/ num_tiles_per_side_),
          board_size_(board_size)  {
    Tile test_tile(top_left_corner_, 2, "white");
    tiles_.push_back(test_tile);
}

const glm::vec2 &Board::GetTopLeftCorner() {
    return top_left_corner_;
}

const double Board::GetTileSideLength() {
    return tile_side_length_;
}

const double Board::GetBoardSize() {
    return board_size_;
}

const size_t Board::GetNumTilesPerSide() {
    return num_tiles_per_side_;
}

const vector<Tile> &Board::GetTiles() {
    return tiles_;
}

}

