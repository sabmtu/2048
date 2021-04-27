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
     * Displays the rectangle board outline.
     */
    void Draw();

    /**
     * Displays the given vectors of tiles covering the board.
     * @param tiles 2d vector representing rows and columns of all tiles on the board
     */
    void DrawNumberTiles(const vector<vector<Tile>>& tiles);


private:
    const double kTileMargin = 5;

    //Details and size of tiles and board
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

};

}

