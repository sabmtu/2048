#pragma once

#include <vector>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class Board {
public:
    Board();
    Board(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
           double board_size);
    void Draw();

private:
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    //size_t board_size_;

    vector<vector<size_t>> tiles_;

    void DrawPixelBox(const size_t row, const size_t col);
};

}

