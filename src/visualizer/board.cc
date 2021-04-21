#include <visualizer/board.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace game_2048 {

Board::Board() {}

const vector<vector<Tile>> &Board::GetTiles() {
    return tiles_;
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

Board::Board(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_((board_size - (kTileMargin * (num_tiles_per_side_ - 1)))/ num_tiles_per_side_),
    board_size_(board_size)  {

    /*for (size_t row = 0; row < num_tiles_per_side_; row++) {
        vector<Tile> columns;

        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            glm::vec2 tile_top_left = top_left_corner_ + glm::vec2(col * tile_side_length_,row * tile_side_length_);
            Tile empty_tile(tile_top_left, 0, ci::Color("beige"));
            columns.push_back(empty_tile);
        }
        tiles_.push_back(columns);
    }
    tiles_[2][0] = Tile(top_left_corner_ + glm::vec2(0, 2 * tile_side_length_), 2, "white");
    tiles_[3][1] = Tile(top_left_corner_ + glm::vec2(tile_side_length_, 3 * tile_side_length_), 2, "white");*/
}

void Board::Draw() {
    glm::vec2 top_left = top_left_corner_ - glm::vec2(kTileMargin, kTileMargin);
    glm::vec2 bottom_right = top_left + glm::vec2(board_size_ + kTileMargin, board_size_ + kTileMargin);
    ci::Rectf game_box(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(game_box);

    glm::vec2 tile_top_left = top_left_corner_;
    glm::vec2 tile_bottom_right;
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            tile_bottom_right = tile_top_left + glm::vec2(tile_side_length_, tile_side_length_);
            ci::Rectf empty_tile(tile_top_left, tile_bottom_right);
            ci::gl::color(ci::Color("beige"));
            ci::gl::drawSolidRect(empty_tile);

            tile_top_left += glm::vec2(tile_side_length_ + kTileMargin, 0);
        }
        tile_top_left = glm::vec2(top_left_corner_.x, tile_top_left.y + tile_side_length_ + kTileMargin);
    }
}

/*void Board::DrawTile(const Tile& tile) {
    glm::vec2 pixel_bottom_right = tile.position_ + glm::vec2(tile_side_length_ - kTileMargin, tile_side_length_ - kTileMargin);
    ci::Rectf pixel_box(tile.position_, pixel_bottom_right);
    ci::gl::drawSolidRect(pixel_box);
    if (tile.GetNumber() != 0) {
        ci::gl::drawStringCentered(std::to_string(tile.GetNumber()), tile.position_ + glm::vec2((tile_side_length_ / 2.25), (tile_side_length_ / 2.75)),
                                   "black", ci::Font("Arial", 35.f));
    }

}*/


}
