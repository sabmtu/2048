#pragma once

#include <vector>
#include <core/tile.h>
#include <core/board.h>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class BoardDisplay {
public:
    BoardDisplay(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
                 double board_size);
    //BoardDisplay(const Board& board);

    /**
     * Displays the board.
     */
    void Draw();

    const double kTileMargin = 10;

private:
    //Board board_;

    //Details and size of tiles and board
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

    /**
     * Draws the number tiles in the game.
     */
    void DrawTiles();
};

}

