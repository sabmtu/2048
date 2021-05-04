#include <visualizer/board_display.h>

#include <utility>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace game_2048 {

BoardDisplay::BoardDisplay(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
                           double size)
                           : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
                           tile_side_length_(size / num_tiles_per_side_), board_size_(size) {
}


void BoardDisplay::Draw() {
    glm::vec2 top_left = top_left_corner_ - glm::vec2(kTileMargin, kTileMargin);
    glm::vec2 bottom_right = top_left_corner_ + glm::vec2(board_size_ + kTileMargin, board_size_ + kTileMargin);

    //Creates and draws rectangle from given positions + margin to outline board
    ci::Rectf board_outline(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(board_outline);
}

void BoardDisplay::DrawNumberTiles(const vector<vector<Tile>>& tiles) {

    //Starts drawing rectangles from top left corner of the board from row 0, column 0
    glm::vec2 tile_top_left = top_left_corner_;
    for (const vector<Tile>& t : tiles) {
        for (const Tile& tile : t) {
            glm::vec2 tile_bottom_right = tile_top_left + glm::vec2(tile_side_length_, tile_side_length_);

            //Creates and draws rectangle margin-size smaller for each Tile object in from given vector
            ci::Rectf num_tile(tile_top_left + glm::vec2(kTileMargin, kTileMargin),
                               tile_bottom_right - glm::vec2(kTileMargin, kTileMargin));
            ci::gl::color(tile.GetColor());
            ci::gl::drawSolidRect(num_tile);

            //Draws tile number only if the tile is not empty
            if (!tile.IsEmpty()) {

                //Sets text number color to gray if the number is 2 or 4 and white otherwise (just for style)
                ci::Color font_color;
                if (tile.GetNumber() < kStartTileNumBound) {
                    font_color = ci::Color("gray");

                } else {
                    font_color = ci::Color("white");
                }
                //Draws the tile's number in the tile
                ci::gl::drawStringCentered(std::to_string(tile.GetNumber()),
                                           tile_top_left + glm::vec2(tile_side_length_ / 2, tile_side_length_ / 3),
                                           font_color, kTileFont);
            }
            //Adds tile side length to x position to move tile position to next tile position to the right
            tile_top_left += glm::vec2(tile_side_length_, 0);
        }
        //Sets top left tile position to left edge of the board and add tile length to move position to next row below
        tile_top_left = glm::vec2(top_left_corner_.x, tile_top_left.y + tile_side_length_);
    }
}

}
