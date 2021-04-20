#include <visualizer/board.h>

namespace game_2048 {

Board::Board() {}

Board::Board(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_) {

    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        vector<size_t> columns;

        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            columns.push_back(0);
        }
        tiles_.push_back(columns);
    }
}

void Board::Draw() {
    for (size_t row = 0; row < num_tiles_per_side_; ++row) {
        for (size_t col = 0; col < num_tiles_per_side_; ++col) {

            ci::gl::color(ci::Color("white"));

            DrawPixelBox(row, col);
        }
    }
}

void Board::DrawPixelBox(const size_t row, const size_t column) {

    //Sets corners of pixel box and draws the pixel
    glm::vec2 pixel_top_left = top_left_corner_ + glm::vec2(column * tile_side_length_,row * tile_side_length_);
    glm::vec2 pixel_bottom_right = pixel_top_left + glm::vec2(tile_side_length_, tile_side_length_);
    ci::Rectf pixel_box(pixel_top_left, pixel_bottom_right);

    ci::gl::drawSolidRect(pixel_box);

    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(pixel_box);
}



}
