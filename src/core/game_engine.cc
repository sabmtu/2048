#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_),
    board_size_(board_size) {
    current_direction_ = Direction::STILL;
    Tile tile(top_left_corner_ + glm::vec2(0, 2 * tile_side_length_), 2, "white");
    Tile tile_(top_left_corner_ + glm::vec2(3 * tile_side_length_,0), 2, "white");
    //tiles_.push_back(tile);
    //tiles_.push_back(tile_);

    glm::vec2 top_left = top_left_corner_;
    for (size_t i = 0; i < num_tiles_per_side_; i++) {
        vector<Tile> test;
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            Tile empty(top_left, 0, "beige");
            test.push_back(empty);
            top_left.x += tile_side_length_;
        }
        tiles_.push_back(test);
        top_left = glm::vec2(top_left_corner_.x, top_left.y + tile_side_length_);
    }

    tiles_[0][2] = tile;
    //tiles_[3][0] = tile_;
    /*vector<Tile> tiles;
    Tile empty(tile.position_ + glm::vec2(tile_side_length_,0), 0, "beige");
    tiles.push_back(empty);
    tiles.push_back(tile);
    Tile empty_2(tile.position_ + glm::vec2(2 * tile_side_length_,0), 0, "beige");
    tiles.push_back(empty_2);
    Tile empty_3(tile.position_ + glm::vec2(3 * tile_side_length_,0), 0, "beige");
    tiles.push_back(empty_3);
    tiles_.push_back(tiles);*/
}

/*GameEngine::GameEngine(Board& board): board_(board) {

}*/

/*const Board &GameEngine::GetBoard() {
    return board_;
}*/

const vector<vector<Tile>> &GameEngine::GetTiles() {
    return tiles_;
}

void GameEngine::SetCurrentDirection(const Direction& direction) {
    current_direction_ = direction;
}

void GameEngine::MoveTiles() {
    if (current_direction_ == Direction::STILL) {
        return;
    }

    switch (current_direction_) {
        case Direction::UP:
            MoveUpUntilCollision();
            break;

        case Direction::DOWN:
            MoveDownUntilCollision();
            break;

        case Direction::LEFT:
            MoveLeftUntilCollision();
            break;

        case Direction::RIGHT:
            MoveRightUntilCollision();
            break;

        default:
            return;
    }
    /*for (size_t i = 0; i < num_tiles_per_side_; i++) {
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            if (tiles_[i][j].GetNumber() == 0) {
                continue;
            }

            MoveInDirection(tiles_[i][j], i, j);
        }
    }*/

    /*for (Tile& tile : tiles_) {
        MoveInDirection(tile, current_direction_);
    }*/
}
/*
void GameEngine::MoveInDirection(Tile& tile, size_t row, size_t col) {
    switch (current_direction_) {
      case Direction::UP:
          MoveUpUntilCollision(tile, row, col);
          break;

      case Direction::DOWN:
          MoveDownUntilCollision(tile, row, col);
          break;

      case Direction::LEFT:
          MoveLeftUntilCollision(tile, row, col);
          break;

      case Direction::RIGHT:
          MoveRightUntilCollision(tile, row, col);
          break;

      default:
          return;
    }
}*/


void GameEngine::MoveUpUntilCollision() {
    for (size_t row = 1; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row - 1][col].IsEmpty()) {
                glm::vec2 temp = tiles_[row][col].position_;
                tiles_[row][col].position_ = tiles_[row - 1][col].position_;
                tiles_[row - 1][col] = tiles_[row][col];

                Tile empty_tile(temp, 0, "beige");
                tiles_[row][col] = empty_tile;
            }
        }
    }

    /*//Sets tile position to the edge of the board if the tile moves close enough
    if (tile.position_.y - tile.kMoveSpeed <= top_left_corner_.y) {
        tile.position_.y = top_left_corner_.y;

    } else {
        tile.MoveUp();
    }*/
}

void GameEngine::MoveRightUntilCollision() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (int col = num_tiles_per_side_ - 2; col >= 0; col--) {
            if (tiles_[row][col + 1].IsEmpty()) {
                Tile temp = tiles_[row][col];
                tiles_[row][col].position_ = tiles_[row][col + 1].position_;
                tiles_[row][col + 1] = tiles_[row][col];

                Tile empty_tile(temp.position_, 0, "beige");
                tiles_[row][col] = empty_tile;
            }
        }
    }


    /*if (tile.position_.x + tile_side_length_ + tile.kMoveSpeed >= top_left_corner_.x + board_size_) {
        tile.position_.x = top_left_corner_.x + board_size_ - tile_side_length_;

    } else {
        tile.MoveRight();
    }*/
}

void GameEngine::MoveLeftUntilCollision() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 1; col < num_tiles_per_side_; col++) {
            if (tiles_[row][col - 1].IsEmpty()) {
                Tile temp = tiles_[row][col];
                tiles_[row][col].position_ = tiles_[row][col - 1].position_;
                tiles_[row][col - 1] = tiles_[row][col];

                Tile empty_tile(temp.position_, 0, "beige");
                tiles_[row][col] = empty_tile;
            }
        }
    }


    board_size_ += 1;
    /*if (tile.position_.x - tile.kMoveSpeed <= top_left_corner_.x) {
        tile.position_.x = top_left_corner_.x;

    } else {
        tile.MoveLeft();
    }*/
}

void GameEngine::MoveDownUntilCollision() {
    for (int row = num_tiles_per_side_ - 2; row >= 0; row--) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row + 1][col].IsEmpty()) {
                Tile temp = tiles_[row][col];

                tiles_[row][col].position_ = tiles_[row + 1][col].position_;
                tiles_[row + 1][col] = tiles_[row][col];

                Tile empty_tile(temp.position_, 0, "beige");
                tiles_[row][col] = empty_tile;
            }
        }
    }

    /*if (tile.position_.y + tile_side_length_ + tile.kMoveSpeed >= top_left_corner_.y + board_size_) {
        tile.position_.y = top_left_corner_.y + board_size_ - tile_side_length_;

    } else {
        tile.MoveDown();
    }*/
}


bool GameEngine::HasCollidedWithTile(Tile &tile) {
    for (const vector<Tile>& columns : tiles_) {
        for (const Tile& check_tile : columns) {
            if (check_tile == tile) {
                continue;
            }

            //Check if touching tiles to the left and right
            if (tile.position_.x - tile.kMoveSpeed <= check_tile.position_.x + tile_side_length_
                || tile.position_.x + tile_side_length_ + tile.kMoveSpeed >= check_tile.position_.x) {
                return true;

                //Check if touching tiles above and below
            } else if (tile.position_.y - tile.kMoveSpeed <= check_tile.position_.y + tile_side_length_
                       || tile.position_.y + tile_side_length_ + tile.kMoveSpeed >= check_tile.position_.y) {
                return true;
            }
        }
    }

    return false;
}

/*
Tile &GameEngine::FindCollidedTile(Tile &tile) {

}*/

}
