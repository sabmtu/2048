#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_),
    board_size_(board_size) {
    current_direction_ = Direction::STILL;

    glm::vec2 top_left = top_left_corner_;
    for (size_t i = 0; i < num_tiles_per_side_; i++) {
        vector<Tile> test;
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            Tile empty(0, "beige");
            test.push_back(empty);
            top_left.x += tile_side_length_;
        }
        tiles_.push_back(test);
        top_left = glm::vec2(top_left_corner_.x, top_left.y + tile_side_length_);
    }

    Tile tile(2, "white");
    tiles_[2][0] = tile;
    tiles_[3][0] = tile;
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
    Tile empty_tile(0, "beige");
    for (size_t row = 1; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row - 1][col].IsEmpty()) {
                tiles_[row - 1][col] = tiles_[row][col];

                tiles_[row][col] = empty_tile;
            }
        }
    }
}

void GameEngine::MoveRightUntilCollision() {
    Tile empty_tile(0, "beige");
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (int col = num_tiles_per_side_ - 2; col >= 0; col--) {
            if (tiles_[row][col + 1].IsEmpty()) {
                tiles_[row][col + 1] = tiles_[row][col];

                tiles_[row][col] = empty_tile;
            }
        }
    }
}

void GameEngine::MoveLeftUntilCollision() {
    Tile empty_tile(0, "beige");
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 1; col < num_tiles_per_side_; col++) {
            if (tiles_[row][col - 1].IsEmpty()) {
                tiles_[row][col - 1] = tiles_[row][col];
                tiles_[row][col] = empty_tile;
            }
        }
    }
}

void GameEngine::MoveDownUntilCollision() {
    Tile empty_tile(0, "beige");
    for (int row = num_tiles_per_side_ - 2; row >= 0; row--) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row + 1][col].IsEmpty()) {

                tiles_[row + 1][col] = tiles_[row][col];
                tiles_[row][col] = empty_tile;
            }
        }
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
