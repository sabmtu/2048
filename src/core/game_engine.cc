#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_),
    board_size_(board_size) {
    Tile tile(top_left_corner_, 2, "beige");
    tiles_.push_back(tile);
}

/*GameEngine::GameEngine(Board& board): board_(board) {

}*/

/*const Board &GameEngine::GetBoard() {
    return board_;
}*/

const vector<Tile> &GameEngine::GetTiles() {
    return tiles_;
}

void GameEngine::MoveTiles(const Direction& direction) {
    current_direction_ = direction;
    for (Tile& tile : tiles_) {
        if (!HasCollidedWithWall(tile) && !HasCollidedWithTile(tile)) {
            MoveInDirection(tile, current_direction_);
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

      default:
          return;
    }
}

bool GameEngine::HasCollidedWithWall(Tile& tile) {
    if (tile.position_.x <= top_left_corner_.x
    || tile.position_.x + tile_side_length_ == top_left_corner_.x + board_size_) {
        return true;

    } else if (tile.position_.y == top_left_corner_.y
    || tile.position_.y + tile_side_length_ == top_left_corner_.y + board_size_) {
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
    for (Tile& check_tile : tiles_) {
        if (check_tile == tile) {
            continue;
        }

        if (tile.position_.x <= check_tile.position_.x + tile_side_length_
        || tile.position_.x + tile_side_length_ >= check_tile.position_.x) {
            return true;

        } else if (tile.position_.y <= check_tile.position_.y + tile_side_length_
                   || tile.position_.y + tile_side_length_ >= check_tile.position_.y) {
            return true;
        }
    }
    return false;
}

}
