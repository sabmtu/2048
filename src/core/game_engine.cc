#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {
    tiles_ = board_.GetTiles();
}

/*const vector<vector<Tile>> &GameEngine::GetTiles() {
    return tiles_;
}*/

void GameEngine::MoveTiles(const Direction& direction) {
    for (size_t row = 0; row < board_.GetNumTilesPerSide(); row++) {
        for (size_t col = 0; col < board_.GetNumTilesPerSide(); col++) {

            MoveInDirection(tiles_[row][col], direction);
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

bool GameEngine::CheckTileMerge() {
    return false;
}

void GameEngine::MergeTiles() {

}

bool GameEngine::HasCollidedWithTile(Tile &tile) {
    return false;
}


}
