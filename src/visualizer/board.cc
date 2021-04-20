#include <visualizer/board.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace game_2048 {

Board::Board() {}

Board::Board(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_), board_size_(board_size)  {

    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        vector<Tile> columns;

        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            glm::vec2 tile_top_left = top_left_corner_ + glm::vec2(col * tile_side_length_,row * tile_side_length_);
            Tile empty_tile(tile_top_left, 0, ci::Color("beige"));
            columns.push_back(empty_tile);
        }
        tiles_.push_back(columns);
    }
    tiles_[2][0] = Tile(top_left_corner_ + glm::vec2(0, 2 * tile_side_length_), 2, "white");
    tiles_[3][1] = Tile(top_left_corner_ + glm::vec2(tile_side_length_, 3 * tile_side_length_), 2, "white");
}

void Board::Draw() {
    glm::vec2 top_left = top_left_corner_ - glm::vec2(kTileMargin, kTileMargin);
    glm::vec2 bottom_right = top_left + glm::vec2(board_size_ + kTileMargin, board_size_ + kTileMargin);
    ci::Rectf game_box(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(game_box);

    for (size_t row = 0; row < num_tiles_per_side_; ++row) {
        for (size_t col = 0; col < num_tiles_per_side_; ++col) {

            ci::gl::color(tiles_[row][col].GetColor());

            DrawTile(tiles_[row][col]);
            //ci::gl::Texture texture = ci::loadImage( "tile_2.png" );
            //ci::gl::draw( texture );
        }
    }
}

void Board::DrawTile(const Tile& tile) {
    glm::vec2 pixel_bottom_right = tile.position_ + glm::vec2(tile_side_length_ - kTileMargin, tile_side_length_ - kTileMargin);
    ci::Rectf pixel_box(tile.position_, pixel_bottom_right);

    ci::gl::drawSolidRect(pixel_box);
}

    /*void Board::DrawPixelBox(const size_t row, const size_t column) {

    //Sets corners of pixel box and draws the pixel
    //glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(column * tile_side_length_,row * tile_side_length_);
    glm::vec2 pixel_bottom_right = tiles_[row][column].position_ + glm::vec2(tile_side_length_ - kTileMargin, tile_side_length_ - kTileMargin);
    ci::Rectf pixel_box(tiles_[row][column].position_, pixel_bottom_right);

    ci::gl::drawSolidRect(pixel_box);

    //ci::gl::color(ci::Color("black"));
    //ci::gl::drawStrokedRect(pixel_box);
}*/



}
