#include <visualizer/board_display.h>

#include <utility>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace game_2048 {

BoardDisplay::BoardDisplay(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
                           double size)
                           : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
                           board_size_(size) {
}


void BoardDisplay::Draw() {
    glm::vec2 top_left = top_left_corner_ - glm::vec2(kTileMargin, kTileMargin);
    glm::vec2 bottom_right = top_left_corner_ + glm::vec2(board_size_ + kTileMargin, board_size_ + kTileMargin);
    ci::Rectf game_box(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(game_box);

    DrawTiles();
}

void BoardDisplay::DrawTiles() {
    glm::vec2 tile_top_left = top_left_corner_;
    glm::vec2 tile_bottom_right;

    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            tile_bottom_right = tile_top_left + glm::vec2(tile_side_length_, tile_side_length_);
            ci::Rectf empty_tile(tile_top_left, tile_bottom_right);
            ci::gl::color(ci::Color("white"));
            ci::gl::drawSolidRect(empty_tile);

            tile_top_left += glm::vec2(tile_side_length_ + kTileMargin, 0);
        }
        tile_top_left = glm::vec2(top_left_corner_.x, tile_top_left.y + tile_side_length_ + kTileMargin);
    }
    /*vector<Tile> tiles = GetTiles();
    for (Tile& tile : tiles) {
        glm::vec2 tile_bottom_right = tile.position_ + glm::vec2(tile_side_length_, tile_side_length_);
        ci::Rectf num_tile(tile.position_, tile_bottom_right);
        ci::gl::color(tile.GetColor());
        ci::gl::drawSolidRect(num_tile);
    }*/
}


}
