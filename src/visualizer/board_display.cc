#include <visualizer/board_display.h>

#include <utility>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace game_2048 {

BoardDisplay::BoardDisplay() {}

BoardDisplay::BoardDisplay(const Board& board) : board_(board) {
}

void BoardDisplay::Draw() {
    glm::vec2 top_left = board_.GetTopLeftCorner() - glm::vec2(board_.kTileMargin, board_.kTileMargin);
    glm::vec2 bottom_right = board_.GetTopLeftCorner() + glm::vec2(board_.GetBoardSize() + board_.kTileMargin, board_.GetBoardSize() + board_.kTileMargin);
    ci::Rectf game_box(top_left, bottom_right);
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(game_box);

    glm::vec2 tile_top_left = board_.GetTopLeftCorner();
    glm::vec2 tile_bottom_right;
    for (size_t row = 0; row < board_.GetNumTilesPerSide(); row++) {
        for (size_t col = 0; col < board_.GetNumTilesPerSide(); col++) {
            tile_bottom_right = tile_top_left + glm::vec2(board_.GetTileSideLength(), board_.GetTileSideLength());
            ci::Rectf empty_tile(tile_top_left, tile_bottom_right);
            ci::gl::color(ci::Color("beige"));
            ci::gl::drawSolidRect(empty_tile);

            tile_top_left += glm::vec2(board_.GetTileSideLength() + board_.kTileMargin, 0);
        }
        tile_top_left = glm::vec2(board_.GetTopLeftCorner().x, tile_top_left.y + board_.GetTileSideLength() + board_.kTileMargin);
    }
    DrawTiles();
}

void BoardDisplay::DrawTiles() {
    vector<Tile> tiles = board_.GetTiles();
    for (Tile& tile : tiles) {
        glm::vec2 tile_bottom_right = tile.position_ + glm::vec2(board_.GetTileSideLength(), board_.GetTileSideLength());
        ci::Rectf num_tile(tile.position_, tile_bottom_right);
        ci::gl::color(tile.GetColor());
        ci::gl::drawSolidRect(num_tile);
    }
}


}
