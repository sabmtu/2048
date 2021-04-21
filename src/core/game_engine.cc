#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : board_(top_left_corner, num_tiles_per_side, board_size) {
}

/*const Board &GameEngine::GetBoard() {
    return board_;
}*/

void GameEngine::MoveTiles(const Direction& direction) {
    vector<Tile> tiles = board_.GetTiles();
    for (Tile& tile : tiles) {
        while (!HasCollidedWithWall(tile) && !HasCollidedWithTile(tile)) {
            MoveInDirection(tile, direction);
        }
    }
}

void GameEngine::MoveInDirection(Tile& tile, const Direction &direction) {
    switch (direction) {
      case Direction::UP:
          tile.MoveUp();
          break;

      case Direction::DOWN:
          tile.MoveDown();
          break;

      case Direction::LEFT:
          tile.MoveLeft();
          break;

      case Direction::RIGHT:
          tile.MoveRight();
          break;
    }
}

bool GameEngine::HasCollidedWithWall(Tile& tile) {
    if (tile.position_.x == board_.GetTopLeftCorner().x
    || tile.position_.x + board_.kTileMargin == board_.GetTopLeftCorner().x + board_.GetBoardSize()) {
        return true;

    } else if (tile.position_.y == board_.GetTopLeftCorner().y
    || tile.position_.y + board_.kTileMargin == board_.GetTopLeftCorner().y + board_.GetBoardSize()) {
        return true;

    } else {
        return false;
    }
}

/*bool GameEngine::CheckTileMerge() {
    return false;
}

void GameEngine::MergeTiles() {

}*/

bool GameEngine::HasCollidedWithTile(Tile &tile) {
    vector<Tile> tiles = board_.GetTiles();
    for (Tile& check_tile : tiles) {
        if (check_tile == tile) {
            continue;
        }
        double tile_margin_length = board_.GetBoardSize() + board_.kTileMargin;

        if (tile.position_.x == check_tile.position_.x + tile_margin_length
        || tile.position_.x + tile_margin_length == check_tile.position_.x) {
            return true;

        } else if (tile.position_.y == check_tile.position_.y + tile_margin_length
                   || tile.position_.y + tile_margin_length == check_tile.position_.y) {
            return true;
        }
    }
    return false;
}




}
