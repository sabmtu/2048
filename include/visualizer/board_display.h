#pragma once

#include <vector>
#include <core/tile.h>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class BoardDisplay {
public:
    BoardDisplay(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
                 double board_size);

    /**
     * Displays the board.
     */
    void Draw();

    void DrawNumberTiles(const vector<Tile>& tiles);


private:
    const double kTileMargin = 5;

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

