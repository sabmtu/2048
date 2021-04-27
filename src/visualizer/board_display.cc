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
    ci::Rectf game_box(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(game_box);

}


void BoardDisplay::DrawNumberTiles(const vector<vector<Tile>>& tiles) {
    glm::vec2 tile_top_left = top_left_corner_;
    for (const vector<Tile>& t : tiles) {
        for (const Tile& tile : t) {
            glm::vec2 tile_bottom_right = tile_top_left + glm::vec2(tile_side_length_, tile_side_length_);
            ci::Rectf num_tile(tile_top_left + glm::vec2(kTileMargin, kTileMargin), tile_bottom_right - glm::vec2(kTileMargin, kTileMargin));
            ci::gl::color(tile.GetColor());
            ci::gl::drawSolidRect(num_tile);

            //Draws tile number only if the tile is not empty
            if (!tile.IsEmpty()) {
                ci::gl::drawStringCentered(std::to_string(tile.GetNumber()),
                                           tile_top_left + glm::vec2(tile_side_length_ / 2, tile_side_length_ / 3),
                                           ci::Color("gray"), ci::Font("Times New roman", 40));
            }
            //Moves tile position to next tile position to the right
            tile_top_left += glm::vec2(tile_side_length_, 0);
        }
        //Sets top left tile position to next row below
        tile_top_left = glm::vec2(top_left_corner_.x, tile_top_left.y + tile_side_length_);
    }

}


}
