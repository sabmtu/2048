#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_),
    board_size_(board_size) {
    current_direction_ = Direction::STILL;

    board_size_ += 1;
    glm::vec2 top_left = top_left_corner_;
    for (size_t i = 0; i < num_tiles_per_side_; i++) {
        vector<Tile> test;
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            test.push_back(kEmptyTile);
            top_left.x += tile_side_length_;
        }
        tiles_.push_back(test);
        top_left = glm::vec2(top_left_corner_.x, top_left.y + tile_side_length_);
    }

    Tile tile(2, "white");
    tiles_[2][0] = tile;
    tiles_[3][0] = tile;
    tiles_[2][2] = tile;
    tiles_[3][3] = tile;
}

const vector<vector<Tile>> &GameEngine::GetTiles() {
    return tiles_;
}

void GameEngine::SetCurrentDirection(const Direction& direction) {
    current_direction_ = direction;
}

void GameEngine::MoveTiles() {
    switch (current_direction_) {
        case Direction::STILL:
            return;
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
}


void GameEngine::MoveUpUntilCollision() {
    for (size_t row = 1; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row - 1][col].IsEmpty()) {
                tiles_[row - 1][col] = tiles_[row][col];

                tiles_[row][col] = kEmptyTile;
            }

            if (CanMergeTileUp(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

bool GameEngine::CanMergeTileUp(size_t row, size_t col) {
    return (!tiles_[row - 1][col].IsEmpty() && (tiles_[row - 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}



void GameEngine::MoveRightUntilCollision() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (int col = num_tiles_per_side_ - 2; col >= 0; col--) {
            if (tiles_[row][col + 1].IsEmpty()) {
                tiles_[row][col + 1] = tiles_[row][col];

                tiles_[row][col] = kEmptyTile;

            } else if (CanMergeTileRight(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

bool GameEngine::CanMergeTileRight(size_t row, size_t col) {
    return (!tiles_[row][col + 1].IsEmpty() && (tiles_[row][col + 1].GetNumber() == tiles_[row][col].GetNumber()));
}

void GameEngine::MoveLeftUntilCollision() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 1; col < num_tiles_per_side_; col++) {
            if (tiles_[row][col - 1].IsEmpty()) {
                tiles_[row][col - 1] = tiles_[row][col];
                tiles_[row][col] = kEmptyTile;

            } else if (CanMergeTileLeft(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

bool GameEngine::CanMergeTileLeft(size_t row, size_t col) {
    return (!tiles_[row][col - 1].IsEmpty() && (tiles_[row][col - 1].GetNumber() == tiles_[row][col].GetNumber()));
}

void GameEngine::MoveDownUntilCollision() {
    for (int row = num_tiles_per_side_ - 2; row >= 0; row--) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row + 1][col].IsEmpty()) {

                tiles_[row + 1][col] = tiles_[row][col];
                tiles_[row][col] = kEmptyTile;

            } else if (CanMergeTileDown(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

bool GameEngine::CanMergeTileDown(size_t row, size_t col) {
    return (!tiles_[row + 1][col].IsEmpty() && (tiles_[row + 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}

void GameEngine::MergeTiles(size_t row, size_t col) {
    Tile combined_tile(2 * tiles_[row][col].GetNumber(), "yellow");

    if (current_direction_ == Direction::UP) {
        tiles_[row - 1][col] = combined_tile;
        tiles_[row][col] = kEmptyTile;

    } else if (current_direction_ == Direction::RIGHT) {
        tiles_[row][col + 1] = combined_tile;
        tiles_[row][col] = kEmptyTile;

    } else if (current_direction_ == Direction::LEFT) {
        tiles_[row][col - 1] = combined_tile;
        tiles_[row][col] = kEmptyTile;

    } else if (current_direction_ == Direction::DOWN) {
        tiles_[row + 1][col] = combined_tile;
        tiles_[row][col] = kEmptyTile;
    }
}

/*

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
*/

/*
Tile &GameEngine::FindCollidedTile(Tile &tile) {

}*/

}
